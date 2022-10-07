//
// Created by maart on 7/10/2022.
//

#include <Objects/Plane.h>

bool Plane::hitPoint(Ray &ray, Hit &hit1, Hit &hit2) {
    //assuming all vectors are normalized
    float denom = Vec4::dot(ray.dir(), this->normal);
    if (denom > 1e-6){
        Vec4 oc = ray.pos() - this->pos;
        hit1.t = Vec4::dot(oc,this->normal);
        hit2.t = hit1.t; //only one intersection is possible
        hit1.obj = this;
        hit2.obj = this;
        return (hit1.t >= 0);
    }
    return false;
}

Plane::Plane(Vec4 pos, Vec4 normal) :pos(pos), normal(normal){}

Plane::Plane(float px, float py, float pz, float nx, float ny, float nz) {
    this->pos = Vec4(px, py, pz, 1);
    this->normal = Vec4(nx, ny, nz, 0);
}




