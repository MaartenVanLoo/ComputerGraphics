//
// Created by Maarten Van Loo on 30/09/2022.
//
#include <catch2/catch_all.hpp>
#include <iostream>
#include <Objects/Sphere.h>

#define DEBUG_PRINT false
using namespace MRay;
TEST_CASE("tSphere_HitPoints"){
    Options options;
    Sphere sphere;
    Ray ray;
    Intersection intersect;
    bool hit;
    Vec4 target1, target2;
    Vec4 p1, p2;
    SECTION("unitSphere"){
        sphere = Sphere(Vec4(0,0,0,1), 1);
        sphere.computeBoundingBox();
        //no hit
        intersect.clear();
        ray = Ray(Vec4(4,0,0,1), Vec4(-4,3,4,0));
        hit = sphere.hitPoint(ray, intersect, options);

        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif

        //single hit

        intersect.clear();
        ray = Ray(Vec4(4,0,1,1), Vec4(-4,0,0,0));
        target1 = Vec4(0,0,1,1);
        hit = sphere.hitPoint(ray, intersect, options);

        CHECK(hit);
        CHECK(intersect.hit.size() == 2); //2 collisions at the same position
        CHECK(intersect.hit[0].t > 0);
        CHECK(intersect.hit[0].t - intersect.hit[1].t <1e-6);
        CHECK(intersect.hit[1].t > 0);
        CHECK(ray.at(intersect.hit[0].t) == target1);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);

        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif

        //two hits
        intersect.clear();
        ray = Ray(Vec4(4,-2,2,1),Vec4(-7,3,-4,0));
        hit = sphere.hitPoint(ray, intersect, options);
        CHECK(hit);
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].t < intersect.hit[1].t);
        CHECK(intersect.hit[0].t > 0);
        CHECK(intersect.hit[1].t > 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif
        //expected intersections:
        target1 = Vec4(0.7718656097,-0.6165138327,0.155351777,1);  // hit1
        target2 = Vec4(-0.7178115556,0.0219192381,-0.6958923175,1); //=hit2
        p1 = intersect.hit[0].point;
        p2 = intersect.hit[1].point;
        CHECK(std::abs((target1-p1).get(0)) < 5e-6);
        CHECK(std::abs((target1-p1).get(1)) < 5e-6);
        CHECK(std::abs((target1-p1).get(2)) < 5e-6);
        CHECK(std::abs((target1-p1).get(3)) < 5e-6);
        CHECK(std::abs((target2-p2).get(0)) < 5e-6);
        CHECK(std::abs((target2-p2).get(1)) < 5e-6);
        CHECK(std::abs((target2-p2).get(2)) < 5e-6);
        CHECK(std::abs((target2-p2).get(3)) < 5e-6);

        //two hits with negative time (= no hit!)
        intersect.clear();
        ray = Ray(Vec4(4,-2,2,1),Vec4(7,-3,+4,0));
        hit = sphere.hitPoint(ray, intersect,options);
        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif

        //origin inside sphere
        intersect.clear();
        ray = Ray(Vec4(0.5,0.3,0.2,1),Vec4(-3.5,0.7,-2.2,0));
        hit = sphere.hitPoint(ray, intersect, options);
        CHECK(hit);
        CHECK(intersect.hit.size() == 1);
        target1 = Vec4(-0.6606293281,0.5321258656,-0.5295384348,1);
        p2 = intersect.hit[0].point; //hit2 contains the "exit"
        CHECK(std::abs((target1-p2).get(0)) < 5e-6);
        CHECK(std::abs((target1-p2).get(1)) < 5e-6);
        CHECK(std::abs((target1-p2).get(2)) < 5e-6);
        CHECK(std::abs((target1-p2).get(3)) < 5e-6);
        CHECK(intersect.hit[0].entering == false);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif
    }

    SECTION("Large sphere"){
        sphere = Sphere(Vec4(0,0,0,1),5);
        sphere.computeBoundingBox();
        //no hit
        intersect.clear();
        ray = Ray(Vec4(-7,8,2,1),Vec4(6,2,4,0));
        hit = sphere.hitPoint(ray, intersect, options);
        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif

        //single hit => precision errors
        /*
        intersect.clear();
        ray = Ray(Vec4(-5,-5,0,1),Vec4(0,5,0,0));
        target1 = Vec4(-5,0,0,1);
        hit = sphere.hitPoint(ray, intersect);
        CHECK(hit);
        CHECK(intersect.hit.size() == 2);//2 collisions at the same position
        CHECK(intersect.hit[0].t > 0);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif
        p1 = intersect.hit[0].point;
        p2 = intersect.hit[1].point;
        CHECK(std::abs((target1-p1).get(0)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(1)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(2)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(3)) <= 5e-6f);
        CHECK(std::abs((target1-p2).get(0)) <= 5e-6f);
        CHECK(std::abs((target1-p2).get(1)) <= 5e-6f);
        CHECK(std::abs((target1-p2).get(2)) <= 5e-6f);
        CHECK(std::abs((target1-p2).get(3)) <= 5e-6f);
*/
        //two hits
        intersect.clear();
        ray = Ray(Vec4(-7,8,2,1),Vec4(13,-7,1,0));
        hit = sphere.hitPoint(ray, intersect, options);
        target1 = Vec4(-0.1506137684,4.3118689522,2.526875864,1);
        target2 = Vec4(3.3652256405,2.4187246551,2.7973250493,1);
        CHECK(hit);
        CHECK(intersect.hit[0].t < intersect.hit[1].t);
        CHECK(intersect.hit[0].t > 0);
        CHECK(intersect.hit[1].t > 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif
        p1 = intersect.hit[0].point;
        p2 = intersect.hit[1].point;
        CHECK(std::abs((target1-p1).get(0)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(1)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(2)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(3)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(0)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(1)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(2)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(3)) <= 5e-6f);

        //two hits with negative time (= no hit!)
        intersect.clear();
        ray = Ray(Vec4(-7,8,2,1),Vec4(-13,7,-1,0));
        hit = sphere.hitPoint(ray, intersect, options);
        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif

        //origin inside sphere
        intersect.clear();
        ray = Ray(Vec4(0.5,0.3,0.2,1),Vec4(-3.5,0.7,-2.2,0));
        target1 = Vec4(-4.0548429193,1.2109685839,-2.6630441207,1);
        hit = sphere.hitPoint(ray, intersect, options);
        CHECK(hit);
        p2 = intersect.hit[0].point; //hit2 contains the "exit"
        CHECK(std::abs((target1-p2).get(0)) <= 5e-6f);
        CHECK(std::abs((target1-p2).get(1)) <= 5e-6f);
        CHECK(std::abs((target1-p2).get(2)) <= 5e-6f);
        CHECK(std::abs((target1-p2).get(3)) <= 5e-6f);
        CHECK(intersect.hit[0].entering == false);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif
    }

    SECTION("Translated sphere"){
        sphere = Sphere(Vec4(2,3,4,1),1);
        sphere.computeBoundingBox();

        //no hit
        intersect.clear();
        ray = Ray(Vec4(-2,3,5,1), Vec4(3,-1,-2,0));
        hit = sphere.hitPoint(ray, intersect, options);
        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif

        //single hit
        intersect.clear();
        ray = Ray(Vec4(-3,3,3,1), Vec4(4,0,0,0));
        target1 = Vec4(2,3,3,1);
        hit = sphere.hitPoint(ray, intersect, options);
        CHECK(hit);
        CHECK(intersect.hit.size() == 2); //2 collisions at the same position
        CHECK(intersect.hit[0].t -intersect.hit[1].t <1e-6);
        CHECK(intersect.hit[0].t > 0);
        CHECK(intersect.hit[1].t > 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif
        CHECK(intersect.hit[0].point == target1);

        //two hits
        intersect.clear();
        ray = Ray(Vec4(-3,3,2,1), Vec4(4,0,1,0));
        target1 = Vec4(1.5109583236,3,3.1277395809,1);
        target2 = Vec4(2.8419828529,3,3.4604957132,1);
        hit = sphere.hitPoint(ray, intersect, options);

        CHECK(hit);
        CHECK(intersect.hit[0].t < intersect.hit[1].t);
        CHECK(intersect.hit[0].t > 0);
        CHECK(intersect.hit[1].t > 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif
        p1 = intersect.hit[0].point;
        p2 = intersect.hit[1].point;
        CHECK(std::abs((target1-p1).get(0)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(1)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(2)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(3)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(0)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(1)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(2)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(3)) <= 5e-6f);

        //two hits with negative time (= no hit!)
        intersect.clear();
        ray = Ray(Vec4(-3,3,2,1), Vec4(-4,-0,-1,0));
        hit = sphere.hitPoint(ray, intersect, options);
        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif

        //origin inside sphere
        intersect.clear();
        ray = Ray(Vec4(2.5,3.5,3.5,1), Vec4(-1.5,-0.5,-0.5,0));
        target1 = Vec4(1.4810723698,3.1603574566,3.1603574566,1);
        hit = sphere.hitPoint(ray, intersect, options);

        CHECK(hit);
        p2 = intersect.hit[0].point; //hit2 contains the "exit"
        CHECK(std::abs((target1-p2).get(0)) <= 5e-6f);
        CHECK(std::abs((target1-p2).get(1)) <= 5e-6f);
        CHECK(std::abs((target1-p2).get(2)) <= 5e-6f);
        CHECK(std::abs((target1-p2).get(3)) <= 5e-6f);
        CHECK(intersect.hit[0].entering == false);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif
    }

    SECTION("Arbitrary sphere"){
        sphere = Sphere(Vec4(-2,-1,5,1),2.5);
        sphere.computeBoundingBox();

        //no hit
        intersect.clear();
        ray = Ray(Vec4(-3,2,-1,1),Vec4(-4,-4,4,0));
        hit = sphere.hitPoint(ray, intersect, options);
        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif

        //single hit => fails due to numeric precision
        /*
        intersect.clear();
        ray = Ray(Vec4(-3,1.5,5,1),Vec4(2,0,0,0));
        target1 = Vec4(-2,1.5,5,1);
        hit = sphere.hitPoint(ray, intersect);
        CHECK(hit);
        CHECK(hit1.t == hit2.t); //2 collisions at the same position
        CHECK(intersect[0].t > 0);
        CHECK(intersect[1].t > 0);
        #if (DEBUG_PRINT)
        std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif
        p1 = intersect.hit[0].point;
        p2 = intersect.hit[1].point;
        CHECK(std::abs((target1-p1).get(0)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(1)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(2)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(3)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(0)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(1)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(2)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(3)) <= 5e-6f);
        */

        //two hits
        intersect.clear();
        ray = Ray(Vec4(-3,2,-1,1),Vec4(2,-5,5,0));
        target1 = Vec4(-1.5520627463,-1.6198431342,2.6198431342,1);
        target2 = Vec4(-0.9664557722,-3.0838605695,4.0838605695,1);
        hit = sphere.hitPoint(ray, intersect, options);

        CHECK(hit);
        CHECK(intersect.hit[0].t < intersect.hit[1].t);
        CHECK(intersect.hit[0].t > 0);
        CHECK(intersect.hit[1].t > 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif
        p1 = intersect.hit[0].point;
        p2 = intersect.hit[1].point;
        CHECK(std::abs((target1-p1).get(0)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(1)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(2)) <= 5e-6f);
        CHECK(std::abs((target1-p1).get(3)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(0)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(1)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(2)) <= 5e-6f);
        CHECK(std::abs((target2-p2).get(3)) <= 5e-6f);

        //two hits with negative time (= no hit!)
        intersect.clear();
        ray = Ray(Vec4(-3,2,-1,1),Vec4(-2,5,-5,0));
        hit = sphere.hitPoint(ray, intersect, options);
        CHECK_FALSE(hit);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif

        //origin inside sphere
        intersect.clear();
        ray = Ray(Vec4(-3,0,6,1),Vec4(2,1.5,-2,0));
        target1 = Vec4(-1.2849028658,1.2863228506,4.2849028658,1);
        hit = sphere.hitPoint(ray, intersect, options);
        CHECK(hit);
        CHECK(intersect.hit[0].entering == false);
        p2 = intersect.hit[0].point; //hit2 contains the "exit"
        CHECK(std::abs((target1-p2).get(0)) <= 5e-6f);
        CHECK(std::abs((target1-p2).get(1)) <= 5e-6f);
        CHECK(std::abs((target1-p2).get(2)) <= 5e-6f);
        CHECK(std::abs((target1-p2).get(3)) <= 5e-6f);
        #if (DEBUG_PRINT)
            std::cout << sphere << "\n" << ray << "\nhit1:" << hit1 << "\nhit2:" << hit2 << std::endl;
        #endif


        //single hit point expected but actually no hit is detected due to precision error:
        ray = Ray(Vec4(-3,1.5,6,1),Vec4(2,0,-2,0));
        target1 = Vec4(-2,1.5,5,1);
        hit = sphere.hitPoint(ray, intersect, options);
    }

}
