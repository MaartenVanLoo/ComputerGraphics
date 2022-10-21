//
// Created by Maarten Van Loo on 1/10/2022.
//

#include <catch2/catch_all.hpp>
#include <iostream>
#include <Objects/Box.h>
using namespace MRay;
TEST_CASE("tBox_HitPoints"){
    Box box = Box();
    Intersection intersect;
    Vec4 target1, target2;
    Vec4 p1, p2;

    SECTION("Axis aligned unit cube"){
        box = Box(Vec4(0,0,0,1),Vec4(1,1,1,0));
        box.computeBoundingBox();
        Ray ray1 = Ray(Vec4(-2,-2,0.5,1),Vec4(0,2,0,0)); //no intersect
        Ray ray2 = Ray(Vec4(-2,-2,0.5,1),Vec4(2,0,0,0)); //no intersect
        Ray ray3 = Ray(Vec4(2,2,0.5,1),Vec4(0,2,0,0));   //no intersect
        Ray ray4 = Ray(Vec4(2,2,0.5,1),Vec4(2,0,0,0));   //no intersect
        Ray ray5 = Ray(Vec4(-2,-2,2,1),Vec4(2,2,0,0));   //no intersect
        Ray ray6 = Ray(Vec4(-2,-2,-2,1),Vec4(2,2,0,0));  //no intersect


        CHECK_FALSE(box.hitPoint(ray1, intersect));
        CHECK_FALSE(box.hitPoint(ray2, intersect));
        CHECK_FALSE(box.hitPoint(ray3, intersect));
        CHECK_FALSE(box.hitPoint(ray4, intersect));
        CHECK_FALSE(box.hitPoint(ray5, intersect));
        CHECK_FALSE(box.hitPoint(ray6, intersect));

        //2 intersections
        Ray ray7 = Ray(Vec4(-1.5,-2,0,1),Vec4(2,2,0,0));
        target1 = Vec4(-0.5,-1,0,1);
        target2 = Vec4(1,0.5,0,1);
        CHECK(box.hitPoint(ray7, intersect));
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
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


    }
    //TODO: continue checking


};