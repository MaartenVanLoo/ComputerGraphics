//
// Created by Maarten Van Loo on 1/10/2022.
//

#include <catch2/catch_all.hpp>
#include <iostream>
#include "../../include/RenderEngineCore.h"

TEST_CASE("tBox_HitPoints"){
    Box box = Box();
    Ray ray;
    bool hit;
    Hit hit1, hit2;
    Vec4 target1, target2;
    Vec4 p1, p2;

    SECTION("Axis aligned unit cube"){
        box = Box(Vec4(0,0,0,1),Vec4(1,1,1,0));
        Ray ray1 = Ray(Vec4(-2,-2,0.5,1),Vec4(0,2,0,0)); //no intersect
        Ray ray2 = Ray(Vec4(-2,-2,0.5,1),Vec4(2,0,0,0)); //no intersect
        Ray ray3 = Ray(Vec4(2,2,0.5,1),Vec4(0,2,0,0));   //no intersect
        Ray ray4 = Ray(Vec4(2,2,0.5,1),Vec4(2,0,0,0));   //no intersect
        Ray ray5 = Ray(Vec4(-2,-2,2,1),Vec4(2,2,0,0));   //no intersect
        Ray ray6 = Ray(Vec4(-2,-2,-2,1),Vec4(2,2,0,0));  //no intersect


        CHECK_FALSE(box.hitPoint(ray1, hit1, hit2));
        CHECK_FALSE(box.hitPoint(ray2, hit1, hit2));
        CHECK_FALSE(box.hitPoint(ray3, hit1, hit2));
        CHECK_FALSE(box.hitPoint(ray4, hit1, hit2));
        CHECK_FALSE(box.hitPoint(ray5, hit1, hit2));
        CHECK_FALSE(box.hitPoint(ray6, hit1, hit2));

        //2 intersections
        Ray ray7 = Ray(Vec4(-1.5,-2,0,1),Vec4(2,2,0,0));
        target1 = Vec4(-0.5,-1,0,1);
        target2 = Vec4(1,0.5,0,1);
        CHECK(box.hitPoint(ray7, hit1, hit2));
        p1 = ray7.at(hit1.t);
        p2 = ray7.at(hit2.t);
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
    SECTION(""){

    }
    SECTION(""){

    }

};