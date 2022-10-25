//
// Created by Maarten Van Loo on 7/10/2022.
//

#include <Light/Color3.h>
#pragma warning( push )
#pragma warning( disable : 4244) //conversion from 'float' to 'uint8_t', possible loss of data
using namespace MRay;
#pragma region Color3
MRay::Color3::Color3() {}

MRay::Color3::Color3(int red, int green, int blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

Color3 &MRay::Color3::operator*=(const Vec3 &rhs) {
    this->red   *=rhs.get<0>();
    this->green *=rhs.get<1>();
    this->blue  *=rhs.get<2>();
    return *this;
}
Color3 &MRay::Color3::operator*=(const Vec4 &rhs) {
    this->red   *=rhs.get<0>();
    this->green *=rhs.get<1>();
    this->blue  *=rhs.get<2>();
    return *this;
}
Color3 &MRay::Color3::operator*=(float rhs) {
    this->red   *=rhs;
    this->green *=rhs;
    this->blue  *=rhs;
    return *this;
}

Color3 MRay::operator*(const Vec3 &lhs, Color3 rhs) {
    rhs *= lhs;
    return rhs;
}
Color3 MRay::operator*(Color3 lhs, const Vec3 &rhs) {
    lhs *= rhs;
    return lhs;
}
Color3 MRay::operator*(const Vec4 &lhs, Color3 rhs) {
    rhs *= lhs;
    return rhs;
}
Color3 MRay::operator*(Color3 lhs, const Vec4 &rhs) {
    lhs *= rhs;
    return lhs;
}
Color3 MRay::operator*(Color3 lhs, float rhs) {
    lhs *= rhs;
    return lhs;
}
Color3 MRay::operator*(float lhs, Color3 rhs) {
    rhs *= lhs;
    return rhs;
}

void MRay::Color3::add(const Color3 &color) {
    if (transactionOpen){
        this->accRed += color.red;
        this->accGreen += color.green;
        this->accBlue += color.blue;
        this->n++;
    }else{
        if (int(color.red) + this->red < 0)
            std::cout << int(color.red) + this->red << "\n";
        if (int(color.green) + this->green < 0)
            std::cout << int(color.green) + this->green << "\n";
        if (int(color.blue) + this->blue < 0)
            std::cout << int(color.blue) + this->blue << "\n";
        this->red   = std::min(int(color.red   )+ this->red  ,255);
        this->green = std::min(int(color.green )+ this->green,255);
        this->blue  = std::min(int(color.blue  )+ this->blue ,255);
    }
}

void MRay::Color3::openTransaction() {
 if (this->transactionOpen) return;
 this->transactionOpen = true;
 this->accRed = 0;
 this->accGreen = 0;
 this->accBlue = 0;
 this->n = 0;
}

void MRay::Color3::closeTransaction() {
    if (!this->transactionOpen) return;
    this->transactionOpen = false;
    if (n == 0) return;
    this->red   = this->red  /2 + this->accRed/(2*n);
    this->green = this->green/2 + this->accGreen/(2*n);
    this->blue  = this->blue /2 + this->accBlue/(2*n);
}

void MRay::Color3::rollBackTransaction() {
    this->transactionOpen = false;
}

void MRay::Color3::clear() {
    this->red  = 0;
    this->green= 0;
    this->blue = 0;
}

Color3::Color3(const Vec3 &v) {
    this->red = v.get<0>();
    this->green = v.get<1>();
    this->blue = v.get<2>();
}
Color3::Color3(const Vec4 &v) {
    this->red = v.get<0>();
    this->green = v.get<1>();
    this->blue = v.get<2>();
}
std::ostream &MRay::operator<<(std::ostream &os, const Color3 &color3) {
    os << "[red: " << int(color3.red) << " green: " << int(color3.green) << " blue: " << int(color3.blue) << "]";
    return os;
}




#pragma endregion
#pragma warning( pop )