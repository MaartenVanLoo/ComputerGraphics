//
// Created by maart on 12/10/2022.
//

#include <Textures/Checkerboard.h>
#include <iostream>
using namespace MRay;
Vec3 MRay::Checkboard::compute(float x, float y, float z,float scale) {
    int v = (int(x/scale)+int(y/scale)+int(z/scale))%2+1;//;float(std::abs((int(x+y+z))%2));
    return Vec3(v,v,v);
}

Checkboard::Checkboard(float sx, float sy, float sz) : sx(sx), sy(sy), sz(sz) {}
