//
// Created by Maarten Van Loo on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_VECTOR_H
#define I_COMPUTERGRAPHICS_VECTOR_H

#include <cmath>
#include <ostream>
#include <immintrin.h>
#include <AVX.h>
#include "LinearAlgebra.h"
#include <cassert>


//for easy indexing
#define _X 0
#define _Y 1
#define _Z 2


namespace MRay {
        class Vec2 {
        public:
            Vec2(float x = 0.0, float y = 0.0);

            float get(int index) const;

            float dot(const Vec2 &rhs) const;

            static float dot(const Vec2 &lhs, const Vec2 &rhs);

            //operators
            bool operator==(const Vec2 &rhs) const;

            bool operator!=(const Vec2 &rhs) const;

            Vec2 operator-() const;

            Vec2 &operator+=(const Vec2 &rhs); // elementwise addition
            Vec2 &operator-=(const Vec2 &rhs); // elementwise subtraction
            Vec2 &operator*=(float rhs); // elementwise multiplication
            Vec2 &operator*=(const Vec2 &rhs); // elementwise multiplication
            Vec2 &operator/=(float rhs); // elementwise division
            Vec2 &operator/=(const Vec2 &rhs); // elementwise division

            friend Vec2 operator+(Vec2 lhs, const Vec2 &rhs);   //elementwise addition
            friend Vec2 operator-(Vec2 lhs, const Vec2 &rhs);   //elementwise subtraction
            friend Vec2 operator*(const float &lhs, Vec2 rhs);  //elementwise multiplication
            friend Vec2 operator*(Vec2 lhs, const float &rhs);  //elementwise multiplication
            friend Vec2 operator*(Vec2 lhs, const Vec2 &rhs);   //elementwise multiplication
            friend Vec2 operator/(const float &lhs, Vec2 rhs);  //elementwise division
            friend Vec2 operator/(Vec2 lhs, const float &rhs);  //elementwise division
            friend Vec2 operator/(Vec2 lhs, const Vec2 &rhs);   //elementwise division

            friend std::ostream &operator<<(std::ostream &os, const Vec2 &vec2);

        private:
            float data[2]{0.0, 0.0};
            friend Matrix4;
            friend Vec3;
            friend Vec4;

        };

    class Vec3 {
    public:
        explicit Vec3(float x = 0.0, float y = 0.0, float z = 0.0);

        //get index
        float get(int index) const;

        template<int index>
        float get() const noexcept {
            assert(index <= 3 & index >= 0);
            return this->data[index];
        }

        float dot(const Vec3 &rhs) const;

        static float dot(const Vec3 &lhs, const Vec3 &rhs);

        Vec3 cross(const Vec3 &rhs) const;

        Vec3 cross(const Vec3 &lhs, const Vec3 &rhs);

        //operators
        bool operator==(const Vec3 &rhs) const;

        bool operator!=(const Vec3 &rhs) const;

        Vec3 operator-() const;

        Vec3 &operator+=(const Vec3 &rhs); // elementwise addition
        Vec3 &operator-=(const Vec3 &rhs); // elementwise subtraction
        Vec3 &operator*=(float rhs); // elementwise multiplication
        Vec3 &operator*=(const Vec3 &rhs); // elementwise multiplication
        Vec3 &operator/=(float rhs); // elementwise division
        Vec3 &operator/=(const Vec3 &rhs); // elementwise division

        friend Vec3 operator+(Vec3 lhs, const Vec3 &rhs);   //elementwise addition
        friend Vec3 operator-(Vec3 lhs, const Vec3 &rhs);   //elementwise subtraction
        friend Vec3 operator*(const float &lhs, Vec3 rhs);  //elementwise multiplication
        friend Vec3 operator*(Vec3 lhs, const float &rhs);  //elementwise multiplication
        friend Vec3 operator*(Vec3 lhs, const Vec3 &rhs);   //elementwise multiplication
        friend Vec3 operator/(const float &lhs, Vec3 rhs);  //elementwise division
        friend Vec3 operator/(Vec3 lhs, const float &rhs);  //elementwise division
        friend Vec3 operator/(Vec3 lhs, const Vec3 &rhs);   //elementwise division



        friend std::ostream &operator<<(std::ostream &os, const Vec3 &vec3);

    private:
        float data[3]{0.0, 0.0, 0.0};;
        friend Matrix4;
        friend Vec2;
        friend Vec4;
        //float x,y,z;
    };

    class Vec4 {
    public:
        explicit Vec4(float x = 0.0, float y = 0.0, float z = 0.0, float w = 0.0);

        explicit Vec4(Vec3 &vec3, float w = 0.0);

        // Copy conclassor
        Vec4(const Vec4 &p1);

        //get index
        float get(int index) const;

        template<int index>
        void set(float value) {
            assert(index <= 3 & index >= 0);
#if SET_DATA
            __m128 b = _mm_set_ss(value);
            this->data = _mm_insert_ps(this->data, b, (index << 4)); //TODO: test!
#else
            this->data[index] = value;
#endif
        }

        //Todo: check if this is faster?:
        template<int index>
        float get() const noexcept {
            assert(index <= 3 & index >= 0);
#if SET_DATA
            return _mm_cvtss_f32(_mm_shuffle_ps(this->data, this->data, _MM_SHUFFLE(0, 0, 0, index)));
#else
            return this->data[index];
#endif
        }

        float dot(const Vec4 &rhs) const;

        static float dot(const Vec4 &lhs, const Vec4 &rhs);

        //compute the cross product as if ti was a Vec3 (only first 3 elements will be used)
        Vec4 cross(const Vec4 &rhs) const;

        static Vec4 cross(const Vec4 &lhs, const Vec4 &rhs);

        //cosine of angle between 2 vectors
        float angle(const Vec4 &rhs) const;

        static float angle(const Vec4 &v1, const Vec4 &v2);

        float abs() const;

        static float abs(const Vec4 &vec);

        //sum of all values
        float sum() const;

        static float sum(const Vec4 &vec);

        //sum of first 3 values (sometimes needed when only xyz is required
        float sum3() const;

        static float sum3(const Vec4 &vec);

        //max of all values
        float max() const;

        static float max(const Vec4 &vec);

        //max of first 3 values (sometimes needed when only xyz is required
        float max3() const;

        static float max3(const Vec4 &vec);

        //min of all values
        float min() const;

        static float min(const Vec4 &vec);

        //min of first 3 values (sometimes needed when only xyz is required
        float min3() const;

        static float min3(const Vec4 &vec);

        //square root elementwise
        static Vec4 sqrt(Vec4 &vec);

        //trigonometric functions
        static Vec4 sin(Vec4 &vec);
        static Vec4 cos(Vec4 &vec);
        static Vec4 acos(Vec4 &vec);
        static Vec4 tan(Vec4 &vec);

        //normalize vector
        void normalize();

        //operators
        bool operator==(const Vec4 &rhs) const;

        bool operator!=(const Vec4 &rhs) const;

        Vec4 operator-() const;

        Vec4 &operator+=(const Vec4 &rhs); // elementwise addition
        Vec4 &operator-=(const Vec4 &rhs); // elementwise subtraction
        Vec4 &operator*=(float rhs); // elementwise multiplication
        Vec4 &operator*=(const Vec4 &rhs); // elementwise multiplication
        Vec4 &operator/=(float rhs); // elementwise division
        Vec4 &operator/=(const Vec4 &rhs); // elementwise division

        friend Vec4 operator+(Vec4 lhs, const Vec4 &rhs);   //elementwise addition
        friend Vec4 operator+(Vec4 lhs, const float rhs);   //elementwise addition
        friend Vec4 operator+(const float lhs, Vec4 rhs);   //elementwise addition
        friend Vec4 operator-(Vec4 lhs, const Vec4 &rhs);   //elementwise subtraction
        friend Vec4 operator-(Vec4 lhs, const float rhs);   //elementwise addition
        friend Vec4 operator-(const float lhs, Vec4 rhs);   //elementwise addition
        friend Vec4 operator*(const float &lhs, Vec4 rhs);  //elementwise multiplication
        friend Vec4 operator*(Vec4 lhs, const float &rhs);  //elementwise multiplication
        friend Vec4 operator*(Vec4 lhs, const Vec4 &rhs);   //elementwise multiplication
        friend Vec4 operator/(const float &lhs, Vec4 rhs);  //elementwise division
        friend Vec4 operator/(Vec4 lhs, const float &rhs);  //elementwise division
        friend Vec4 operator/(Vec4 lhs, const Vec4 &rhs);   //elementwise division


        //special vectors
        static Vec4 xAxis();

        static Vec4 yAxis();

        static Vec4 zAxis();


        friend std::ostream &operator<<(std::ostream &os, const Vec4 &vec4);

    private:

#if SET_DATA
        __m128 data;
#else
        float data[4] {0.0,0.0,0.0,0.0};
#endif
        friend Matrix4;
        friend Vec2;
        friend Vec3;

        //float x,y,z,w;
    };
}



#endif //I_COMPUTERGRAPHICS_VECTOR_H
