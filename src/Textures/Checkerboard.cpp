//
// Created by Maarten Van Loo on 12/10/2022.
//

#include <Textures/Checkerboard.h>
#include <iostream>
using namespace MRay;
Vec3 MRay::Checkboard::compute(float u, float v, float w) {
    int ui = std::abs((int(u / this->su)) % 2);
    int vi = std::abs((int(v / this->sv)) % 2);
    int c = ui ^ vi;
    if ((u < 0) ^ (v < 0)) c ^= 1;
    return Vec3(float(c),float(c),float(c));
}

Checkboard::Checkboard(float su, float sv, float sw) : su(su), sv(sv), sw(sw) {}
