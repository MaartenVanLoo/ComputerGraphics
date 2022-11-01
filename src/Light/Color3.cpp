//
// Created by Maarten Van Loo on 7/10/2022.
//

#include <Light/Color3.h>
#pragma warning( push )
#pragma warning( disable : 4244) //conversion from 'float' to 'uint8_t', possible loss of data
using namespace MRay;
#pragma region Color3
MRay::Color3::Color3() {}

void clipColor(Color3 *c){
    c->setRed(std::min(c->getRed(),255));
    c->setGreen(std::min(c->getGreen(),255));
    c->setBlue(std::min(c->getBlue(),255));
}
MRay::Color3::Color3(int red, int green, int blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

Color3 &MRay::Color3::operator*=(const Vec3 &rhs) {
    this->red   *=rhs.get<0>();
    this->green *=rhs.get<1>();
    this->blue  *=rhs.get<2>();
    clipColor(this);
    return *this;
}
Color3 &MRay::Color3::operator*=(const Vec4 &rhs) {
    this->red   *=rhs.get<0>();
    this->green *=rhs.get<1>();
    this->blue  *=rhs.get<2>();
    clipColor(this);
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
        this->red   = int(color.red   )+ this->red  ;
        this->green = int(color.green )+ this->green;
        this->blue  = int(color.blue  )+ this->blue ;
        clipColor(this);
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

Color3 &Color3::operator*=(double rhs) {
    this->red =   this->red * rhs;
    this->green = this->green * rhs;
    this->blue =  this->blue * rhs;
    clipColor(this);
    return *this;
}

Color3 MRay::operator*(Color3 lhs, double rhs) {
    lhs *= rhs;
    return lhs;
}

Color3 MRay::operator*(double lhs, Color3 rhs) {
    rhs*= lhs;
    return rhs;
}

int Color3::getRed() const {
    return red;
}

int Color3::getGreen() const {
    return green;
}

int Color3::getBlue() const {
    return blue;
}

void Color3::setRed(int red) {
    Color3::red = red;
}

void Color3::setGreen(int green) {
    Color3::green = green;
}

void Color3::setBlue(int blue) {
    Color3::blue = blue;
}

Vec3 Color3::getVector() {
    return Vec3(this->red, this->green, this->blue);
}


#pragma endregion
#pragma warning( pop )