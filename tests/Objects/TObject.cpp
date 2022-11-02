//
// Created by Maarten Van Loo on 7/10/2022.
//

#include <catch2/catch_all.hpp>
#include <iostream>
#include <Objects/Object.h>
using namespace MRay;
class TObject : public Object{
public:
    bool hitPoint(Ray &ray,Intersection &intersect, const Options& options) override {
        return false;
    }

    Vec4 normal(Vec4 &point) const {
        return Vec4();
    }
    Matrix4 getTransform(){
        return this->transform;
    }
    Matrix4 getInvTransform(){
        return this->invtransform;
    }
};
TEST_CASE("tObject") {
    TObject object;
    Matrix4 result;
    SECTION("rotate"){
        object.rotate(1,2,3);
        result = object.getTransform() * object.getInvTransform(); //should be identity matrix
        for (int i = 0; i < 16; i++){
            if (i%4 == i/4) CHECK(std::abs(result.get(i%4,i/4) -1) < 5e-6);
            else CHECK(std::abs(result.get(i%4,i/4)) < 5e-6);
        }
    }
    SECTION("translate"){
        object.translate(1,2,3);
        result = object.getTransform() * object.getInvTransform(); //should be identity matrix
        for (int i = 0; i < 16; i++){
            if (i%4 == i/4) CHECK(std::abs(result.get(i%4,i/4) -1) < 5e-6);
            else CHECK(std::abs(result.get(i%4,i/4)) < 5e-6);
        }
    }
    SECTION("scale"){
        object.scale(1,2,3);
        result = object.getTransform() * object.getInvTransform(); //should be identity matrix
        for (int i = 0; i < 16; i++){
            if (i%4 == i/4) CHECK(std::abs(result.get(i%4,i/4) -1) < 5e-6);
            else CHECK(std::abs(result.get(i%4,i/4)) < 5e-6);
        }
    }
    SECTION("shear"){
        object.shear(1,2,3,4,5,6);
        result = object.getTransform() * object.getInvTransform(); //should be identity matrix
        for (int i = 0; i < 16; i++){
            if (i%4 == i/4) CHECK(std::abs(result.get(i%4,i/4) -1) < 5e-6);
            else CHECK(std::abs(result.get(i%4,i/4)) < 5e-6);
        }
    }
}