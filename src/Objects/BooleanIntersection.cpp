//
// Created by Maarten Van Loo on 13/10/2022.
//

#include <Objects/BooleanIntersection.h>
#include <algorithm>
using namespace MRay;
bool BooleanIntersection::hitPoint(Ray &ray, Intersection &intersection) {
    if (intersection.leftHit == nullptr) intersection.leftHit = new Intersection();
    if (intersection.rightHit == nullptr) intersection.rightHit = new Intersection();

    intersection.clear();
    intersection.leftHit->clear();  // Do I need this? this is not done in every hitpoint, make sure i don't make errors by clearing here
    intersection.rightHit->clear();  // Do I need this? this is not done in every hitpoint, make sure i don't make errors by clearing here

    this->left->hitPoint(ray,*intersection.leftHit);
    if (intersection.leftHit->empty()) return false; //No hitpoints with this object => not possible to hit the "intersection" of A & B, no need to compute "right hit"
    this->right->hitPoint(ray, *intersection.rightHit);
    if (intersection.rightHit->empty()) return false; //No hitpoints with this object => not possible to hit the "intersection" of A & B, return false;
    //if (intersection.leftHit->empty() || intersection.rightHit->empty())return false; //no hitpoints found when either one of the objects is empty

    //sort out the intersection of the union of the points
    // merge all hits, sort them by time
    for (auto& hit : intersection.leftHit->hit) intersection.hit.push_back(hit);
    for (auto& hit : intersection.rightHit->hit) intersection.hit.push_back(hit);
    intersection.sort();

    // find out which intersections have to be kept and which are "inside" the object
    // a hit must be kept when the state insideLeft || insideRight doesn't change
    //start conditions:
    bool insideLeft = !intersection.leftHit->hit[0].entering; //start condition for left object
    bool insideRight = !intersection.rightHit->hit[0].entering; //start condition for right object
    bool inside =  insideLeft && insideRight; //inside union object = OR operation
    for ( auto hit_itt = intersection.hit.begin(); hit_itt < intersection.hit.end();) {
        if (hit_itt->obj == this->left){
            insideLeft = hit_itt->entering;
        }else{
            //hit.obj == this->right
            insideRight = hit_itt->entering;
        }
        if (inside == (insideLeft && insideRight)){
            //this hit doesn't change the state of the solid and is obsolete: remove
            hit_itt=intersection.hit.erase(hit_itt);
        }else{
            inside = (insideLeft && insideRight);
            hit_itt++;
        }
    }
    return !intersection.hit.empty();
}


Vec4 BooleanIntersection::normal(Vec4 &point) const {
    return Vec4();
}

BooleanIntersection::BooleanIntersection(Object *left, Object *right) : BooleanObject(left, right) {}
