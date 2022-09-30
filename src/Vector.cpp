//
// Created by maart on 30/09/2022.
//

#include "../include/Vector.h"

Vec2::Vec2(float x, float y) : x(x), y(y) {}
float Vec2::dot(const Vec2 &rhs) const {
    return this->x * rhs.x + this->y * rhs.y;
}

float Vec2::dot(const Vec2 &lhs, const Vec2 &rhs) {
    return lhs.dot(rhs);
}

Vec2& Vec2::operator+=(const Vec2& rhs) {
    this->x+=rhs.x;
    this->y+=rhs.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& rhs) {
    this->x-=rhs.x;
    this->y-=rhs.y;
    return *this;
}
Vec2 operator+(Vec2 lhs, const Vec2 &rhs) {
    lhs += rhs;
    return lhs;
}
Vec2 operator-(Vec2 lhs, const Vec2 &rhs) {
    lhs -= rhs;
    return lhs;
}

std::ostream &operator<<(std::ostream &os, const Vec2 &vec2) {
    os <<"[" << vec2.x << ", " << vec2.y << "]";
    return os;
}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

float Vec3::dot(const Vec3 &rhs) const {
    return this->x * rhs.x + this->y * rhs.y +  this->z * rhs.z;
}
float Vec3::dot(const Vec3 &lhs, const Vec3 &rhs) {
    return lhs.dot(rhs);
}
Vec3& Vec3::operator+=(const Vec3& rhs) {
    this->x+=rhs.x;
    this->y+=rhs.y;
    this->z+=rhs.z;
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& rhs) {
    this->x-=rhs.x;
    this->y-=rhs.y;
    this->z-=rhs.z;
    return *this;
}
Vec3 operator+(Vec3 lhs, const Vec3 &rhs) {
    lhs += rhs;
    return lhs;
}
Vec3 operator-(Vec3 lhs, const Vec3 &rhs) {
    lhs -= rhs;
    return lhs;
}

std::ostream &operator<<(std::ostream &os, const Vec3 &vec3) {
    os <<"[" << vec3.x << ", " << vec3.y << ", " << vec3.z << "]";
    return os;
}

Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

float Vec4::dot(const Vec4 &rhs) const {
    return this->x * rhs.x + this->y * rhs.y + this->z* rhs.z + this->w * rhs.w;
}
float Vec4::dot(const Vec4 &lhs, const Vec4 &rhs) {
    return lhs.dot(rhs);
}
float Vec4::abs() const {
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

float Vec4::abs(const Vec4 &vec) {
    return vec.abs();
}

bool Vec4::operator==(const Vec4 &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           z == rhs.z &&
           w == rhs.w;
}

bool Vec4::operator!=(const Vec4 &rhs) const {
    return !(rhs == *this);
}
Vec4& Vec4::operator+=(const Vec4& rhs) {
    this->x+=rhs.x;
    this->y+=rhs.y;
    this->z+=rhs.z;
    this->w+=rhs.w;
    return *this;
}

Vec4& Vec4::operator-=(const Vec4& rhs) {
    this->x-=rhs.x;
    this->y-=rhs.y;
    this->z-=rhs.z;
    this->w-=rhs.w;
    return *this;
}
Vec4 &Vec4::operator*=(const float rhs) {
    this->x*=rhs;
    this->y*=rhs;
    this->z*=rhs;
    this->w*=rhs;
    return *this;
}
Vec4 &Vec4::operator*=(const Vec4& rhs) {
    this->x*=rhs.x;
    this->y*=rhs.y;
    this->z*=rhs.z;
    this->w*=rhs.w;
    return *this;
}
Vec4 &Vec4::operator/=(const float rhs) {
    this->x/=rhs;
    this->y/=rhs;
    this->z/=rhs;
    this->w/=rhs;
    return *this;
}
Vec4 &Vec4::operator/=(const Vec4& rhs) {
    this->x/=rhs.x;
    this->y/=rhs.y;
    this->z/=rhs.z;
    this->w/=rhs.w;
    return *this;
}

Vec4 operator+(Vec4 lhs, const Vec4 &rhs) {
    lhs += rhs;
    return lhs;
}
Vec4 operator-(Vec4 lhs, const Vec4 &rhs) {
    lhs-=rhs;
    return lhs;
}

Vec4 operator*(const float &lhs, Vec4 rhs) {
    rhs*=lhs;
    return rhs;
}

Vec4 operator*(Vec4 lhs, const float &rhs) {
    lhs*=rhs;
    return lhs;
}
Vec4 operator*(Vec4 lhs, const Vec4 &rhs) {
    lhs*=rhs;
    return lhs;
}

Vec4 operator/(Vec4 lhs, const float &rhs) {
    lhs/=rhs;
    return lhs;
}

Vec4 operator/(const float &lhs, Vec4 rhs ) {
    rhs/=lhs;
    return rhs;
}
Vec4 operator/(Vec4 lhs, const Vec4 &rhs) {
    lhs/=rhs;
    return lhs;
}

Vec4 Vec4::operator-() const {
    Vec4 res = *this;
    res.x = -res.x;
    res.y = -res.y;
    res.z = -res.z;
    res.w = -res.w;
    return res;
}

std::ostream &operator<<(std::ostream &os, const Vec4 &vec4) {
    os <<"[" << vec4.x << ", " << vec4.y << ", " << vec4.z << ", " << vec4.w << "]";
    return os;
}











