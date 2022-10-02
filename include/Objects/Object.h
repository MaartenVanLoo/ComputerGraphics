//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_OBJECT_H
#define I_COMPUTERGRAPHICS_OBJECT_H

#include "../Ray.h"
#include "../Vector.h"
#include <cmath>
#include <algorithm>
#include <ostream>
class Object {
public:
    virtual bool hitPoint(Ray& ray, float &t1, float &t2) = 0;
    virtual Vec4 normal(Ray& ray) = 0;
};


#endif //I_COMPUTERGRAPHICS_OBJECT_H
