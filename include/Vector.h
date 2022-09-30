//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_VECTOR_H
#define I_COMPUTERGRAPHICS_VECTOR_H

#include <cmath>
#include <ostream>

struct Vec2 {
    Vec2(float x = 0.0, float y = 0.0);

    float dot(const Vec2& rhs) const;
    static float dot(const Vec2& lhs, const Vec2& rhs);

    //operators
    Vec2& operator +=(const Vec2& rhs);
    Vec2& operator -=(const Vec2& rhs);
    friend Vec2 operator +(Vec2 lhs, const Vec2& rhs);
    friend Vec2 operator -(Vec2 lhs, const Vec2& rhs);

    friend std::ostream &operator<<(std::ostream &os, const Vec2 &vec2);

    float x, y;
};

struct Vec3{
    Vec3(float x = 0.0, float y = 0.0, float z = 0.0);

    float dot(const Vec3& rhs) const;
    static float dot(const Vec3& lhs, const Vec3& rhs);

    //operators
    Vec3& operator +=(const Vec3& rhs);
    Vec3& operator -=(const Vec3& rhs);
    friend Vec3 operator +(Vec3 lhs, const Vec3& rhs);
    friend Vec3 operator -(Vec3 lhs, const Vec3& rhs);

    friend std::ostream &operator<<(std::ostream &os, const Vec3 &vec3);

    float x,y,z;
};

struct Vec4{
    Vec4(float  = 0.0, float y = 0.0, float z = 0.0, float w = 0.0);

    float dot(const Vec4& rhs) const;
    static float dot(const Vec4& lhs,const Vec4& rhs);

    float abs() const;
    static float abs(const Vec4& vec);

    //operators
    bool operator==(const Vec4 &rhs) const;
    bool operator!=(const Vec4 &rhs) const;

    Vec4 operator-() const;
    Vec4& operator +=(const Vec4& rhs); // elementwise addition
    Vec4& operator -=(const Vec4& rhs); // elementwise subtraction
    Vec4& operator *=(const float rhs); // elementwise multiplication
    Vec4& operator *=(const Vec4& rhs); // elementwise multiplication
    Vec4& operator /=(const float rhs); // elementwise division
    Vec4& operator /=(const Vec4& rhs); // elementwise division

    friend Vec4 operator +(Vec4 lhs, const Vec4& rhs);   //elementwise addition
    friend Vec4 operator -(Vec4 lhs, const Vec4& rhs);   //elementwise subtraction
    friend Vec4 operator *(const float &lhs, Vec4 rhs);  //elementwise multiplication
    friend Vec4 operator *(Vec4 lhs, const float& rhs);  //elementwise multiplication
    friend Vec4 operator *(Vec4 lhs, const Vec4& rhs);   //elementwise multiplication
    friend Vec4 operator /(const float &lhs, Vec4 rhs);  //elementwise division
    friend Vec4 operator /(Vec4 lhs, const float& rhs);  //elementwise division
    friend Vec4 operator /(Vec4 lhs, const Vec4& rhs);   //elementwise division

    friend std::ostream &operator<<(std::ostream &os, const Vec4 &vec4);

    float x,y,z,w;
};


#endif //I_COMPUTERGRAPHICS_VECTOR_H
