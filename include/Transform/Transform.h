//
// Created by Maarten Van Loo on 2/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_TRANSFORM_H
#define I_COMPUTERGRAPHICS_TRANSFORM_H

#include <LinearAlgebra/Vector.h>
#include <LinearAlgebra/Matrix.h>
namespace MRay {

    class Transform {
    public:
        //angle in radians unless specified different
        void applyTransform(const Matrix4 &T, const Matrix4 &invT);

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

        const Matrix4 &getTransform() const;

        const Matrix4 &getInvtransform() const;

    protected:
        Matrix4 transform = Matrix4::identity();
        Matrix4 invtransform = Matrix4::identity();
    };

    class AffineTransform {
    public:
        static Vec4 applyTransform(const Matrix4 &T, const Vec4 &vec);

        //http://scipp.ucsc.edu/~haber/ph216/rotation_12.pdf
        static void rotatef(Matrix4 &T, float angle, float x, float y, float z);

        static void rotatef(Matrix4 &T, float angle, const Vec3 &axis);

        static void rotatef(Matrix4 &T, float angle, const Vec4 &axis);

        static Matrix4 rotatef(float anlge, float x, float y, float z);

        static Matrix4 rotatef(float angle, const Vec3 &axis);

        static Matrix4 rotatef(float angle, const Vec4 &axis);

        //https://people.cs.clemson.edu/~dhouse/courses/401/notes/affines-matrices.pdf => rotation Y and Z are swapped?
        //checked with matlab makehgtform function
        static void translate(Matrix4 &T, float dx, float dy, float dz);

        static Matrix4 translate(float dx, float dy, float ds);

        static void scale(Matrix4 &T, float s);

        static void scale(Matrix4 &T, float sx, float sy, float sz);

        static Matrix4 scale(float s);

        static Matrix4 scale(float sx, float sy, float sz);

        //don't use "shear" as inverse is hard!
        static void shear(Matrix4 &T, float hxy, float hxz, float hyz, float hyx, float hzx, float hzy);

        static Matrix4 shear(float hxy, float hxz, float hyz, float hyx, float hzx, float hzy);

        //https://www.gatevidyalay.com/3d-shearing-in-computer-graphics-definition-examples/
        static void shearX(Matrix4 &T, float shy, float shz);

        static void shearY(Matrix4 &T, float shx, float shz);

        static void shearZ(Matrix4 &T, float shx, float shy);

        static Matrix4 shearX(float shy, float shz);

        static Matrix4 shearY(float shx, float shz);

        static Matrix4 shearZ(float shx, float shy);

        static void rotateX(Matrix4 &T, float angle);

        static void rotateY(Matrix4 &T, float angle);

        static void rotateZ(Matrix4 &T, float angle);

        static Matrix4 rotateX(float angle);

        static Matrix4 rotateY(float angle);

        static Matrix4 rotateZ(float angle);

#pragma endregion
    };
}
#endif //I_COMPUTERGRAPHICS_TRANSFORM_H
