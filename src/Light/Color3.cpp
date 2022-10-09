//
// Created by maart on 7/10/2022.
//

#include <Light/Color3.h>

#pragma region Color3
Color3::Color3() {}

Color3::Color3(int red, int green, int blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

Color3 &Color3::operator*=(const Vec3 &rhs) {
    this->red   *=rhs.get<0>();
    this->green *=rhs.get<1>();
    this->blue  *=rhs.get<2>();
    return *this;
}
Color3 &Color3::operator*=(const Vec4 &rhs) {
    this->red   *=rhs.get<0>();
    this->green *=rhs.get<1>();
    this->blue  *=rhs.get<2>();
    return *this;
}
Color3 &Color3::operator*=(float rhs) {
    this->red   *=rhs;
    this->green *=rhs;
    this->blue  *=rhs;
    return *this;
}

Color3 operator*(const Vec3 &lhs, Color3 rhs) {
    rhs *= lhs;
    return rhs;
}
Color3 operator*(Color3 lhs, const Vec3 &rhs) {
    lhs *= rhs;
    return lhs;
}
Color3 operator*(const Vec4 &lhs, Color3 rhs) {
    rhs *= lhs;
    return rhs;
}
Color3 operator*(Color3 lhs, const Vec4 &rhs) {
    lhs *= rhs;
    return lhs;
}
Color3 operator*(Color3 lhs, float rhs) {
    lhs *= rhs;
    return lhs;
}
Color3 operator*(float lhs, Color3 rhs) {
    rhs *= lhs;
    return rhs;
}

void Color3::add(const Color3 &color) {
    this->red   = (int(color.red)   + this->red  )/2;
    this->green = (int(color.green) + this->green)/2;
    this->blue  = (int(color.blue)  + this->blue )/2;
}


#pragma endregion
