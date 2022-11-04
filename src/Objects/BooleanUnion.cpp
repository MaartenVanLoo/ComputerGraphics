//
// Created by Maarten Van Loo on 13/10/2022.
//

#include <Objects/BooleanUnion.h>
#include <algorithm>

using namespace MRay;
bool BooleanUnion::hitPoint(Ray &ray, Intersection &intersection, const Options &options) {
    //bounding box test
    if (!this->bb.hit(ray)) return false;

    Ray tr = ray.transform(this->invtransform);

    if (intersection.leftHit == nullptr) intersection.leftHit = new Intersection();
    if (intersection.rightHit == nullptr) intersection.rightHit = new Intersection();

    intersection.clear();
    intersection.leftHit->clear();  // Do I need this? this is not done in every hitpoint, make sure i don't make errors by clearing here
    intersection.rightHit->clear();  // Do I need this? this is not done in every hitpoint, make sure i don't make errors by clearing here

    this->left->hitPoint(tr,*intersection.leftHit, options);
    this->right->hitPoint(tr, *intersection.rightHit, options);

    //sort out the intersection of the union of the points
    if (intersection.leftHit->empty() && intersection.rightHit->empty()) return false; //no hitpoints found

    // merge all hits, sort them by time
    for (auto& hit : intersection.leftHit->hit) intersection.hit.push_back(hit);
    for (auto& hit : intersection.rightHit->hit) intersection.hit.push_back(hit);
    intersection.sort();

    //if 1 of the objects is not intersected the total intersection will be the intersection of the other object
    if (intersection.leftHit->empty() || intersection.rightHit->empty()) {
        for (auto& h: intersection.hit){
            h.normal = this->getTransform() * h.normal;
            h.point = this->getTransform() * h.point;
        }
        return !intersection.hit.empty();
    }


    // find out which intersections have to be kept and which are "inside" the object
    // a hit must be kept when the state insideLeft || insideRight doesn't change
    intersection.leftHit->sort();
    intersection.rightHit->sort();
    bool insideLeft = !intersection.leftHit->hit[0].entering; //start condition for left object
    bool insideRight = !intersection.rightHit->hit[0].entering; //start condition for right object
    bool inside =  insideLeft || insideRight; //inside union object = OR operation
    auto l = intersection.leftHit->hit.begin();
    auto r = intersection.rightHit->hit.begin();
    while (l != intersection.leftHit->hit.end() || r != intersection.rightHit->hit.end()){
        bool isLeft = false;
        if (r==intersection.rightHit->hit.end()) isLeft = true;
        else if (l==intersection.leftHit->hit.end()) isLeft = false;
        else if ( *l < *r) isLeft = true;

        Hit* current;
        if (isLeft){
            insideLeft = l->entering;
            current = &*l;
            l++;
        }else{
            //hit.obj == this->right
            insideRight = r->entering;
            current = &*r;
            r++;
        }
        if (inside == (insideLeft || insideRight)){
            //this hit doesn't change the state of the solid
        }else{
            intersection.hit.push_back(*current);
            inside = (insideLeft && insideRight);
        }
    }
    //Todo: do i need to transpose normals & hitpoints?
    for (auto& h: intersection.hit){
        h.normal = this->getTransform() * h.normal;
        h.point = this->getTransform() * h.point;
    }
    return !intersection.hit.empty();
    /*
    //start conditions:
    bool insideLeft = !intersection.leftHit->hit[0].entering; //start condition for left object
    bool insideRight = !intersection.rightHit->hit[0].entering; //start condition for right object
    bool inside =  insideLeft || insideRight; //inside union object = OR operation
    for ( auto hit_itt = intersection.hit.begin(); hit_itt < intersection.hit.end();) {
        if (hit_itt->obj == this->left){
            insideLeft = hit_itt->entering;
        }else{
            //hit.obj == this->right
            insideRight = hit_itt->entering;
        }
        if (inside == (insideLeft || insideRight)){
            //this hit doesn't change the state of the solid and is obsolete: remove
            hit_itt=intersection.hit.erase(hit_itt);
        }else{
            inside = (insideLeft || insideRight);
            hit_itt++;
        }
    }

    //Todo: do i need to transpose normals & hitpoints?
    for (auto& h: intersection.hit){
        h.normal = this->getTransform() * h.normal;
        h.point = this->getTransform() * h.point;
    }
    return !intersection.hit.empty();

     */
}

Vec4 BooleanUnion::normal(Vec4 &point) const {
    return Vec4();
}

BooleanUnion::BooleanUnion(Object *left, Object *right) : BooleanObject(left, right) {}

void BooleanUnion::computeBoundingBox() {
    this->left->computeBoundingBox();
    this->right->computeBoundingBox();
    this->bb = this->left->getBoundingBox();
    this->bb.add(this->right->getBoundingBox());
    this->bb.transform(this->transform);
}

void BooleanUnion::setMaterial(Material mtrl) {
    Object::setMaterial(mtrl);
    this->left->setMaterial(mtrl);
    this->right->setMaterial(mtrl);
}
