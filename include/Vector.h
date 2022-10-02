//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_VECTOR_H
#define I_COMPUTERGRAPHICS_VECTOR_H

#include <cmath>
#include <ostream>

struct Vec2;
struct Vec3;
struct Vec4;

struct Vec2 {
    Vec2(float x = 0.0, float y = 0.0);

    float dot(const Vec2& rhs) const;
    static float dot(const Vec2& lhs, const Vec2& rhs);

    //operators
    bool operator==(const Vec2 &rhs) const;
    bool operator!=(const Vec2 &rhs) const;

    Vec2 operator-() const;
    Vec2& operator +=(const Vec2& rhs); // elementwise addition
    Vec2& operator -=(const Vec2& rhs); // elementwise subtraction
    Vec2& operator *=(const float rhs); // elementwise multiplication
    Vec2& operator *=(const Vec2& rhs); // elementwise multiplication
    Vec2& operator /=(const float rhs); // elementwise division
    Vec2& operator /=(const Vec2& rhs); // elementwise division

    friend Vec2 operator +(Vec2 lhs, const Vec2& rhs);   //elementwise addition
    friend Vec2 operator -(Vec2 lhs, const Vec2& rhs);   //elementwise subtraction
    friend Vec2 operator *(const float &lhs, Vec2 rhs);  //elementwise multiplication
    friend Vec2 operator *(Vec2 lhs, const float& rhs);  //elementwise multiplication
    friend Vec2 operator *(Vec2 lhs, const Vec2& rhs);   //elementwise multiplication
    friend Vec2 operator /(const float &lhs, Vec2 rhs);  //elementwise division
    friend Vec2 operator /(Vec2 lhs, const float& rhs);  //elementwise division
    friend Vec2 operator /(Vec2 lhs, const Vec2& rhs);   //elementwise division

    float& operator[](int index);

    friend std::ostream &operator<<(std::ostream &os, const Vec2 &vec2);
private:
    float data[2] {0.0,0.0};
    friend Vec3;
    friend Vec4;

};

struct Vec3{
    Vec3(float x = 0.0, float y = 0.0, float z = 0.0);

    float dot(const Vec3& rhs) const;
    static float dot(const Vec3& lhs, const Vec3& rhs);

    Vec3 cross(const Vec3& rhs) const;
    Vec3 cross(const Vec3& lhs, const Vec3& rhs);

    //operators
    bool operator==(const Vec3 &rhs) const;
    bool operator!=(const Vec3 &rhs) const;

    Vec3 operator-() const;
    Vec3& operator +=(const Vec3& rhs); // elementwise addition
    Vec3& operator -=(const Vec3& rhs); // elementwise subtraction
    Vec3& operator *=(const float rhs); // elementwise multiplication
    Vec3& operator *=(const Vec3& rhs); // elementwise multiplication
    Vec3& operator /=(const float rhs); // elementwise division
    Vec3& operator /=(const Vec3& rhs); // elementwise division

    friend Vec3 operator +(Vec3 lhs, const Vec3& rhs);   //elementwise addition
    friend Vec3 operator -(Vec3 lhs, const Vec3& rhs);   //elementwise subtraction
    friend Vec3 operator *(const float &lhs, Vec3 rhs);  //elementwise multiplication
    friend Vec3 operator *(Vec3 lhs, const float& rhs);  //elementwise multiplication
    friend Vec3 operator *(Vec3 lhs, const Vec3& rhs);   //elementwise multiplication
    friend Vec3 operator /(const float &lhs, Vec3 rhs);  //elementwise division
    friend Vec3 operator /(Vec3 lhs, const float& rhs);  //elementwise division
    friend Vec3 operator /(Vec3 lhs, const Vec3& rhs);   //elementwise division

    float& operator[](int index);

    friend std::ostream &operator<<(std::ostream &os, const Vec3 &vec3);

private:
    float data[3] {0.0,0.0,0.0};;
    friend Vec2;
    friend Vec4;
    //float x,y,z;
};

struct Vec4{
    Vec4(float  = 0.0, float y = 0.0, float z = 0.0, float w = 0.0);
    Vec4(Vec3 &vec3, float w = 0.0);

    // Copy constructor
    Vec4(const Vec4& p1);

    float dot(const Vec4& rhs) const;
    static float dot(const Vec4& lhs,const Vec4& rhs);

    //compute the cross product as if ti was a Vec3 (only first 3 elements will be used)
    Vec4 cross(const Vec4& rhs) const;
    Vec4 cross(const Vec4& lhs, const Vec4& rhs);

    float abs() const;
    static float abs(const Vec4& vec);

    //angle between 2 vectors
    float angle(const Vec4& v1, const Vec4& v2);

    //sum of all values
    static float sum(const Vec4& vec);
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

    float& operator[](int index);

    friend std::ostream &operator<<(std::ostream &os, const Vec4 &vec4);

private:
    float data[4] {0.0,0.0,0.0,0.0};
    friend Vec2;
    friend Vec3;
    //float x,y,z,w;
};



#endif //I_COMPUTERGRAPHICS_VECTOR_H
