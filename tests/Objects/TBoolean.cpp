//
// Created by maart on 13/10/2022.
//

#include <catch2/catch_all.hpp>
#include <iostream>
#include <Objects/BooleanIntersection.h>
#include <Objects/BooleanUnion.h>
#include <Objects/Object.h>
#include <Materials/MaterialsLibrary.h>
#include <Objects/Sphere.h>
#include <Objects/BooleanDifference.h>
#include <Objects/Box.h>

using namespace MRay;
TEST_CASE("tBoolean"){

    SECTION("BooleanUnion") {
        Object *obj1 = new Sphere(Vec4(0, -0.2, 0, 1), 1);
        obj1->setMaterial(MaterialsLibrary::red_plastic());
        //this->addObject(obj);

        Object *obj2 = new Sphere(Vec4(0, 0.2, 0, 1), 1);
        obj2->setMaterial(MaterialsLibrary::bronze());

        Object *obj = new BooleanUnion(obj1, obj2);

        Ray ray = Ray(Vec4(-2, 0, 0, 1), Vec4(1, 0, 0, 0));

        Intersection intersection;

        obj->hitPoint(ray, intersection);
    }
    SECTION("BooleanIntersection") {
        Object *obj1 = new Sphere(Vec4(0, -0.2, 0, 1), 1);
        obj1->setMaterial(MaterialsLibrary::red_plastic());
        //this->addObject(obj);

        Object *obj2 = new Sphere(Vec4(0, 0.2, 0, 1), 1);
        obj2->setMaterial(MaterialsLibrary::bronze());

        Object *obj = new BooleanIntersection(obj1, obj2);

        Ray ray = Ray(Vec4(-2, 0, 0, 1), Vec4(1, 0, 0, 0));

        Intersection intersection;

        obj->hitPoint(ray, intersection);
    }
    SECTION("BooleanDifference") {
        //Boolean Difference
        Object* obj1 = new Box(Vec4(0,0,0,1), Vec4(1,1,1,1));
        obj1->setMaterial(MaterialsLibrary::green_plastic());
        Object* obj2 = new Sphere(Vec4(-1,0,0,0),0.5);
        obj2->setMaterial(MaterialsLibrary::red_plastic());
        Object* obj = new BooleanDifference(obj1,obj2);

        Ray ray = Ray(Vec4(-2, 0, 0, 1), Vec4(1, 0.4, 0, 0));

        Intersection intersection;

        obj->hitPoint(ray, intersection);
    }
}