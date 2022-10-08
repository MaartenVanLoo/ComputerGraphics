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
    float t = FLT_MAX;
    Object *obj= nullptr;
    Vec4 point;
};

class Object {
public:
    virtual ~Object();

    virtual bool hitPoint(Ray& ray, Hit &hit1, Hit &hit2) = 0;
    virtual Vec4 normal(Ray& ray) = 0;

    /**
     * Rotate object
     * @param rx Rotation around X-axis, in radians
     * @param ry Rotation around Y-axis, in radians
     * @param rz Rotation around Z-axis, in radians
     */
    void rotate(float rx, float ry, float rz);
    /**
    * Translate object
    * @param rx Translation in X direction
    * @param ry Translation in Y direction
    * @param rz Translation in Z direction
    */
    void translate(float tx, float ty, float tz);
    /**
     * Scale the object
     * @param sx X scaling
     * @param sy Y scaling
     * @param sz Z scaling
     */
    void scale(float sx, float sy, float sz);
    /**
     * Shear the object
     */
    void shear(float hxy, float hxz, float hyz, float hyx, float hzx, float hzy);

    void setMaterial(Material &mtrl);
    Material& getMaterial();
protected:
    Matrix4 transform = Matrix4::identity();
    Matrix4 invtransform = Matrix4::identity();
    Material mtrl;
};


#endif //I_COMPUTERGRAPHICS_OBJECT_H
