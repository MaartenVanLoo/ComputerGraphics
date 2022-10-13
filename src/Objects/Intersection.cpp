//
// Created by maart on 12/10/2022.
//
#include <Objects/Intersection.h>

using namespace MRay;
void Intersection::clear() {
    this->hit.clear();
}

bool Intersection::empty() {
    return this->hit.empty();
}

Intersection::~Intersection() {
    delete this->rightHit;
    delete this->leftHit;
}

void Intersection::sort() {
    std::sort(this->hit.begin(), this->hit.end());
}
