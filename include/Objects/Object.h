//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_OBJECT_H
#define I_COMPUTERGRAPHICS_OBJECT_H

#include "../Ray.h"
#include "LinearAlgebra/Vector.h"
#include <cmath>
#include <algorithm>
#include <ostream>
#include <Materials/Material.h>
#include "Camera/CameraUtils.h"
#include "Transform/Transform.h"

class Object;
struct Hit {
    double t = DBL_MAX;
    Object *obj= nullptr;
    Vec4 point;
};

class Object : public Transform{
public:
    virtual ~Object();

    virtual bool hitPoint(Ray& ray, Hit &hit1, Hit &hit2) = 0;
    virtual Vec4 normal(Ray& ray) = 0;

    void setMaterial(Material &mtrl);
    Material& getMaterial();
protected:

    Material mtrl;
};


#endif //I_COMPUTERGRAPHICS_OBJECT_H
