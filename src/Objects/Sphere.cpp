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
    //bounding box test
    if (!this->bb.hit(ray)) return false;

    Ray tr = ray.transform(this->invtransform);
    Vec4 oc = tr.pos()-Vec4(0,0,0,1);

    double a = Vec4::dot(tr.dir(),tr.dir());
    double b = Vec4::dot(oc,tr.dir());
    double c = Vec4::dot(oc,oc)-1;
    double discrim = b*b-a*c;
    if (discrim < -0.0001){
        return false;
    }
    double discRoot = sqrt(std::fabs(discrim));
    auto hit1 = double((-b-discRoot)/a);
    auto hit2 = double((-b+discRoot)/a);

    int num = 0;
    if (hit1 > 0.0001){
        intersection.hit.emplace_back();
        intersection.hit[0].t = hit1;
        intersection.hit[0].obj = this;
        intersection.hit[0].point = this->transform * tr.at(hit1);
        intersection.hit[0].normal = this->getTransform() * normal(tr.at(hit1));
        intersection.hit[0].entering = true;
        num++;
    }
    if (hit2 > 0.0001){
        intersection.hit.emplace_back();
        intersection.hit[num].t = hit2;
        intersection.hit[num].obj = this;
        intersection.hit[num].point = this->transform * tr.at(hit2);
        intersection.hit[num].normal = this->getTransform() * normal(tr.at(hit2));
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

Vec4 MRay::Sphere::normal(const Vec4 &point) const{
    Vec4 n = point;
    n.set<3>(0); //set last value to zero, indicate 'vector' instead of point;
    return n;
}

void Sphere::computeBoundingBox() {
    this->bb = BoundingBox(Vec3(-1.1,-1.1,-1.1),Vec3(1.1,1.1,1.1)); //additional margin to avoid precision errors
    this->bb.transform(this->transform);
}




