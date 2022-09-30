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
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    this->position.w = 1.0;
}
void Ray::setPos(const Vec4 &pos) {
    this->position.x = pos.x;
    this->position.y = pos.y;
    this->position.z = pos.z;
    this->position.w = 1.0;
}

void Ray::setDir(float x, float y, float z) {
    this->direction.x = x;
    this->direction.y = y;
    this->direction.z = z;
    this->direction.w = 0.0;
    normalizeDir();
}

Ray::Ray(const Vec4 &position, const Vec4 &direction) : position(position), direction(direction) {
    normalizeDir();
}

void Ray::normalizeDir() {
    float invSqrt = 1.0/std::sqrt(this->direction.x * this->direction.x
            + this->direction.y * this->direction.y
            + this->direction.z * this->direction.z
            + this->direction.w * this->direction.w);
    this->direction*=invSqrt;
}

Vec4 Ray::at(float t) const {
    return this->pos() + this->dir() * t;
}






