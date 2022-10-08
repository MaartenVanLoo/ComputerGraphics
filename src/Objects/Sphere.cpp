//
// Created by maart on 30/09/2022.
//

#include <iostream>
#include "../../include/Objects/Sphere.h"

//https://iquilezles.org/articles/intersectors/
//https://www.shadertoy.com/view/4d2XWV
//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
bool Sphere::hitPoint(Ray &ray, Hit &hit1, Hit &hit2) {

    Ray tr = ray.transform(this->invtransform);

    Vec4 oc = tr.pos()-Vec4(0,0,0,1);

    float a = Vec4::dot(tr.dir(),tr.dir());
    float b = Vec4::dot(oc,tr.dir());
    float c = Vec4::dot(oc,oc)-1;
    float discrim = b*b-a*c;
    if (discrim < 0.0){
        return false;
    }
    float discRoot = sqrt(discrim);
    hit1.t = (-b-discRoot)/a;
    hit2.t = (-b+discRoot)/a;

    int num = 0;
    if (hit1.t > 0){
        hit1.obj = this;
        hit1.point = this->transform * tr.at(hit1.t);
        num++;
    }
    if (hit2.t > 0){
        hit2.obj = this;
        hit2.point = tr.at(hit2.t);
        num++;
    }

    return num > 0;
}

std::ostream &operator<<(std::ostream &os, const Sphere &sphere) {
    os << "Sphere: {" << " position: " << sphere.position << "}";
    return os;
}

Sphere::Sphere(const Vec4 &position) {
    this->translate(position.get<0>(),position.get<1>(),position.get<2>());
}

Sphere::Sphere(const Vec4 &position, float radius){
    this->scale(radius,radius,radius);
    this->translate(position.get<0>(),position.get<1>(),position.get<2>());
}

Vec4 Sphere::normal(Vec4 point) {
    return point;
}

Vec4 Sphere::normal(Ray &ray) {
    return Vec4();
}


