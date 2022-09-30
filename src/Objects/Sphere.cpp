//
// Created by maart on 30/09/2022.
//

#include "../../include/Objects/Sphere.h"

//https://iquilezles.org/articles/intersectors/
//https://www.shadertoy.com/view/4d2XWV
bool Sphere::hitPoint(Ray &ray, float &t1, float&t2) {
    Vec4 oc = ray.pos() - this->position; //=transformation!
    float b = Vec4::dot(oc,ray.dir());
    float c = Vec4::dot(oc,oc) - this->radius * this->radius;
    float h = b*b - c;
    if (h<0.0) {
        t1 = -1.0;
        t2 = -1.0;
        return false;
    }
    h = std::sqrt(h); //compute once
    t1 = -b - h;
    t2 = -b + h;

    if (t1 < 0 && t2 < 0) return false; //intersect at opposite side
    // if initial point inside sphere => 1 negative time and 1 positive time
    // => only interested in positive time. t1 always smaller than t2.
    if (t1 < 0) t1 = t2;

    return true;
}

std::ostream &operator<<(std::ostream &os, const Sphere &sphere) {
    os << "Sphere: {" << " position: " << sphere.position << " radius: " << sphere.radius << "}";
    return os;
}

Sphere::Sphere(const Vec4 &position, float radius) : position(position), radius(radius) {}

Vec4 Sphere::normal(Vec4 point) {
    return point - this->position;
}
