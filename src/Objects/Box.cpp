#include "../../include/Ray.h"
#include "../../include/Objects/Box.h"


//
// Created by maart on 30/09/2022.
//

//https://iquilezles.org/articles/intersectors/
//https://www.shadertoy.com/view/ld23DV
bool Box::hitPoint(Ray &ray, float &t1, float &t2) {
    Vec4 m = 1.0/ray.dir();
    Vec4 n = m * ray.pos();

    Vec4 boxSize = this->max - this->min;
    Vec4 k = m.abs()*boxSize;
    Vec4 tStart = - n - k;
    Vec4 tEnd = - n + k;
    t1 = std::max(std::max(tStart.x, tStart.y), tStart.z);
    t2 = std::max(std::max(tEnd.x, tEnd.y), tEnd.z);
    if (t1 > t2 ||t2 < 0) return false; //No intersection
    return true;
}

std::ostream &operator<<(std::ostream &os, const Box &box) {
    os << "Box: {" << "min: " << box.min << " max: " << box.max << "}";
    return os;
}
