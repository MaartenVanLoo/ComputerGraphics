//
// Created by maart on 30/09/2022.
//

#include "../include/Ray.h"

const Vec4 &Ray::pos() const{
    return this->position;
}


const Vec4 &Ray::dir() const{
    return this->direction;
}


std::ostream &operator<<(std::ostream &os, const Ray &ray) {
    os << "Ray: {" << "position: " << ray.position << " direction: " << ray.direction << "}";
    return os;
}

void Ray::setPos(float x, float y, float z) {
    this->position = Vec4(x,y,z,1);
    //this->position[0] = x;
    //this->position[1] = y;
    //this->position[2] = z;
    //this->position[3] = 1.0;
}
void Ray::setPos(Vec4 &pos) {
    this->position = pos;
    //this->position[0] = pos[0];
    //this->position[1] = pos[1];
    //this->position[2] = pos[2];
    //this->position[3] = 1.0;
}

void Ray::setDir(float x, float y, float z) {
    this->direction = Vec4(x,y,z,0);
    //this->direction[0] = x;
    //this->direction[1] = y;
    //this->direction[2] = z;
    //this->direction[3] = 0.0;
    normalizeDir();
}

Ray::Ray(const Vec4 &position, const Vec4 &direction) : position(position), direction(direction) {
    normalizeDir();
}

void Ray::normalizeDir() {
    float invSqrt = 1.0f/this->direction.abs();
    this->direction*=invSqrt;
}

Vec4 Ray::at(float t) const {
    return this->pos() + this->dir() * t;
}

Ray Ray::transform(const Matrix4 &T) const {
    Ray r;
    r.position = T * this->position;
    r.direction = T * this->direction;
    return r;
}





