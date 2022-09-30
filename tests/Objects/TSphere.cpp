//
// Created by maart on 30/09/2022.
//
#include <catch2/catch_all.hpp>
#include <iostream>
#include "../../include/RenderEngineCore.h"

#define DEBUG_PRINT false

TEST_CASE("tSphere_HitPoints"){
    Sphere unitSphere = Sphere(Vec4(0,0,0,1), 1);
    Sphere largeSphere = Sphere(Vec4(0,0,0,1),5);
    Sphere translatedSphere = Sphere(Vec4(2,3,4),1);
    Sphere arbitrarySphere = Sphere(Vec4(-2,-1,5,1),2.5);

    Ray unitRay = Ray();
    Ray largeRay = Ray();
    Ray translatedRay = Ray();
    Ray arbitraryRay = Ray();

    Sphere sphere;
    Ray ray;
    float t1=0, t2=0;
    bool hit;
    SECTION("unitSphere"){
        sphere = Sphere(Vec4(0,0,0,1), 1);

        //no hit
        ray = Ray(Vec4(4,0,0,1), Vec4(-4,3,4,0));
        hit = sphere.hitPoint(ray,t1,t2);

        CHECK_FALSE(hit);
        if (DEBUG_PRINT){
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        }

        //single hit
        ray = Ray(Vec4(4,0,1,1), Vec4(-4,0,0,0));
        hit = sphere.hitPoint(ray,t1,t2);

        CHECK(hit);
        CHECK(t1 == t2); //2 collisions at the same position
        CHECK(ray.at(t1) == Vec4(0,0,1,1));
        if (DEBUG_PRINT){
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        }

        //two hits
        ray = Ray(Vec4(4,-2,2,1),Vec4(-7,3,-4,0));
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK(hit);
        CHECK(t1 < t2);
        if (DEBUG_PRINT){
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        }
        //expected intersections:
        Vec4 target1 = Vec4(0.7718656097,-0.6165138327,0.155351777,1);  // t1
        Vec4 target2 = Vec4(-0.7178115556,0.0219192381,-0.6958923175,1); //=t2
        Vec4 p1 = ray.at(t1);
        Vec4 p2 = ray.at(t2);
        CHECK(std::abs((target1-p1).x) < 1e-6);
        CHECK(std::abs((target1-p1).y) < 1e-6);
        CHECK(std::abs((target1-p1).z) < 1e-6);
        CHECK(std::abs((target1-p1).w) < 1e-6);
        CHECK(std::abs((target2-p2).x) < 1e-6);
        CHECK(std::abs((target2-p2).y) < 1e-6);
        CHECK(std::abs((target2-p2).z) < 1e-6);
        CHECK(std::abs((target2-p2).w) < 1e-6);

        //two hits with negative time (= no hit!)
        ray = Ray(Vec4(4,-2,2,1),Vec4(7,-3,+4,0));
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK_FALSE(hit);
        if (DEBUG_PRINT){
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        }

        //origin inside sphere
        ray = Ray(Vec4(0.5,0.3,0.2,1),Vec4(-3.5,0.7,-2.2,0));
        hit = sphere.hitPoint(ray, t1, t2);
        CHECK(hit);
        if (DEBUG_PRINT){
            std::cout << sphere << "\n" << ray << "\nt1:" << t1 << "\nt2:" << t2 << std::endl;
        }
    }

    SECTION("Large sphere"){
        sphere = Sphere(Vec4(0,0,0,1),5);
        //no hit
        //single hit
        //two hits
        //two hits with negative time (= no hit!)
        //origin inside sphere
    }

    SECTION("Translated sphere"){
        sphere = Sphere(Vec4(2,3,4),1);
        //no hit
        //single hit
        //two hits
        //two hits with negative time (= no hit!)
        //origin inside sphere
    }

    SECTION("Arbitrary sphere"){
        sphere = Sphere(Vec4(-2,-1,5,1),2.5);
        //no hit
        //single hit
        //two hits
        //two hits with negative time (= no hit!)
        //origin inside sphere
    }

}
