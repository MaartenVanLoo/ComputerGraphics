//
// Created by Maarten Van Loo on 2/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_TRANSFORM_H
#define I_COMPUTERGRAPHICS_TRANSFORM_H

#include <LinearAlgebra/Vector.h>
#include <LinearAlgebra/Matrix.h>
class Transform{
public:
    //angle in radians unless specified different

    static Vec4 applyTransform(const Matrix4 &T, const Vec4& vec);

    //http://scipp.ucsc.edu/~haber/ph216/rotation_12.pdf
    static void rotatef(Matrix4 &T, float angle, float x, float y, float z);
    static void rotatef(Matrix4 &T, float angle, const Vec3 &axis);
    static void rotatef(Matrix4 &T, float angle, const Vec4 &axis);

    //https://people.cs.clemson.edu/~dhouse/courses/401/notes/affines-matrices.pdf => rotation Y and Z are swapped?
    //checked with matlab makehgtform function
    static void translate(Matrix4 &T, float dx, float dy, float dz);
    static void scale(Matrix4 &T, float s);
    static void scale(Matrix4 &T, float sx, float sy, float sz);
    //don't use "shear" as inverse is hard!
    static void shear(Matrix4 &T, float hxy, float hxz, float hyz, float hyx, float hzx, float hzy);
    //https://www.gatevidyalay.com/3d-shearing-in-computer-graphics-definition-examples/
    static void shearX(Matrix4 &T, float shy, float shz);
    static void shearY(Matrix4 &T, float shx, float shz);
    static void shearZ(Matrix4 &T, float shx, float shy);
    static void rotateX(Matrix4 &T, float angle);
    static void rotateY(Matrix4 &T, float angle);
    static void rotateZ(Matrix4 &T, float angle);
};
#endif //I_COMPUTERGRAPHICS_TRANSFORM_H
