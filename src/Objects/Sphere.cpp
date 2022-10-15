//
// Created by Maarten Van Loo on 30/09/2022.
//

#include <iostream>
#include "../../include/Objects/Sphere.h"
using namespace MRay;
//https://iquilezles.org/articles/intersectors/
//https://www.shadertoy.com/view/4d2XWV
//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
bool MRay::Sphere::hitPoint(Ray &ray, Intersection& intersection) {
    Ray tr = ray.transform(this->invtransform);
    Vec4 oc = tr.pos()-Vec4(0,0,0,1);

    double a = Vec4::dot(tr.dir(),tr.dir());
    double b = Vec4::dot(oc,tr.dir());
    double c = Vec4::dot(oc,oc)-1;
    double discrim = b*b-a*c;
    if (discrim < -0.00001){
        return false;
    }
    double discRoot = sqrt(std::fabs(discrim));
    auto hit1 = float((-b-discRoot)/a);
    auto hit2 = float((-b+discRoot)/a);

    int num = 0;
    if (hit1 > 0.00001){
        intersection.hit.emplace_back();
        intersection.hit[0].t = hit1;
        intersection.hit[0].obj = this;
        intersection.hit[0].point = this->transform * tr.at(hit1);
        intersection.hit[0].normal = tr.at(hit1);
        intersection.hit[0].entering = true;
        num++;
    }
    if (hit2 > 0.00001){
        intersection.hit.emplace_back();
        intersection.hit[num].t = hit2;
        intersection.hit[num].obj = this;
        intersection.hit[num].point = this->transform * tr.at(hit2);
        intersection.hit[num].normal = tr.at(hit2);
        intersection.hit[num].entering = false;

        num++;
    }
    //std::cout << "t1: " << hit1 << "\tt2:" << hit2 << "\n";
    return num > 0;
}

std::ostream &MRay::operator<<(std::ostream &os, const Sphere &sphere) {
    os << "Sphere: {" << " position: " << sphere.position << "}";
    return os;
}

MRay::Sphere::Sphere(const Vec4 &position) {
    this->translate(position.get<0>(),position.get<1>(),position.get<2>());
}

MRay::Sphere::Sphere(const Vec4 &position, float radius){
    this->scale(radius,radius,radius);
    this->translate(position.get<0>(),position.get<1>(),position.get<2>());
}

Vec4 MRay::Sphere::normal(Vec4 &point) const{
    const Vec4& n = point;
    return n;
}




