//
// Created by Maarten Van Loo on 2/10/2022.
//

#include "../../include/Transform/Transform.h"

Vec4 Transform::applyTransform(const Matrix4 &T, const Vec4 &vec) {
    //T = 4x4 matrix!
    return T*vec;
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

    T.set<0>(Vec4(cosa + x * x *(1 - cosa),   x*y*(1-cosa)-z*sina,    x*z*(1-cosa) + y*sina , 0));
    T.set<1>(Vec4(x*y*(1-cosa)+z*sina,       cosa + y*y*(1-cosa),    y*z*(1-cosa) - x*sina , 0 ));
    T.set<2>(Vec4(x*z*(1-cosa)-y*sina,       y*z*(1-cosa) + x*sina,  cosa + z*z * (1-cosa) , 0 ));
    T.set<3>(Vec4(0,                         0,                      0,                      1 ));
}

void Transform::rotatef(Matrix4 &T, float angle,const Vec3 &axis) {
    //T must be a 4x4 matrix, each vec4 is a row
    float invnorm = 1.0f/std::sqrt(Vec3::dot(axis,axis));
    float cosa = std::cos(angle);
    float sina = std::sin(angle);
    float x = axis.get(0)*invnorm;
    float y = axis.get(1)*invnorm;
    float z = axis.get(2)*invnorm;
    T.set<0>(Vec4(cosa + x * x *(1 - cosa),   x*y*(1-cosa)-z*sina,    x*z*(1-cosa) + y*sina , 0));
    T.set<1>(Vec4(x*y*(1-cosa)+z*sina,       cosa + y*y*(1-cosa),    y*z*(1-cosa) - x*sina , 0 ));
    T.set<2>(Vec4(x*z*(1-cosa)-y*sina,       y*z*(1-cosa) + x*sina,  cosa + z*z * (1-cosa) , 0 ));
    T.set<3>(Vec4(0,                         0,                      0,                      1 ));
}

void Transform::rotatef(Matrix4 &T, float angle, const Vec4 &axis) {
    //T must be a 4x4 matrix, each vec4 is a row
    float invnorm = 1.0f/std::sqrt(Vec4::dot(axis,axis));
    float cosa = std::cos(angle);
    float sina = std::sin(angle);
    float x = axis.get(0) * invnorm;
    float y = axis.get(1) * invnorm;
    float z = axis.get(2) * invnorm;
    T.set<0>(Vec4(cosa + x * x *(1 - cosa),   x*y*(1-cosa)-z*sina,    x*z*(1-cosa) + y*sina , 0));
    T.set<1>(Vec4(x*y*(1-cosa)+z*sina,       cosa + y*y*(1-cosa),    y*z*(1-cosa) - x*sina , 0 ));
    T.set<2>(Vec4(x*z*(1-cosa)-y*sina,       y*z*(1-cosa) + x*sina,  cosa + z*z * (1-cosa) , 0 ));
    T.set<3>(Vec4(0,                         0,                      0,                      1 ));
}

void Transform::translate(Matrix4 &T, float dx, float dy, float dz) {
    //T must be a 4x4 matrix, each vec4 is a row
    T.set<0>(Vec4(1,0,0,dx));
    T.set<1>(Vec4(0,1,0,dy));
    T.set<2>(Vec4(0,0,1,dz));
    T.set<3>(Vec4(0,0,0,1));
}

void Transform::scale(Matrix4 &T, float s) {
    //T must be a 4x4 matrix, each vec4 is a row
    T.set<0>(Vec4( s,0,0,0));
    T.set<1>(Vec4( 0,   s,0,0));
    T.set<2>(Vec4( 0,0 ,  s,0));
    T.set<3>(Vec4( 0,0,0,1));
}

void Transform::scale(Matrix4 &T, float sx, float sy, float sz) {
    //T must be a 4x4 matrix, each vec4 is a row
    T.set<0>(Vec4(sx,0,0,0));
    T.set<1>(Vec4( 0,  sy,0,0));
    T.set<2>(Vec4( 0,0,  sz,0));
    T.set<3>(Vec4( 0,0,0,1));
}

//https://en.wikipedia.org/wiki/Shear_matrix
void Transform::shear(Matrix4 &T, float hxy, float hxz, float hyz, float hyx, float hzx, float hzy) {
    //T must be a 4x4 matrix, each vec4 is a row
    T.set<0>(Vec4(1, hxy, hxz,0));
    T.set<1>(Vec4( hyx,1, hyz,0));
    T.set<2>(Vec4( hzx, hzy,1,0));
    T.set<3>(Vec4(0,0,0,1));
}
void Transform::shearX(Matrix4 &T, float shy, float shz) {
    T.set<0>(Vec4(1, 0, 0,0));
    T.set<1>(Vec4( shy,1, 0,0));
    T.set<2>(Vec4( shz, 0,1,0));
    T.set<3>(Vec4(0,0,0,1));
}
void Transform::shearY(Matrix4 &T, float shx, float shz) {
    T.set<0>(Vec4(1, shx, 0,0));
    T.set<1>(Vec4( 0,1, 0,0));
    T.set<2>(Vec4( 0, shz,1,0));
    T.set<3>(Vec4(0,0,0,1));
}

void Transform::shearZ(Matrix4 &T, float shx, float shy) {
    T.set<0>(Vec4(1, 0, shx,0));
    T.set<1>(Vec4( 0,1, shy,0));
    T.set<2>(Vec4( 0, 0,1,0));
    T.set<3>(Vec4(0,0,0,1));
}

void Transform::rotateX(Matrix4 &T, float angle) {
    float cosa = std::cos(angle);
    float sina = std::sin(angle);
    T.set<0>(Vec4( 1, 0,  0,0));
    T.set<1>(Vec4( 0, cosa, -sina,0));
    T.set<2>(Vec4( 0, sina,  cosa,0));
    T.set<3>(Vec4( 0, 0,  0,1));
}
void Transform::rotateY(Matrix4 &T, float angle) {
    float cosa = std::cos(angle);
    float sina = std::sin(angle);
    T.set<0>(Vec4( cosa, -sina,0,0));
    T.set<1>(Vec4( sina,  cosa,0,0));
    T.set<2>(Vec4(    0,  0,1,0));
    T.set<3>(Vec4(    0,  0,0,1));
}
void Transform::rotateZ(Matrix4 &T, float angle) {
    float cosa = std::cos(angle);
    float sina = std::sin(angle);
    T.set<0>(Vec4(  cosa, 0, sina,0));
    T.set<1>(Vec4(     0, 1, 0,0));
    T.set<2>(Vec4( -sina, 0, cosa,0));
    T.set<3>(Vec4(     0, 0, 0,1));

}







