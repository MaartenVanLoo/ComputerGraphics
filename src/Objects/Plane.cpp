//
// Created by maart on 7/10/2022.
//

#include <Objects/Plane.h>

bool Plane::hitPoint(Ray &ray, Hit &hit1, Hit &hit2) {
    //assuming all vectors are normalized
    float denom = Vec4::dot(this->norm,ray.dir());
    if (std::abs(denom) > 1e-6){
        Vec4 oc = this->pos - ray.pos();
        hit1.t = Vec4::dot(oc,this->norm) / denom;
        hit2.t = hit1.t; //only one intersection is possible
        hit1.obj = this;
        hit2.obj = this;
        return (hit1.t >= 0);
    }
    return false;
}

Plane::Plane(const Vec4 &pos, const Vec4 &normal) :pos(pos), norm(normal){}

Plane::Plane(float px, float py, float pz, float nx, float ny, float nz) {
    this->pos = Vec4(px, py, pz, 1);
    this->norm = Vec4(nx, ny, nz, 0);
}

Vec4 Plane::normal(Ray &ray) {
    return this->norm;
}




