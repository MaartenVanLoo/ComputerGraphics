//
// Created by Maarten Van Loo on 7/10/2022.
//

#include <Objects/Plane.h>
using namespace MRay;

const Vec4 Plane::pos = Vec4(0,0,0,1);
const Vec4 Plane::norm = Vec4(0,0,1,0);

bool MRay::Plane::hitPoint(Ray &ray, Intersection &intersection, const Options &options) {
    //bounding box test
    //if (!this->bb.hit(ray)) return false;
    Ray tr = ray.transform(this->invtransform);
    //assuming all vectors are normalized
    float denom = Vec4::dot(Plane::norm,tr.dir());
    if (std::abs(denom) > 0.00001){
        Vec4 oc = Plane::pos - tr.pos();
        double tHit = Vec4::dot(oc,Plane::norm) / denom;
        if (tHit >= 0.00001){
            intersection.hit.emplace_back();
            intersection.hit[0].t = tHit;
            intersection.hit[0].obj = this;
            intersection.hit[0].point = ray.at(float(tHit));
            intersection.hit[0].normal = denom < 0?this->normal(intersection.hit[0].point):-this->normal(intersection.hit[0].point); //if denom > 0 hit on top of plane, otherwise on the bottom //todo: check if correct!
            intersection.hit[0].entering = denom < 0;
            intersection.hit.emplace_back();
            intersection.hit[1].t = tHit;
            intersection.hit[1].obj = this;
            intersection.hit[1].point = intersection.hit[0].point; //same as entry point
            intersection.hit[1].normal = -intersection.hit[0].normal; // opposite of entering node todo: check if correct!
            intersection.hit[1].entering = denom > 0; //ray leaves at same place

            if(!intersection.hit[0].entering) std::swap(intersection.hit[0], intersection.hit[1]); //first enter than leave!
            return true;
        }

    }
    return false;
}

MRay::Plane::Plane(const Vec4 &pos, const Vec4 &normal){
}

MRay::Plane::Plane(float px, float py, float pz, float nx, float ny, float nz) {
}
Plane::Plane() {}

Vec4 MRay::Plane::normal(Vec4 &point) const  {
    if (texture == nullptr){
        return transformNormal(Plane::norm);
    }
    Vec2 n = this->texture->normalMap(point.get<0>(),point.get<1>());
    return transformNormal(Plane::norm + Vec4(n.get<0>(), n.get<1>())/4);
}

void Plane::computeBoundingBox() {
    this->bb = BoundingBox();
    this->bb.transform(this->transform);
}





