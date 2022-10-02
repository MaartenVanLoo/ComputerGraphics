//
// Created by Maarten Van Loo on 2/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_TRANSFORM_H
#define I_COMPUTERGRAPHICS_TRANSFORM_H

#include <Vector.h>
#include <Matrix.h>
class Transform{
    //angle in radians unless specified different

    static Vec4 applyTransform(Matrix4 &T, Vec4& vec);
    //http://scipp.ucsc.edu/~haber/ph216/rotation_12.pdf
    static void rotatef(Matrix4 &T, float angle, float x, float y, float z);
    static void rotatef(Matrix4 &T, float angle, Vec3 axis);
    static void rotatef(Matrix4 &T, float angle, Vec4 axis);
};
#endif //I_COMPUTERGRAPHICS_TRANSFORM_H
