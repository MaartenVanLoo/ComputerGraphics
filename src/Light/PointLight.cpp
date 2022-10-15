//
// Created by Maarten Van Loo on 7/10/2022.
//

#include <Light/PointLight.h>
using namespace MRay;
Ray MRay::PointLight::getRay(const Vec4 &point) const {
    return Ray(point,this->position - point);
}

float MRay::PointLight::getDist(const Vec4 &point) const {
    Vec4 p = this->position - point;
    return Vec4::dot(p,p);
}

Vec4 MRay::PointLight::getVec(const Vec4 &point) const {
    return this->position - point;
}

MRay::PointLight::PointLight(const Vec4 &position) : position(position) {}

std::ostream &MRay::operator<<(std::ostream &os, const PointLight &light) {
    os << " position: " << light.position;
    return os;
}

