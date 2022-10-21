//
// Created by Maarten Van Loo on 13/10/2022.
//

#include <catch2/catch_all.hpp>
#include <iostream>
#include <Objects/TaperedCylinder.h>

#define DEBUG_PRINT false
using namespace MRay;
TEST_CASE("tTaperedCylinder_HitPoints") {
    TaperedCylinder cylinder = TaperedCylinder(1);
    cylinder.computeBoundingBox();
    Intersection intersect;
    bool hit;
    Vec4 target1, target2;
    Vec4 p1, p2;
    Vec4 n,n1,n2;

    SECTION("Origin Inside"){
        Ray ray1 = Ray(Vec4(0,0,0.5,1),Vec4(1,0,0,0)); //hit wall (0)
        Ray ray2 = Ray(Vec4(0,0,0.5,1),Vec4(0,0,-1,0)); //hit base (1)
        Ray ray3 = Ray(Vec4(0,0,0.5,1),Vec4(0,0,1,0)); //hit top (2)

        CHECK(cylinder.hitPoint(ray1,intersect));
        CHECK(intersect.hit.size() == 1);
        CHECK(intersect.hit[0].surface == 0);
        CHECK(intersect.hit[0].entering == false);
        n = intersect.hit[0].normal - Vec4(1,0,0,0);
        CHECK(std::abs(n.get(0)) < 5e-6);
        CHECK(std::abs(n.get(1)) < 5e-6);
        CHECK(std::abs(n.get(2)) < 5e-6);
        CHECK(std::abs(n.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray2,intersect));
        CHECK(intersect.hit.size() == 1);
        CHECK(intersect.hit[0].surface == 1);
        CHECK(intersect.hit[0].entering == false);
        n = intersect.hit[0].normal - Vec4(0,0,-1,0);
        CHECK(std::abs(n.get(0)) < 5e-6);
        CHECK(std::abs(n.get(1)) < 5e-6);
        CHECK(std::abs(n.get(2)) < 5e-6);
        CHECK(std::abs(n.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray3,intersect));
        CHECK(intersect.hit.size() == 1);
        CHECK(intersect.hit[0].surface == 2);
        CHECK(intersect.hit[0].entering == false);
        n = intersect.hit[0].normal - Vec4(0,0,1,0);
        CHECK(std::abs(n.get(0)) < 5e-6);
        CHECK(std::abs(n.get(1)) < 5e-6);
        CHECK(std::abs(n.get(2)) < 5e-6);
        CHECK(std::abs(n.get(3)) < 5e-6);
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
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = Vec4(-1,0,0,0);
        target2 = Vec4(1,0,0,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);


        intersect.clear();
        CHECK(cylinder.hitPoint(ray2,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 2);
        CHECK(intersect.hit[1].surface == 1);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = Vec4(0,0,1,0);
        target2 = Vec4(0,0,-1,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray3,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 1);
        CHECK(intersect.hit[1].surface == 2);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = Vec4(0,0,-1,0);
        target2 = Vec4(0,0,1,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray4,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 2);
        CHECK(intersect.hit[1].surface == 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = Vec4(0,0,1,0);
        target2 = Vec4(1,1,0,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray5,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 1);
        CHECK(intersect.hit[1].surface == 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = Vec4(0,0,-1,0);
        target2 = Vec4(1,1,0,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray6,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 0);
        CHECK(intersect.hit[1].surface == 2);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = Vec4(1,1,0,0);
        target2 = Vec4(0,0,1,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray7,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 0);
        CHECK(intersect.hit[1].surface == 1);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = Vec4(1,1,0,0);
        target2 = Vec4(0,0,-1,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

    }

    SECTION("2 intersections tapered"){
        cylinder = TaperedCylinder(0.5);
        cylinder.computeBoundingBox();

        Ray ray1 = Ray(Vec4(-2,0,0.5,1),Vec4(1,0,0,0)); //hit wall 2x (0)
        Ray ray2 = Ray(Vec4(0,0,1.5,1),Vec4(0,0,-1,0)); //hit top than base
        Ray ray3 = Ray(Vec4(0,0,-0.5,1),Vec4(0,0,1,0)); //hit base than top
        Ray ray4 = Ray(Vec4(0,0,1.5,1), Vec4(1,1,-2,0)); // hit top than wall
        Ray ray5 = Ray(Vec4(0,0,-0.5,1), Vec4(1,1,1,0)); // hit base than wall
        Ray ray6 = Ray(Vec4(1.5,1.5,0, 1),Vec4(-1,-1,0.6,0));    //hit wall than top
        Ray ray7 = Ray(Vec4(1.5,1.5,1,1), Vec4(-1,-1,-1,0)); // hit wall than base


        CHECK(cylinder.hitPoint(ray1,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 0);
        CHECK(intersect.hit[1].surface == 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = Vec4(-0.793786344,0,.39689317,0);
        target2 = Vec4(0.793786344,0,.39689317,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);


        intersect.clear();
        CHECK(cylinder.hitPoint(ray2,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 2);
        CHECK(intersect.hit[1].surface == 1);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = Vec4(0,0,1,0);
        target2 = Vec4(0,0,-1,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray3,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 1);
        CHECK(intersect.hit[1].surface == 2);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = Vec4(0,0,-1,0);
        target2 = Vec4(0,0,1,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray4,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 2);
        CHECK(intersect.hit[1].surface == 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = Vec4(0,0,1,0);
        target2 = Vec4(0.5656854249,0.5656854249,0.4,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray5,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 1);
        CHECK(intersect.hit[1].surface == 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = Vec4(0,0,-1,0);
        target2 = Vec4(0.56568542490,0.5656854249,0.4,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray6,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 0);
        CHECK(intersect.hit[1].surface == 2);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = Vec4(2.7674660216,2.7674660216,1.95689399060);
        target2 = Vec4(0,0,1,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray7,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 0);
        CHECK(intersect.hit[1].surface == 1);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = Vec4(0.7012755766,0.7012755766,0.4958767157,0);
        target2 = Vec4(0,0,-1,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);
    }

    SECTION("2 intersections tapered_90 rotated xaxis"){
        cylinder = TaperedCylinder(0.5);
        cylinder.rotate(1.57079632679,0,0);
        cylinder.computeBoundingBox();

        Ray ray1 = Ray(Vec4(-2,0,0.5,1),Vec4(1,0,0,0)); //hit wall 2x (0)
        Ray ray2 = Ray(Vec4(0,0,1.5,1),Vec4(0,0,-1,0)); //hit top than base
        Ray ray3 = Ray(Vec4(0,0,-0.5,1),Vec4(0,0,1,0)); //hit base than top
        Ray ray4 = Ray(Vec4(0,0,1.5,1), Vec4(1,1,-2,0)); // hit top than wall
        Ray ray5 = Ray(Vec4(0,0,-0.5,1), Vec4(1,1,1,0)); // hit base than wall
        Ray ray6 = Ray(Vec4(1.5,1.5,0, 1),Vec4(-1,-1,0.6,0));    //hit wall than top
        Ray ray7 = Ray(Vec4(1.5,1.5,1,1), Vec4(-1,-1,-1,0)); // hit wall than base

        ray1 = ray1.transform(AffineTransform::rotateX(1.57079632679));
        ray2 = ray2.transform(AffineTransform::rotateX(1.57079632679));
        ray3 = ray3.transform(AffineTransform::rotateX(1.57079632679));
        ray4 = ray4.transform(AffineTransform::rotateX(1.57079632679));
        ray5 = ray5.transform(AffineTransform::rotateX(1.57079632679));
        ray6 = ray6.transform(AffineTransform::rotateX(1.57079632679));
        ray7 = ray7.transform(AffineTransform::rotateX(1.57079632679));

        CHECK(cylinder.hitPoint(ray1,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 0);
        CHECK(intersect.hit[1].surface == 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = AffineTransform::rotateX(1.57079632679)*Vec4(-0.793786344,0,.39689317,0);
        target2 = AffineTransform::rotateX(1.57079632679)*Vec4(0.793786344,0,.39689317,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);


        intersect.clear();
        CHECK(cylinder.hitPoint(ray2,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 2);
        CHECK(intersect.hit[1].surface == 1);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = AffineTransform::rotateX(1.57079632679) * Vec4(0,0,1,0);
        target2 = AffineTransform::rotateX(1.57079632679) * Vec4(0,0,-1,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray3,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 1);
        CHECK(intersect.hit[1].surface == 2);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = AffineTransform::rotateX(1.57079632679) * Vec4(0,0,-1,0);
        target2 = AffineTransform::rotateX(1.57079632679) * Vec4(0,0,1,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray4,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 2);
        CHECK(intersect.hit[1].surface == 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = AffineTransform::rotateX(1.57079632679) * Vec4(0,0,1,0);
        target2 = AffineTransform::rotateX(1.57079632679) * Vec4(0.5656854249,0.5656854249,0.4,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray5,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 1);
        CHECK(intersect.hit[1].surface == 0);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 =  AffineTransform::rotateX(1.57079632679) * Vec4(0,0,-1,0);
        target2 =  AffineTransform::rotateX(1.57079632679) * Vec4(0.56568542490,0.5656854249,0.4,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray6,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 0);
        CHECK(intersect.hit[1].surface == 2);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 =  AffineTransform::rotateX(1.57079632679) * Vec4(2.7674660216,2.7674660216,1.95689399060);
        target2 =  AffineTransform::rotateX(1.57079632679) * Vec4(0,0,1,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);

        intersect.clear();
        CHECK(cylinder.hitPoint(ray7,intersect));
        CHECK(intersect.hit.size() == 2);
        CHECK(intersect.hit[0].surface == 0);
        CHECK(intersect.hit[1].surface == 1);
        CHECK(intersect.hit[0].entering == true);
        CHECK(intersect.hit[1].entering == false);
        intersect.hit[0].normal.normalize();
        intersect.hit[1].normal.normalize();
        target1 = AffineTransform::rotateX(1.57079632679) * Vec4(0.7012755766,0.7012755766,0.4958767157,0);
        target2 = AffineTransform::rotateX(1.57079632679) * Vec4(0,0,-1,0);
        target1.normalize();
        target2.normalize();
        n1 = intersect.hit[0].normal - target1;
        n2 = intersect.hit[1].normal - target2;
        CHECK(std::abs(n1.get(0)) < 5e-6);
        CHECK(std::abs(n1.get(1)) < 5e-6);
        CHECK(std::abs(n1.get(2)) < 5e-6);
        CHECK(std::abs(n1.get(3)) < 5e-6);
        CHECK(std::abs(n2.get(0)) < 5e-6);
        CHECK(std::abs(n2.get(1)) < 5e-6);
        CHECK(std::abs(n2.get(2)) < 5e-6);
        CHECK(std::abs(n2.get(3)) < 5e-6);
    }

}