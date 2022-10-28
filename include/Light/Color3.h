//
// Created by Maarten Van Loo on 7/10/2022.
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
        Color3(const Vec3 &v);
        Color3(const Vec4 &v);

        void add(const Color3 &color);


        void clear();

        void openTransaction();

        void closeTransaction();

        void rollBackTransaction();

        //multiplication
        Color3 &operator*=(const Vec3 &rhs);                    // elementwise multiplication
        Color3 &operator*=(const Vec4 &rhs);                    // elementwise multiplication
        Color3 &operator*=(double rhs);                          // elementwise multiplication
        friend Color3 operator*(Color3 lhs, const Vec3 &rhs);   //elementwise multiplication
        friend Color3 operator*(const Vec3 &lhs, Color3 rhs);   //elementwise multiplication
        friend Color3 operator*(Color3 lhs, const Vec4 &rhs);   //elementwise multiplication
        friend Color3 operator*(const Vec4 &lhs, Color3 rhs);   //elementwise multiplication
        friend Color3 operator*(Color3 lhs, double rhs);         //elementwise subtraction
        friend Color3 operator*(double lhs, Color3 rhs);         //elementwise subtraction

        friend std::ostream &operator<<(std::ostream &os, const Color3 &color3);

        int getRed() const;

        int getGreen() const;

        int getBlue() const;

        void setRed(int red);

        void setGreen(int green);

        void setBlue(int blue);

    private:
        int red = 0;
        int green = 0;
        int blue = 0;

        //transaction variables
        bool transactionOpen = false;
        int accRed  =0; // red   accumulator
        int accGreen=0; // green accumulator
        int accBlue =0; // blue  accumulator
        int n       =0; // number of samples
    };
}
#endif //I_COMPUTERGRAPHICS_COLOR3_H
