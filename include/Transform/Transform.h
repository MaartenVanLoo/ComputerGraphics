//
// Created by Maarten Van Loo on 2/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_TRANSFORM_H
#define I_COMPUTERGRAPHICS_TRANSFORM_H

#include <Vector.h>
#include <Matrix.h>
class Transform{
public:
    //angle in radians unless specified different

    static Vec4 applyTransform(Matrix4 &T, Vec4& vec);

    //http://scipp.ucsc.edu/~haber/ph216/rotation_12.pdf
    static void rotatef(Matrix4 &T, float angle, float x, float y, float z);
    static void rotatef(Matrix4 &T, float angle, Vec3 axis);
    static void rotatef(Matrix4 &T, float angle, Vec4 axis);

    //https://people.cs.clemson.edu/~dhouse/courses/401/notes/affines-matrices.pdf
    static void translate(Matrix4 &T, float dx, float dy, float dz);
    static void scale(Matrix4 &T, float sx, float sy, float sz);
    static void shear(Matrix4 &T, float hxy, float hxz, float hyz, float hyx, float hzx, float hzy);
    static void rotateX(Matrix4 &T, float angle);
    static void rotateY(Matrix4 &T, float angle);
    static void rotateZ(Matrix4 &T, float angle);
    static void rotate(Matrix4 &T, float Rx, float Ry, float Rz);
};
#endif //I_COMPUTERGRAPHICS_TRANSFORM_H
