//
// Created by maart on 7/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_COLOR3_H
#define I_COMPUTERGRAPHICS_COLOR3_H

#include <cstdint>
#include <Ray.h>

struct Color3{
    Color3();
    Color3(int red, int green, int blue);

    void add(const Color3 &color);

    //multiplication
    Color3& operator *=(const Vec3& rhs);                    // elementwise multiplication
    Color3& operator *=(const Vec4& rhs);                    // elementwise multiplication
    Color3& operator *=(float rhs);                          // elementwise multiplication
    friend Color3 operator *(Color3 lhs, const Vec3& rhs);   //elementwise multiplication
    friend Color3 operator *(const Vec3& lhs, Color3 rhs);   //elementwise multiplication
    friend Color3 operator *(Color3 lhs, const Vec4& rhs);   //elementwise multiplication
    friend Color3 operator *(const Vec4& lhs, Color3 rhs);   //elementwise multiplication
    friend Color3 operator *(Color3 lhs, float rhs);         //elementwise subtraction
    friend Color3 operator *(float lhs, Color3 rhs);         //elementwise subtraction
    uint8_t red=0;
    uint8_t green=0;
    uint8_t blue=0;
};
#endif //I_COMPUTERGRAPHICS_COLOR3_H
