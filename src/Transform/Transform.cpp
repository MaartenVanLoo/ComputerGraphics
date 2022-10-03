//
// Created by Maarten Van Loo on 2/10/2022.
//

#include "../../include/Transform/Transform.h"

Vec4 Transform::applyTransform(Matrix4 &T, Vec4 &vec) {
    //T = 4x4 matrix!
    Vec4 result;
    for (int row = 0; row < 4; row++){
        result[row] = Vec4::sum(T[row]*vec);
    }
    return result;
}


void Transform::rotatef(Matrix4 &T, float angle, float x, float y, float z) {
    //T must be a 4x4 matrix, each vec4 is a row
    //normalize x y z
    float invnorm = 1.0f/sqrt(x*x+y*y+z*z);
    x *= invnorm;
    y *= invnorm;
    z *= invnorm;
    //precompute  cosine and sine
    float cosa = std::cos(angle);
    float sina = std::sin(angle);

    T[0] = Vec4(cosa + x * x *(1 - cosa),   x*y*(1-cosa)-z*sina,    x*z*(1-cosa) + y*sina , 0);
    T[1] = Vec4(x*y*(1-cosa)+z*sina,       cosa + y*y*(1-cosa),    y*z*(1-cosa) - x*sina , 0 );
    T[2] = Vec4(x*z*(1-cosa)-y*sina,       y*z*(1-cosa) + x*sina,  cosa + z*z * (1-cosa) , 0 );
    T[3] = Vec4(0,                         0,                      0,                      1 );
}

void Transform::rotatef(Matrix4 &T, float angle, Vec3 axis) {
    //T must be a 4x4 matrix, each vec4 is a row
    float invnorm = 1.0f/std::sqrt(Vec3::dot(axis,axis));
    float cosa = std::cos(angle);
    float sina = std::sin(angle);
    float x = axis[0]*invnorm;
    float y = axis[1]*invnorm;
    float z = axis[2]*invnorm;
    T[0] = Vec4(cosa + x * x *(1 - cosa),   x*y*(1-cosa)-z*sina,    x*z*(1-cosa) + y*sina , 0);
    T[1] = Vec4(x*y*(1-cosa)+z*sina,       cosa + y*y*(1-cosa),    y*z*(1-cosa) - x*sina , 0 );
    T[2] = Vec4(x*z*(1-cosa)-y*sina,       y*z*(1-cosa) + x*sina,  cosa + z*z * (1-cosa) , 0 );
    T[3] = Vec4(0,                         0,                      0,                      1 );
}

void Transform::rotatef(Matrix4 &T, float angle, Vec4 axis) {
    //T must be a 4x4 matrix, each vec4 is a row
    float invnorm = 1.0f/std::sqrt(Vec4::dot(axis,axis));
    float cosa = std::cos(angle);
    float sina = std::sin(angle);
    float x = axis[0] * invnorm;
    float y = axis[1] * invnorm;
    float z = axis[2] * invnorm;
    T[0] = Vec4(cosa + x * x *(1 - cosa),   x*y*(1-cosa)-z*sina,    x*z*(1-cosa) + y*sina , 0);
    T[1] = Vec4(x*y*(1-cosa)+z*sina,       cosa + y*y*(1-cosa),    y*z*(1-cosa) - x*sina , 0 );
    T[2] = Vec4(x*z*(1-cosa)-y*sina,       y*z*(1-cosa) + x*sina,  cosa + z*z * (1-cosa) , 0 );
    T[3] = Vec4(0,                         0,                      0,                      1 );
}

void Transform::translate(Matrix4 &T, float dx, float dy, float dz) {
    //T must be a 4x4 matrix, each vec4 is a row
    T[0] = Vec4(1,0,0,dx);
    T[1] = Vec4(0,1,0,dy);
    T[2] = Vec4(0,0,1,dz);
    T[3] = Vec4(0,0,0,1);
}

void Transform::scale(Matrix4 &T, float s) {
    //T must be a 4x4 matrix, each vec4 is a row
    T[0] = Vec4( s,0,0,0);
    T[1] = Vec4( 0,   s,0,0);
    T[2] = Vec4( 0,0 ,  s,0);
    T[3] = Vec4( 0,0,0,1);
}

void Transform::scale(Matrix4 &T, float sx, float sy, float sz) {
    //T must be a 4x4 matrix, each vec4 is a row
    T[0] = Vec4(sx,0,0,0);
    T[1] = Vec4( 0,  sy,0,0);
    T[2] = Vec4( 0,0,  sz,0);
    T[3] = Vec4( 0,0,0,1);
}

void Transform::shear(Matrix4 &T, float hxy, float hxz, float hyz, float hyx, float hzx, float hzy) {
    //T must be a 4x4 matrix, each vec4 is a row
    T[0] = Vec4(  1, hxy, hxz,0);
    T[1] = Vec4(hyx,1, hyz,0);
    T[2] = Vec4(hzx, hzy,1,0);
    T[3] = Vec4(  0,0,0,1);
}

void Transform::rotateX(Matrix4 &T, float angle) {
    float cosa = std::cos(angle);
    float sina = std::sin(angle);
    T[0] = Vec4( 1, 0,  0,0);
    T[1] = Vec4( 0, cosa, -sina,0);
    T[2] = Vec4( 0, sina,  cosa,0);
    T[3] = Vec4( 0, 0,  0,1);
}
void Transform::rotateY(Matrix4 &T, float angle) {
    float cosa = std::cos(angle);
    float sina = std::sin(angle);
    T[0] = Vec4( cosa, -sina,0,0);
    T[1] = Vec4( sina,  cosa,0,0);
    T[2] = Vec4(    0,  0,1,0);
    T[3] = Vec4(    0,  0,0,1);
}
void Transform::rotateZ(Matrix4 &T, float angle) {
    float cosa = std::cos(angle);
    float sina = std::sin(angle);
    T[0] = Vec4(  cosa, 0, sina,0);
    T[1] = Vec4(     0, 1, 0,0);
    T[2] = Vec4( -sina, 0, cosa,0);
    T[3] = Vec4(     0, 0, 0,1);

}



