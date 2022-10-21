//
// Created by Maarten Van Loo on 30/09/2022.
//

#include "../../include/Objects/Object.h"
using namespace MRay;

MRay::Object::~Object() {

}

void MRay::Object::setMaterial(Material mtrl) {
    this->mtrl = mtrl;
}

Material& MRay::Object::getMaterial() {
    return this->mtrl;
}

void Object::setTexture(Texture* texture) {
    this->texture = texture;
}

Texture *Object::getTexture() {
    return this->texture;
}

BoundingBox& MRay::Object::getBoundingBox(){
    return this->bb;
}

Vec4 Object::transformNormal(Vec4 normal) const{
    normal = this->invtransform.getTransposed() * normal;
    normal.set<3>(0);
    return normal;
}



