//
// Created by maart on 30/09/2022.
//

#include "../../include/Objects/Object.h"

std::ostream &operator<<(std::ostream &os, const Object &object) {
    return os;
}


Object::~Object() {

}

void Object::setMaterial(Material &mtrl) {
    this->mtrl = mtrl;
}

Material& Object::getMaterial() {
    return this->mtrl;
}
