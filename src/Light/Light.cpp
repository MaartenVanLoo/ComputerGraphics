//
// Created by Maarten Van Loo on 2/10/2022.
//

#include "Light/Light.h"

using namespace MRay;
MRay::Light::~Light() {

}

void Light::setPosition(double px, double py, double pz) {
    //nop for default light
}

void Light::setPosition(const Vec4 &) {
    //nop for default light
}
