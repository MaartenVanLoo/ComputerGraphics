//
// Created by Maarten Van Loo on 13/10/2022.
//

#include <Objects/BooleanObject.h>
using namespace MRay;
BooleanObject::~BooleanObject() {
    delete this->left;
    delete this->right;

}

BooleanObject::BooleanObject(Object *left, Object *right) : left(left), right(right) {}

