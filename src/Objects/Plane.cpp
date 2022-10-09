//
// Created by maart on 7/10/2022.
//

#include <Objects/Plane.h>

bool Plane::hitPoint(Ray &ray, Intersection &intersection) {
    //assuming all vectors are normalized
    float denom = Vec4::dot(this->norm,ray.dir());
    if (std::abs(denom) > 1e-6){
        Vec4 oc = this->pos - ray.pos();
        double tHit = Vec4::dot(oc,this->norm) / denom;
        if (tHit >= 0.00001){
            intersection.hit.emplace_back();
            intersection.hit[0].t = tHit;
            intersection.hit[0].obj = this;
            intersection.hit[0].point = ray.at(float(tHit));
            intersection.hit[0].normal = denom < 0?this->norm:-this->norm; //if denom > 0 hit on top of plane, otherwise on the bottom //todo: check if correct!
            return true;
        }

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




