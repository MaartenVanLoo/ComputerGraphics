//
// Created by Maarten Van Loo on 12/10/2022.
//

#include <Textures/Checkerboard.h>
#include <iostream>
using namespace MRay;
Vec3 MRay::Checkboard::compute(float x, float y, float z,float scale) {
    int u = std::abs((int(x/scale)) % 2);
    int v = std::abs((int(y/scale)) % 2);
    int c = u ^ v;
    if ((x < 0) ^ (y < 0)) c ^= 1;
    return Vec3(float(c),float(c),float(c));
}

Checkboard::Checkboard(float sx, float sy, float sz) : sx(sx), sy(sy), sz(sz) {}
