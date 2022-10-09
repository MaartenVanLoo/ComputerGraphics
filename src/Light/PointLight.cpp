//
// Created by maart on 7/10/2022.
//

#include <Light/PointLight.h>
Ray PointLight::getRay(const Vec4 &point) const {
    return Ray(point,this->position - point);
}

float PointLight::getDist(const Vec4 &point) const {
    Vec4 p = this->position - point;
    return Vec4::dot(p,p);
}

Vec4 PointLight::getVec(const Vec4 &point) const {
    return this->position - point;
}

PointLight::PointLight(const Vec4 &position) : position(position) {}

