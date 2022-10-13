//
// Created by maart on 13/10/2022.
//

#include <catch2/catch_all.hpp>
#include <iostream>
#include <Objects/TaperedCylinder.h>

#define DEBUG_PRINT false
using namespace MRay;
TEST_CASE("tTaperedCylinder_HitPoints") {
    TaperedCylinder cylinder = TaperedCylinder(1);
    Intersection intersect;
    bool hit;
    Vec4 target1, target2;
    Vec4 p1, p2;

    SECTION("Origin Inside"){
        Ray ray1 = Ray(Vec4(0,0,0.5,1),Vec4(1,0,0,0)); //hit wall (0)
        Ray ray2 = Ray(Vec4(0,0,0.5,1),Vec4(0,0,-1,0)); //hit base (1)
        Ray ray3 = Ray(Vec4(0,0,0.5,1),Vec4(0,0,1,0)); //hit top (2)

        CHECK(cylinder.hitPoint(ray1,intersect));
        CHECK(intersect.hit.size() == 1);
        CHECK(intersect.hit[0].surface == 0);
        CHECK(intersect.hit[0].entering == false);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray2,intersect));
        CHECK(intersect.hit.size() == 1);
        CHECK(intersect.hit[0].surface == 1);
        CHECK(intersect.hit[0].entering == false);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray3,intersect));
        CHECK(intersect.hit.size() == 1);
        CHECK(intersect.hit[0].surface == 2);
        CHECK(intersect.hit[0].entering == false);
    }

    SECTION("2 intersections"){
        Ray ray1 = Ray(Vec4(-2,0,0.5,1),Vec4(1,0,0,0)); //hit wall 2x (0)
        Ray ray2 = Ray(Vec4(0,0,1.5,1),Vec4(0,0,-1,0)); //hit top than base
        Ray ray3 = Ray(Vec4(0,0,-0.5,1),Vec4(0,0,1,0)); //hit base than top
        Ray ray4 = Ray(Vec4(0,0,1.5,1), Vec4(1,1,-1,0)); // hit top than wall
        Ray ray5 = Ray(Vec4(0,0,-0.5,1), Vec4(1,1,1,0)); // hit base than wall
        Ray ray6 = Ray(Vec4(1.5,1.5,0),Vec4(-1,-1,1,0));    //hit wall than top
        Ray ray7 = Ray(Vec4(1.5,1.5,1,1), Vec4(-1,-1,-1,0)); // hit wall than base

        CHECK(cylinder.hitPoint(ray1,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 0);
        CHECK(intersect.hit[1].surface == 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray2,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 2);
        CHECK(intersect.hit[1].surface == 1);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray3,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 1);
        CHECK(intersect.hit[1].surface == 2);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray4,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 2);
        CHECK(intersect.hit[1].surface == 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray5,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 1);
        CHECK(intersect.hit[1].surface == 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray6,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 0);
        CHECK(intersect.hit[1].surface == 2);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray7,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 0);
        CHECK(intersect.hit[1].surface == 1);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);

    }
}