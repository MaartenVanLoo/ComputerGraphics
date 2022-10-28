//
// Created by Maarten Van Loo on 30/09/2022.
//

#include "../include/Ray.h"
#include <Objects/Object.h>
using namespace MRay;
const Vec4 & MRay::Ray::pos() const{
    return this->position;
}


const Vec4 & MRay::Ray::dir() const{
    return this->direction;
}




void  MRay::Ray::setPos(float x, float y, float z) {
    this->position = Vec4(x,y,z,1);
    //this->position[0] = x;
    //this->position[1] = y;
    //this->position[2] = z;
    //this->position[3] = 1.0;
}
void  MRay::Ray::setPos(const Vec4 &pos) {
    this->position = pos;
    //this->position[0] = pos[0];
    //this->position[1] = pos[1];
    //this->position[2] = pos[2];
    //this->position[3] = 1.0;
}

void  MRay::Ray::setDir(float x, float y, float z) {
    this->direction = Vec4(x,y,z,0);
    //this->direction[0] = x;
    //this->direction[1] = y;
    //this->direction[2] = z;
    //this->direction[3] = 0.0;
    normalizeDir();
}

 MRay::Ray::Ray(const Vec4 &position, const Vec4 &direction) : position(position), direction(direction) {
    normalizeDir();
}

void  MRay::Ray::normalizeDir() {
    float invSqrt = 1.0f/this->direction.abs();
    this->direction*=invSqrt;
}

Vec4  MRay::Ray::at(float t) const {
    return this->pos() + this->dir() * t;
}

Ray  MRay::Ray::transform(const Matrix4 &T) const {
    Ray r;
    r.position = T * this->position;
    r.direction = T * this->direction;
    return r;
}

void Ray::setDir(const Vec4 &dir) {
    this->direction = dir;
    normalizeDir();
}

void Ray::setDepth(int d) {
    this->depth = d;
}

void Ray::increaseDepth(){
    this->depth++;
}


int Ray::getDepth() const {
    return this->depth;
}

std::ostream &MRay::operator<<(std::ostream &os, const Ray &ray) {
    os << "position: " << ray.position << " direction: " << ray.direction;
    return os;
}

Object *Ray::getObject() const{
    return this->obj;
}

void Ray::setObject(Object *obj) {
    this->obj = obj;
}




