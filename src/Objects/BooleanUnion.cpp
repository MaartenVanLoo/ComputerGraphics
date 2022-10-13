//
// Created by maart on 13/10/2022.
//

#include <Objects/BooleanUnion.h>

bool MRay::BooleanUnion::hitPoint(MRay::Ray &ray, MRay::Intersection &intersection) {
    if (intersection.leftHit == nullptr) intersection.leftHit = new Intersection();
    if (intersection.rightHit == nullptr) intersection.rightHit = new Intersection();

    intersection.clear();
    intersection.leftHit->clear();  // Do I need this? this is not done in every hitpoint, make sure i don't make errors by clearing here
    intersection.rightHit->clear();  // Do I need this? this is not done in every hitpoint, make sure i don't make errors by clearing here

    this->left->hitPoint(ray,*intersection.leftHit);
    this->right->hitPoint(ray, *intersection.rightHit);

    //sort out the intersection of the union of the points
    if (intersection.leftHit->empty() && intersection.rightHit->empty()) return false; //no hitpoints found

    // merge all hits, sort them by time
    for (auto& hit : intersection.leftHit->hit) intersection.hit.push_back(hit);
    for (auto& hit : intersection.rightHit->hit) intersection.hit.push_back(hit);
    intersection.sort();

    // find out which intersections have to be kept and which are "inside" the object
    // 2 consecutive intersections must be kept when ... TODO: WHEN?

    return false;
}

MRay::Vec4 MRay::BooleanUnion::normal(MRay::Vec4 &point) const {
    return Vec4();
}
