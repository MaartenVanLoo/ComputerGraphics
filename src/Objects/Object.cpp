//
// Created by maart on 30/09/2022.
//

#include "../../include/Objects/Object.h"

std::ostream &operator<<(std::ostream &os, const Object &object) {
    return os;
}

void Object::rotate(float rx, float ry, float rz) {
    Matrix4 Tx,Ty,Tz;
    Transform::rotateX(Tx,rx);
    Transform::rotateY(Ty,ry);
    Transform::rotateZ(Tz,rz);
    this->transform = Tx * this->transform;
    this->transform = Ty * this->transform;
    this->transform = Tz * this->transform;
    //inverse transform
    Transform::rotateX(Tx,-rx);
    Transform::rotateY(Ty,-ry);
    Transform::rotateZ(Tz,-rz);
    this->invtransform = this->invtransform * Tx; //reverse order of transform!
    this->invtransform = this->invtransform * Ty;
    this->invtransform = this->invtransform * Tz;
}

void Object::translate(float tx, float ty, float tz) {
    Matrix4 T;
    Transform::translate(T,tx,ty,tz);
    this->transform = T * this->transform;
    //inverse transform
    Transform::translate(T,-tx,-ty,-tz);
    this->invtransform = this->invtransform * T; //reverse order of transform!
}

void Object::scale(float sx, float sy, float sz) {
    Matrix4 T;
    Transform::scale(T,sx,sy,sz);
    this->transform = T * this->transform;
    Transform::scale(T,1/sx,1/sy,1/sz);
    this->invtransform = this->invtransform * T; //reverse order of transform!
}

void Object::shear(float shXy, float shXz, float shYx, float shYz, float shZx, float shZy ) {
    Matrix4 Tx,Ty,Tz;
    Transform::shearX(Tx,shXy,shXz);
    Transform::shearY(Ty,shYx,shYz);
    Transform::shearZ(Tz,shZx,shZy);
    this->transform = Tx * this->transform;
    this->transform = Ty * this->transform;
    this->transform = Tz * this->transform;
    //inverse transform
    Transform::shearX(Tx,-shXy,-shXz);
    Transform::shearY(Ty,-shYx,-shYz);
    Transform::shearZ(Tz,-shZx,-shZy);
    this->invtransform = this->invtransform * Tx; //reverse order of transform!
    this->invtransform = this->invtransform * Ty;
    this->invtransform = this->invtransform * Tz;
}