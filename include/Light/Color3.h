//
// Created by maart on 7/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_COLOR3_H
#define I_COMPUTERGRAPHICS_COLOR3_H

#include <cstdint>
#include <Ray.h>
#include <ostream>

namespace MRay {
    struct Color3 {
        Color3();

        Color3(int red, int green, int blue);
        Color3(Vec3 v);

        void add(const Color3 &color);

        void clear();

        void openTransaction();

        void closeTransaction();

        void rollBackTransaction();

        //multiplication
        Color3 &operator*=(const Vec3 &rhs);                    // elementwise multiplication
        Color3 &operator*=(const Vec4 &rhs);                    // elementwise multiplication
        Color3 &operator*=(float rhs);                          // elementwise multiplication
        friend Color3 operator*(Color3 lhs, const Vec3 &rhs);   //elementwise multiplication
        friend Color3 operator*(const Vec3 &lhs, Color3 rhs);   //elementwise multiplication
        friend Color3 operator*(Color3 lhs, const Vec4 &rhs);   //elementwise multiplication
        friend Color3 operator*(const Vec4 &lhs, Color3 rhs);   //elementwise multiplication
        friend Color3 operator*(Color3 lhs, float rhs);         //elementwise subtraction
        friend Color3 operator*(float lhs, Color3 rhs);         //elementwise subtraction

        friend std::ostream &operator<<(std::ostream &os, const Color3 &color3);

        uint8_t red = 0;
        uint8_t green = 0;
        uint8_t blue = 0;
    private:

        //transaction variables
        bool transactionOpen = false;
        int accRed  =0; // red   accumulator
        int accGreen=0; // green accumulator
        int accBlue =0; // blue  accumulator
        int n       =0; // number of samples
    };
}
#endif //I_COMPUTERGRAPHICS_COLOR3_H
