//
// Created by maart on 30/09/2022.
//
#include <catch2/catch_all.hpp>
#include <iostream>
#include "../../include/RenderEngineCore.h"

#define DEBUG_PRINT false

TEST_CASE("tSphere_HitPoints"){
    Sphere sphere;
    Ray ray;
    float t1=0, t2=0;
    bool hit;
    Vec4 target1, target2;
    Vec4 p1, p2;
    SECTION("unitSphere"){
        sphere = Sphere(Vec4(0,0,0,1), 1);

        //no hit
        ray = Ray(Vec4(4,0,0,1), Vec4(-4,3,4,0));
        hit = sphere.hitPoint(ray,t1,t2);

        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif

        //single hit
        ray = Ray(Vec4(4,0,1,1), Vec4(-4,0,0,0));
        target1 = Vec4(0,0,1,1);
        hit = sphere.hitPoint(ray,t1,t2);

        CHECK(hit);
        CHECK(t1 == t2); //2 collisions at the same position
        CHECK(t1 > 0);
        CHECK(t2 > 0);
        CHECK(ray.at(t1) == target1);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif

        //two hits
        ray = Ray(Vec4(4,-2,2,1),Vec4(-7,3,-4,0));
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK(hit);
        CHECK(t1 < t2);
        CHECK(t1 > 0);
        CHECK(t2 > 0);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif
        //expected intersections:
        target1 = Vec4(0.7718656097,-0.6165138327,0.155351777,1);  // t1
        target2 = Vec4(-0.7178115556,0.0219192381,-0.6958923175,1); //=t2
        p1 = ray.at(t1);
        p2 = ray.at(t2);
        CHECK(std::abs((target1-p1).get(0)) < 5e-6);
        CHECK(std::abs((target1-p1).get(1)) < 5e-6);
        CHECK(std::abs((target1-p1).get(2)) < 5e-6);
        CHECK(std::abs((target1-p1).get(3)) < 5e-6);
        CHECK(std::abs((target2-p2).get(0)) < 5e-6);
        CHECK(std::abs((target2-p2).get(1)) < 5e-6);
        CHECK(std::abs((target2-p2).get(2)) < 5e-6);
        CHECK(std::abs((target2-p2).get(3)) < 5e-6);

        //two hits with negative time (= no hit!)
        ray = Ray(Vec4(4,-2,2,1),Vec4(7,-3,+4,0));
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif

        //origin inside sphere
        ray = Ray(Vec4(0.5,0.3,0.2,1),Vec4(-3.5,0.7,-2.2,0));
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK(hit);
        target1 = Vec4(-0.6606293281,0.5321258656,-0.5295384348,1);
        p1 = ray.at(t1);
        CHECK(std::abs((target1-p1).get(0)) < 5e-6);
        CHECK(std::abs((target1-p1).get(1)) < 5e-6);
        CHECK(std::abs((target1-p1).get(2)) < 5e-6);
        CHECK(std::abs((target1-p1).get(3)) < 5e-6);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif
    }

    SECTION("Large sphere"){
        sphere = Sphere(Vec4(0,0,0,1),5);

        //no hit
        ray = Ray(Vec4(-7,8,2,1),Vec4(6,2,4,0));
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif

        //single hit
        ray = Ray(Vec4(-5,-5,0,1),Vec4(0,5,0,0));
        target1 = Vec4(-5,0,0,1);
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK(hit);
        CHECK(t1 == t2); //2 collisions at the same position
        CHECK(t1 > 0);
        CHECK(t2 > 0);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif
        CHECK(ray.at(t1) == target1);

        //two hits
        ray = Ray(Vec4(-7,8,2,1),Vec4(13,-7,1,0));
        hit = sphere.hitPoint(ray, t1, t2);
        target1 = Vec4(-0.1506137684,4.3118689522,2.526875864,1);
        target2 = Vec4(3.3652256405,2.4187246551,2.7973250493,1);
        CHECK(hit);
        CHECK(t1 < t2);
        CHECK(t1 > 0);
        CHECK(t2 > 0);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif
        p1 = ray.at(t1);
        p2 = ray.at(t2);
        CHECK(std::abs((target1-p1).get(0)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(1)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(2)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(3)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(0)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(1)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(2)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(3)) <= 5e-6f);

        //two hits with negative time (= no hit!)
        ray = Ray(Vec4(-7,8,2,1),Vec4(-13,7,-1,0));
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif

        //origin inside sphere
        ray = Ray(Vec4(0.5,0.3,0.2,1),Vec4(-3.5,0.7,-2.2,0));
        target1 = Vec4(-4.0548429193,1.2109685839,-2.6630441207,1);
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK(hit);
        p1 = ray.at(t1);
        CHECK(std::abs((target1-p1).get(0)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(1)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(2)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(3)) <= 5e-6f);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif
    }

    SECTION("Translated sphere"){
        sphere = Sphere(Vec4(2,3,4,1),1);
        //no hit
        ray = Ray(Vec4(-2,3,5,1), Vec4(3,-1,-2,0));
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif

        //single hit
        ray = Ray(Vec4(-3,3,3,1), Vec4(4,0,0,0));
        target1 = Vec4(2,3,3,1);
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK(hit);
        CHECK(t1 == t2); //2 collisions at the same position
        CHECK(t1 > 0);
        CHECK(t2 > 0);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif
        CHECK(ray.at(t1) == target1);

        //two hits
        ray = Ray(Vec4(-3,3,2,1), Vec4(4,0,1,0));
        target1 = Vec4(1.5109583236,3,3.1277395809,1);
        target2 = Vec4(2.8419828529,3,3.4604957132,1);
        hit = sphere.hitPoint(ray, t1, t2);

        CHECK(hit);
        CHECK(t1 < t2);
        CHECK(t1 > 0);
        CHECK(t2 > 0);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif
        p1 = ray.at(t1);
        p2 = ray.at(t2);
        CHECK(std::abs((target1-p1).get(0)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(1)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(2)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(3)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(0)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(1)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(2)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(3)) <= 5e-6f);

        //two hits with negative time (= no hit!)
        ray = Ray(Vec4(-3,3,2,1), Vec4(-4,-0,-1,0));
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif

        //origin inside sphere
        ray = Ray(Vec4(2.5,3.5,3.5,1), Vec4(-1.5,-0.5,-0.5,0));
        target1 = Vec4(1.4810723698,3.1603574566,3.1603574566,1);
        hit = sphere.hitPoint(ray, t1, t2);

        CHECK(hit);
        p1 = ray.at(t1);
        CHECK(std::abs((target1-p1).get(0)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(1)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(2)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(3)) <= 5e-6f);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif
    }

    SECTION("Arbitrary sphere"){
        sphere = Sphere(Vec4(-2,-1,5,1),2.5);

        //no hit
        ray = Ray(Vec4(-3,2,-1,1),Vec4(-4,-4,4,0));
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif

        //single hit
        ray = Ray(Vec4(-3,1.5,5,1),Vec4(2,0,0,0));
        target1 = Vec4(-2,1.5,5,1);
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK(hit);
        CHECK(t1 == t2); //2 collisions at the same position
        CHECK(t1 > 0);
        CHECK(t2 > 0);
        #if (DEBUG_PRINT)
        std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif
        CHECK(ray.at(t1) == target1);

        //two hits
        ray = Ray(Vec4(-3,2,-1,1),Vec4(2,-5,5,0));
        target1 = Vec4(-1.5520627463,-1.6198431342,2.6198431342,1);
        target2 = Vec4(-0.9664557722,-3.0838605695,4.0838605695,1);
        hit = sphere.hitPoint(ray, t1, t2);

        CHECK(hit);
        CHECK(t1 < t2);
        CHECK(t1 > 0);
        CHECK(t2 > 0);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif
        p1 = ray.at(t1);
        p2 = ray.at(t2);
        CHECK(std::abs((target1-p1).get(0)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(1)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(2)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(3)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(0)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(1)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(2)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(3)) <= 5e-6f);

        //two hits with negative time (= no hit!)
        ray = Ray(Vec4(-3,2,-1,1),Vec4(-2,5,-5,0));
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif

        //origin inside sphere
        ray = Ray(Vec4(-3,0,6,1),Vec4(2,1.5,-2,0));
        target1 = Vec4(-1.2849028658,1.2863228506,4.2849028658,1);
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK(hit);
        p1 = ray.at(t1);
        CHECK(std::abs((target1-p1).get(0)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(1)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(2)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(3)) <= 5e-6f);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        #endif


        //single hit point expected but actually no hit is detected due to precision error:
        ray = Ray(Vec4(-3,1.5,6,1),Vec4(2,0,-2,0));
        target1 = Vec4(-2,1.5,5,1);
        hit = sphere.hitPoint(ray, t1, t2);
    }

}
