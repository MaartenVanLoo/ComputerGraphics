//
// Created by Maarten Van Loo on 16/10/2022.
//

#include <Objects/BoundingBox.h>
#include <vector>

MRay::BoundingBox::BoundingBox() {

}

MRay::BoundingBox::BoundingBox(const MRay::Vec3 &min, const MRay::Vec3 &max) {

}

void MRay::BoundingBox::transform(const MRay::Matrix4 &transform) {
    //generate corner points:
    Vec4 p1 = Vec4(min.get<_X>(),min.get<_Y>(),min.get<_Z>(),0);
    Vec4 p2 = Vec4(min.get<_X>(),min.get<_Y>(),max.get<_Z>(),0);
    Vec4 p3 = Vec4(min.get<_X>(),max.get<_Y>(),min.get<_Z>(),0);
    Vec4 p4 = Vec4(min.get<_X>(),max.get<_Y>(),max.get<_Z>(),0);
    Vec4 p5 = Vec4(max.get<_X>(),min.get<_Y>(),min.get<_Z>(),0);
    Vec4 p6 = Vec4(max.get<_X>(),min.get<_Y>(),max.get<_Z>(),0);
    Vec4 p7 = Vec4(max.get<_X>(),max.get<_Y>(),min.get<_Z>(),0);
    Vec4 p8 = Vec4(max.get<_X>(),max.get<_Y>(),max.get<_Z>(),0);

    //transform
    p1 = transform * p1;
    p2 = transform * p2;
    p3 = transform * p3;
    p4 = transform * p4;
    p5 = transform * p5;
    p6 = transform * p6;
    p7 = transform * p7;
    p8 = transform * p8;

    //get bounding values:
    this->max.set<_X>(std::max(std::max(std::max(p1.get<_X>(),p2.get<_X>()),std::max(p3.get<_X>(),p4.get<_X>())),
                           std::max(std::max(p5.get<_X>(),p6.get<_X>()),std::max(p7.get<_X>(),p8.get<_X>()))));
    this->max.set<_Y>(std::max(std::max(std::max(p1.get<_Y>(),p2.get<_Y>()),std::max(p3.get<_Y>(),p4.get<_Y>())),
                               std::max(std::max(p5.get<_Y>(),p6.get<_Y>()),std::max(p7.get<_Y>(),p8.get<_Y>()))));
    this->max.set<_Z>(std::max(std::max(std::max(p1.get<_Z>(),p2.get<_Z>()),std::max(p3.get<_Z>(),p4.get<_Z>())),
                               std::max(std::max(p5.get<_Z>(),p6.get<_Z>()),std::max(p7.get<_Z>(),p8.get<_Z>()))));

    this->min.set<_X>(std::min(std::min(std::min(p1.get<_X>(),p2.get<_X>()),std::min(p3.get<_X>(),p4.get<_X>())),
                               std::min(std::min(p5.get<_X>(),p6.get<_X>()),std::min(p7.get<_X>(),p8.get<_X>()))));
    this->min.set<_Y>(std::min(std::min(std::min(p1.get<_Y>(),p2.get<_Y>()),std::min(p3.get<_Y>(),p4.get<_Y>())),
                               std::min(std::min(p5.get<_Y>(),p6.get<_Y>()),std::min(p7.get<_Y>(),p8.get<_Y>()))));
    this->min.set<_Z>(std::min(std::min(std::min(p1.get<_Z>(),p2.get<_Z>()),std::min(p3.get<_Z>(),p4.get<_Z>())),
                               std::min(std::min(p5.get<_Z>(),p6.get<_Z>()),std::min(p7.get<_Z>(),p8.get<_Z>()))));

}

void MRay::BoundingBox::add(const MRay::BoundingBox &bb) {
    this->min = Vec4::min(this->min, bb.min);
    this->max = Vec4::max(this->max, bb.max);
}

bool MRay::BoundingBox::hit(const MRay::Ray &ray) {
    Vec4 invDir = 1/ray.dir();  //todo store this in ray, don't recompute every time
    Vec4 t0 = (this->min - ray.pos()) * invDir;
    Vec4 t1 = (this->max - ray.pos()) * invDir;
    Vec4 tmin = Vec4::min(t0,t1);
    Vec4 tmax = Vec4::max(t0,t1);

    return tmin.max() <= tmax.min();
}

