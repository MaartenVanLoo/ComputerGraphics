//
// Created by Maarten Van Loo on 2/10/2022.
//

#include "../../include/Transform/Transform.h"

using namespace MRay;
#pragma region Transform
void MRay::Transform::applyTransform(const Matrix4 &T, const Matrix4 &invT){
    this->transform = T * this->transform;
    this->invtransform = this->invtransform * invT;
}

void MRay::Transform::rotate(float rx, float ry, float rz) {
    Matrix4 Tx,Ty,Tz;
      MRay::AffineTransform::rotateX(Tx, rx);
      MRay::AffineTransform::rotateY(Ty, ry);
      MRay::AffineTransform::rotateZ(Tz, rz);
    this->transform = Tx * this->transform;
    this->transform = Ty * this->transform;
    this->transform = Tz * this->transform;
    //inverse transform
      MRay::AffineTransform::rotateX(Tx, -rx);
      MRay::AffineTransform::rotateY(Ty, -ry);
      MRay::AffineTransform::rotateZ(Tz, -rz);
    this->invtransform = this->invtransform * Tx; //reverse order of transform!
    this->invtransform = this->invtransform * Ty;
    this->invtransform = this->invtransform * Tz;
}

void MRay::Transform::translate(float tx, float ty, float tz) {
    Matrix4 T;
      MRay::AffineTransform::translate(T, tx, ty, tz);
    this->transform = T * this->transform;
    //inverse transform
      MRay::AffineTransform::translate(T, -tx, -ty, -tz);
    this->invtransform = this->invtransform * T; //reverse order of transform!
}

void MRay::Transform::scale(float sx, float sy, float sz) {
    Matrix4 T;
      MRay::AffineTransform::scale(T, sx, sy, sz);
    this->transform = T * this->transform;
      MRay::AffineTransform::scale(T, 1 / sx, 1 / sy, 1 / sz);
    this->invtransform = this->invtransform * T; //reverse order of transform!
}

void MRay::Transform::shear(float shXy, float shXz, float shYx, float shYz, float shZx, float shZy ) {
    Matrix4 Tx,Ty,Tz;
      MRay::AffineTransform::shearX(Tx, shXy, shXz);
      MRay::AffineTransform::shearY(Ty, shYx, shYz);
      MRay::AffineTransform::shearZ(Tz, shZx, shZy);
    this->transform = Tx * this->transform;
    this->transform = Ty * this->transform;
    this->transform = Tz * this->transform;
    //inverse transform
      MRay::AffineTransform::shearX(Tx, -shXy, -shXz);
      MRay::AffineTransform::shearY(Ty, -shYx, -shYz);
      MRay::AffineTransform::shearZ(Tz, -shZx, -shZy);
    this->invtransform = this->invtransform * Tx; //reverse order of transform!
    this->invtransform = this->invtransform * Ty;
    this->invtransform = this->invtransform * Tz;
}

const Matrix4 &Transform::getTransform() const {
    return transform;
}

const Matrix4 &Transform::getInvtransform() const {
    return invtransform;
}

#pragma endregion

#pragma region AffineTransform
Vec4 MRay::AffineTransform::applyTransform(const Matrix4 &T, const Vec4 &vec) {
    //T = 4x4 matrix!
    return T*vec;
}

void MRay::AffineTransform::rotatef(Matrix4 &T, float angle, float x, float y, float z) {
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
void MRay::AffineTransform::rotatef(Matrix4 &T, float angle, const Vec3 &axis) {
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
void MRay::AffineTransform::rotatef(Matrix4 &T, float angle, const Vec4 &axis) {
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
Matrix4 MRay::AffineTransform::rotatef(float angle, float x, float y ,float z){
    Matrix4 mat4;
      MRay::AffineTransform::rotatef(mat4, angle, x,y,z);
    return mat4;
}
Matrix4 MRay::AffineTransform::rotatef(float angle, const Vec3 &axis){
    Matrix4 mat4;
      MRay::AffineTransform::rotatef(mat4, angle, axis);
    return mat4;
}
Matrix4 MRay::AffineTransform::rotatef(float angle, const Vec4 &axis){
    Matrix4 mat4;
      MRay::AffineTransform::rotatef(mat4, angle, axis);
    return mat4;
}


void   MRay::AffineTransform::translate(Matrix4 &T, float dx, float dy, float dz) {
    //T must be a 4x4 matrix, each vec4 is a row
    T.set<0>(Vec4(1,0,0,dx));
    T.set<1>(Vec4(0,1,0,dy));
    T.set<2>(Vec4(0,0,1,dz));
    T.set<3>(Vec4(0,0,0,1));
}
Matrix4   MRay::AffineTransform::translate(float dx, float dy, float dz){
    Matrix4 mat4;
      MRay::AffineTransform::translate(mat4, dx, dy, dz);
    return mat4;
}

void   MRay::AffineTransform::scale(Matrix4 &T, float s) {
    //T must be a 4x4 matrix, each vec4 is a row
    T.set<0>(Vec4( s,0,0,0));
    T.set<1>(Vec4( 0,   s,0,0));
    T.set<2>(Vec4( 0,0 ,  s,0));
    T.set<3>(Vec4( 0,0,0,1));
}
void   MRay::AffineTransform::scale(Matrix4 &T, float sx, float sy, float sz) {
    //T must be a 4x4 matrix, each vec4 is a row
    T.set<0>(Vec4(sx,0,0,0));
    T.set<1>(Vec4( 0,  sy,0,0));
    T.set<2>(Vec4( 0,0,  sz,0));
    T.set<3>(Vec4( 0,0,0,1));
}
Matrix4   MRay::AffineTransform::scale(float s){
    Matrix4 mat4;
      MRay::AffineTransform::scale(mat4, s);
    return mat4;
}
Matrix4   MRay::AffineTransform::scale(float sx, float sy, float sz){
    Matrix4 mat4;
      MRay::AffineTransform::scale(mat4, sx, sy, sz);
    return mat4;
}

//https://en.wikipedia.org/wiki/Shear_matrix
void   MRay::AffineTransform::shear(Matrix4 &T, float hxy, float hxz, float hyz, float hyx, float hzx, float hzy) {
    //T must be a 4x4 matrix, each vec4 is a row
    T.set<0>(Vec4(1, hxy, hxz,0));
    T.set<1>(Vec4( hyx,1, hyz,0));
    T.set<2>(Vec4( hzx, hzy,1,0));
    T.set<3>(Vec4(0,0,0,1));
}
void   MRay::AffineTransform::shearX(Matrix4 &T, float shy, float shz) {
    T.set<0>(Vec4(1, 0, 0,0));
    T.set<1>(Vec4( shy,1, 0,0));
    T.set<2>(Vec4( shz, 0,1,0));
    T.set<3>(Vec4(0,0,0,1));
}
void   MRay::AffineTransform::shearY(Matrix4 &T, float shx, float shz) {
    T.set<0>(Vec4(1, shx, 0,0));
    T.set<1>(Vec4( 0,1, 0,0));
    T.set<2>(Vec4( 0, shz,1,0));
    T.set<3>(Vec4(0,0,0,1));
}
void   MRay::AffineTransform::shearZ(Matrix4 &T, float shx, float shy) {
    T.set<0>(Vec4(1, 0, shx,0));
    T.set<1>(Vec4( 0,1, shy,0));
    T.set<2>(Vec4( 0, 0,1,0));
    T.set<3>(Vec4(0,0,0,1));
}
Matrix4   MRay::AffineTransform::shear(float hxy, float hxz, float hyz, float hyx, float hzx, float hzy){
    Matrix4 mat4;
      MRay::AffineTransform::shear(mat4, hxy, hxz, hyz, hyx, hzx, hzy);
    return mat4;
}
Matrix4   MRay::AffineTransform::shearX(float shy, float shz){
    Matrix4 mat4;
      MRay::AffineTransform::shearX(mat4, shy, shz);
    return mat4;
}
Matrix4   MRay::AffineTransform::shearY(float shx, float shz){
    Matrix4 mat4;
      MRay::AffineTransform::shearY(mat4, shx, shz);
    return mat4;
}
Matrix4   MRay::AffineTransform::shearZ(float shx, float shy){
    Matrix4 mat4;
      MRay::AffineTransform::shearZ(mat4, shx, shy);
    return mat4;
}

void   MRay::AffineTransform::rotateX(Matrix4 &T, float angle) {
    float cosa = std::cos(angle);
    float sina = std::sin(angle);
    T.set<0>(Vec4( 1, 0,  0,0));
    T.set<1>(Vec4( 0, cosa, -sina,0));
    T.set<2>(Vec4( 0, sina,  cosa,0));
    T.set<3>(Vec4( 0, 0,  0,1));
}
void   MRay::AffineTransform::rotateY(Matrix4 &T, float angle) {
    float cosa = std::cos(angle);
    float sina = std::sin(angle);
    T.set<0>(Vec4(  cosa, 0, sina,0));
    T.set<1>(Vec4(     0, 1, 0,0));
    T.set<2>(Vec4( -sina, 0, cosa,0));
    T.set<3>(Vec4(     0, 0, 0,1));
}
void   MRay::AffineTransform::rotateZ(Matrix4 &T, float angle) {
    float cosa = std::cos(angle);
    float sina = std::sin(angle);


    T.set<0>(Vec4( cosa, -sina,0,0));
    T.set<1>(Vec4( sina,  cosa,0,0));
    T.set<2>(Vec4(    0,  0,1,0));
    T.set<3>(Vec4(    0,  0,0,1));
}
Matrix4   MRay::AffineTransform::rotateX(float angle){
    Matrix4 mat4;
      MRay::AffineTransform::rotateX(mat4, angle);
    return mat4;
}
Matrix4   MRay::AffineTransform::rotateY(float angle){
    Matrix4 mat4;
      MRay::AffineTransform::rotateY(mat4, angle);
    return mat4;
}
Matrix4   MRay::AffineTransform::rotateZ(float angle){
    Matrix4 mat4;
      MRay::AffineTransform::rotateZ(mat4, angle);
    return mat4;
}
#pragma endregion





