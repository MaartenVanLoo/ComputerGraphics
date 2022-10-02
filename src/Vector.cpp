//
// Created by maart on 30/09/2022.
//

#include "../include/Vector.h"

#pragma region Vec2
Vec2::Vec2(float x, float y) {
    this->data[0] = x;
    this->data[1] = y;
}
float Vec2::dot(const Vec2 &rhs) const {
    return this->data[0] * rhs.data[0] + this->data[1] * rhs.data[1];
}

float Vec2::dot(const Vec2 &lhs, const Vec2 &rhs) {
    return lhs.dot(rhs);
}

#pragma region operators
bool Vec2::operator==(const Vec2 &rhs) const {
    return this->data[0] == rhs.data[0] &&
           this->data[1] == rhs.data[1];
}
bool Vec2::operator!=(const Vec2 &rhs) const {
    return !(rhs == *this);
}

Vec2 Vec2::operator-() const {
    Vec2 res = *this;
    res.data[0] = -res.data[0];
    res.data[1] = -res.data[1];
    return res;
}
Vec2& Vec2::operator+=(const Vec2& rhs) {
    this->data[0]+=rhs.data[0];
    this->data[1]+=rhs.data[1];
    return *this;
}
Vec2& Vec2::operator-=(const Vec2& rhs) {
    this->data[0]-=rhs.data[0];
    this->data[1]-=rhs.data[1];
    return *this;
}
Vec2 &Vec2::operator*=(const float rhs) {
    this->data[0]*=rhs;
    this->data[1]*=rhs;
    return *this;
}
Vec2 &Vec2::operator*=(const Vec2& rhs) {
    this->data[0]*=rhs.data[0];
    this->data[1]*=rhs.data[1];
    return *this;
}
Vec2 &Vec2::operator/=(const float rhs) {
    this->data[0]/=rhs;
    this->data[1]/=rhs;
    return *this;
}
Vec2 &Vec2::operator/=(const Vec2& rhs) {
    this->data[0]/=rhs.data[0];
    this->data[1]/=rhs.data[1];
    return *this;
}

Vec2 operator+(Vec2 lhs, const Vec2 &rhs) {
    lhs += rhs;
    return lhs;
}
Vec2 operator-(Vec2 lhs, const Vec2 &rhs) {
    lhs-=rhs;
    return lhs;
}
Vec2 operator*(const float &lhs, Vec2 rhs) {
    rhs*=lhs;
    return rhs;
}
Vec2 operator*(Vec2 lhs, const float &rhs) {
    lhs*=rhs;
    return lhs;
}
Vec2 operator*(Vec2 lhs, const Vec2 &rhs) {
    lhs*=rhs;
    return lhs;
}
Vec2 operator/(Vec2 lhs, const float &rhs) {
    lhs/=rhs;
    return lhs;
}
Vec2 operator/(const float &lhs, Vec2 rhs ) {
    rhs.data[0] = lhs/rhs.data[0];
    rhs.data[1] = lhs/rhs.data[1];
    return rhs;
}
Vec2 operator/(Vec2 lhs, const Vec2 &rhs) {
    lhs/=rhs;
    return lhs;
}
#pragma endregion

std::ostream &operator<<(std::ostream &os, const Vec2 &vec2) {
    os <<"[" << vec2.data[0] << ", " << vec2.data[1] << "]";
    return os;
}

float &Vec2::operator[](int index) {
    if (index > 1 || index < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    return this->data[index];
}

#pragma endregion


#pragma region Vec3

Vec3::Vec3(float x, float y, float z) {
    this->data[0] = x;
    this->data[1] = y;
    this->data[2] = z;
}

float Vec3::dot(const Vec3 &rhs) const {
    return this->data[0] * rhs.data[0] + this->data[1] * rhs.data[1] +  this->data[2] * rhs.data[2];
}
float Vec3::dot(const Vec3 &lhs, const Vec3 &rhs) {
    return lhs.dot(rhs);
}

Vec3 Vec3::cross(const Vec3& rhs) const {
    return Vec3(this->data[1]*rhs.data[2] - this->data[2]*rhs.data[1],
                this->data[2]*rhs.data[0] - this->data[0]*rhs.data[2],
                this->data[0]*rhs.data[1] - this->data[1]*rhs.data[0]);
}

Vec3 Vec3::cross(const Vec3& lhs, const Vec3& rhs) {
    return Vec3(lhs.data[1]*rhs.data[2] - lhs.data[2]*rhs.data[1],
                lhs.data[2]*rhs.data[0] - lhs.data[0]*rhs.data[2],
                lhs.data[0]*rhs.data[1] - lhs.data[1]*rhs.data[0]);
}

#pragma region operators
bool Vec3::operator==(const Vec3 &rhs) const {
    return this->data[0] == rhs.data[0] &&
           this->data[1] == rhs.data[1] &&
           this->data[2] == rhs.data[2];
}
bool Vec3::operator!=(const Vec3 &rhs) const {
    return !(rhs == *this);
}

Vec3 Vec3::operator-() const {
    Vec3 res = *this;
    res.data[0] = -res.data[0];
    res.data[1] = -res.data[1];
    res.data[2] = -res.data[2];
    return res;
}
Vec3& Vec3::operator+=(const Vec3& rhs) {
    this->data[0]+=rhs.data[0];
    this->data[1]+=rhs.data[1];
    this->data[2]+=rhs.data[2];
    return *this;
}
Vec3& Vec3::operator-=(const Vec3& rhs) {
    this->data[0]-=rhs.data[0];
    this->data[1]-=rhs.data[1];
    this->data[2]-=rhs.data[2];
    return *this;
}
Vec3 &Vec3::operator*=(const float rhs) {
    this->data[0]*=rhs;
    this->data[1]*=rhs;
    this->data[2]*=rhs;
    return *this;
}
Vec3 &Vec3::operator*=(const Vec3& rhs) {
    this->data[0]*=rhs.data[0];
    this->data[1]*=rhs.data[1];
    this->data[2]*=rhs.data[2];
    return *this;
}
Vec3 &Vec3::operator/=(const float rhs) {
    this->data[0]/=rhs;
    this->data[1]/=rhs;
    this->data[2]/=rhs;
    return *this;
}
Vec3 &Vec3::operator/=(const Vec3& rhs) {
    this->data[0]/=rhs.data[0];
    this->data[1]/=rhs.data[1];
    this->data[2]/=rhs.data[2];
    return *this;
}

Vec3 operator+(Vec3 lhs, const Vec3 &rhs) {
    lhs += rhs;
    return lhs;
}
Vec3 operator-(Vec3 lhs, const Vec3 &rhs) {
    lhs-=rhs;
    return lhs;
}
Vec3 operator*(const float &lhs, Vec3 rhs) {
    rhs*=lhs;
    return rhs;
}
Vec3 operator*(Vec3 lhs, const float &rhs) {
    lhs*=rhs;
    return lhs;
}
Vec3 operator*(Vec3 lhs, const Vec3 &rhs) {
    lhs*=rhs;
    return lhs;
}
Vec3 operator/(Vec3 lhs, const float &rhs) {
    lhs/=rhs;
    return lhs;
}
Vec3 operator/(const float &lhs, Vec3 rhs ) {
    rhs.data[0] = lhs/rhs.data[0];
    rhs.data[1] = lhs/rhs.data[1];
    rhs.data[2] = lhs/rhs.data[2];
    return rhs;
}
Vec3 operator/(Vec3 lhs, const Vec3 &rhs) {
    lhs/=rhs;
    return lhs;
}
#pragma endregion

std::ostream &operator<<(std::ostream &os, const Vec3 &vec3) {
    os <<"[" << vec3.data[0] << ", " << vec3.data[0] << ", " << vec3.data[0] << "]";
    return os;
}

float &Vec3::operator[](int index) {
    if (index > 2 || index < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    return this->data[index];
}

#pragma endregion


#pragma region Vec4
Vec4::Vec4(float x, float y, float z, float w) {
    this->data[0] = x;
    this->data[1] = y;
    this->data[2] = z;
    this->data[3] = w;
}
Vec4::Vec4(Vec3 &vec3, float w) {
    this->data[0] = vec3.data[0];
    this->data[1] = vec3.data[0];
    this->data[2] = vec3.data[0];
    this->data[3] = w;
}

float Vec4::dot(const Vec4 &rhs) const {
    return
        this->data[0] * rhs.data[0] +
        this->data[1] * rhs.data[1] +
        this->data[2] * rhs.data[2] +
        this->data[3] * rhs.data[3];
}
float Vec4::dot(const Vec4 &lhs, const Vec4 &rhs) {
    return lhs.dot(rhs);
}

Vec4 Vec4::cross(const Vec4 &rhs) const {
    return Vec4(this->data[1]*rhs.data[2] - this->data[2]*rhs.data[1],
                this->data[2]*rhs.data[0] - this->data[0]*rhs.data[2],
                this->data[0]*rhs.data[1] - this->data[1]*rhs.data[0],
                this->data[3]);
}

Vec4 Vec4::cross(const Vec4 &lhs, const Vec4 &rhs) {
    return Vec4(lhs.data[1]*rhs.data[2] - lhs.data[2]*rhs.data[1],
                lhs.data[2]*rhs.data[0] - lhs.data[0]*rhs.data[2],
                lhs.data[0]*rhs.data[1] - lhs.data[1]*rhs.data[0],
                lhs.data[3]);
}

float Vec4::abs() const {
    return std::sqrt(this->data[0] * this->data[0] +
                     this->data[1] * this->data[1] +
                     this->data[2] * this->data[2] +
                     this->data[3] * this->data[3]);
}

float Vec4::abs(const Vec4 &vec) {
    return vec.abs();
}

#pragma region operators
bool Vec4::operator==(const Vec4 &rhs) const {
    return this->data[0] == rhs.data[0] &&
            this->data[1] == rhs.data[1] &&
            this->data[2] == rhs.data[2] &&
            this->data[3] == rhs.data[3];
}
bool Vec4::operator!=(const Vec4 &rhs) const {
    return !(rhs == *this);
}

Vec4 Vec4::operator-() const {
    Vec4 res = *this;
    res.data[0] = -res.data[0];
    res.data[1] = -res.data[1];
    res.data[2] = -res.data[2];
    res.data[3] = -res.data[3];
    return res;
}
Vec4& Vec4::operator+=(const Vec4& rhs) {
    this->data[0]+=rhs.data[0];
    this->data[1]+=rhs.data[1];
    this->data[2]+=rhs.data[2];
    this->data[3]+=rhs.data[3];
    return *this;
}
Vec4& Vec4::operator-=(const Vec4& rhs) {
    this->data[0]-=rhs.data[0];
    this->data[1]-=rhs.data[1];
    this->data[2]-=rhs.data[2];
    this->data[3]-=rhs.data[3];
    return *this;
}
Vec4 &Vec4::operator*=(const float rhs) {
    this->data[0]*=rhs;
    this->data[1]*=rhs;
    this->data[2]*=rhs;
    this->data[3]*=rhs;
    return *this;
}
Vec4 &Vec4::operator*=(const Vec4& rhs) {
    this->data[0]*=rhs.data[0];
    this->data[1]*=rhs.data[1];
    this->data[2]*=rhs.data[2];
    this->data[3]*=rhs.data[3];
    return *this;
}
Vec4 &Vec4::operator/=(const float rhs) {
    this->data[0]/=rhs;
    this->data[1]/=rhs;
    this->data[2]/=rhs;
    this->data[3]/=rhs;
    return *this;
}
Vec4 &Vec4::operator/=(const Vec4& rhs) {
    this->data[0]/=rhs.data[0];
    this->data[1]/=rhs.data[1];
    this->data[2]/=rhs.data[2];
    this->data[3]/=rhs.data[3];
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
    rhs.data[0] = lhs/rhs.data[0];
    rhs.data[1] = lhs/rhs.data[1];
    rhs.data[2] = lhs/rhs.data[2];
    rhs.data[3] = lhs/rhs.data[3];
    return rhs;
}
Vec4 operator/(Vec4 lhs, const Vec4 &rhs) {
    lhs/=rhs;
    return lhs;
}

#pragma endregion

std::ostream &operator<<(std::ostream &os, const Vec4 &vec4) {
    os <<"[" << vec4.data[0] << ", " << vec4.data[1] << ", " << vec4.data[2] << ", " << vec4.data[3] << "]";
    return os;
}

float& Vec4::operator[](int index){
    if (index > 3 || index < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    return this->data[index];
}

Vec4::Vec4(const Vec4 &p1) {
    this->data[0] = p1.data[0];
    this->data[1] = p1.data[1];
    this->data[2] = p1.data[2];
    this->data[3] = p1.data[3];
}

float Vec4::angle(const Vec4 &v1, const Vec4 &v2) {
    return v1.dot(v2)/(abs(v1)*abs(v2));
}

float Vec4::sum(const Vec4 &vec) {
    return vec.data[0] + vec.data[1] + vec.data[2] + vec.data[3];
}


#pragma endregion









