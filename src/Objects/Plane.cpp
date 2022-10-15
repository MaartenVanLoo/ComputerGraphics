//
// Created by Maarten Van Loo on 7/10/2022.
//

#include <Objects/Plane.h>
using namespace MRay;
bool MRay::Plane::hitPoint(Ray &ray, Intersection &intersection) {
    //assuming all vectors are normalized
    float denom = Vec4::dot(this->norm,ray.dir());
    if (std::abs(denom) > 0.00001){
        Vec4 oc = this->pos - ray.pos();
        double tHit = Vec4::dot(oc,this->norm) / denom;
        if (tHit >= 0.00001){
            intersection.hit.emplace_back();
            intersection.hit[0].t = tHit;
            intersection.hit[0].obj = this;
            intersection.hit[0].point = ray.at(float(tHit));
            intersection.hit[0].normal = denom < 0?this->norm:-this->norm; //if denom > 0 hit on top of plane, otherwise on the bottom //todo: check if correct!
            intersection.hit[0].entering = denom > 0;
            intersection.hit.emplace_back();
            intersection.hit[1].t = tHit;
            intersection.hit[1].obj = this;
            intersection.hit[1].point = intersection.hit[0].point; //same as entry point
            intersection.hit[1].normal = -intersection.hit[0].normal; // opposite of entering node todo: check if correct!
            intersection.hit[1].entering = denom < 0; //ray leaves at same place
            return true;
        }

    }
    return false;
}

MRay::Plane::Plane(const Vec4 &pos, const Vec4 &normal) :pos(pos), norm(normal){}

MRay::Plane::Plane(float px, float py, float pz, float nx, float ny, float nz) {
    this->pos = Vec4(px, py, pz, 1);
    this->norm = Vec4(nx, ny, nz, 0);
}

Vec4 MRay::Plane::normal(Vec4 &point) const  {
    return this->norm;
}




