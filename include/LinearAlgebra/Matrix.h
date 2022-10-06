//
// Created by Maarten Van Loo on 2/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_MATRIX_H
#define I_COMPUTERGRAPHICS_MATRIX_H

#include <LinearAlgebra/LinearAlgebra.h>
#include <LinearAlgebra/Vector.h>
#include <ostream>


struct Matrix4{
public:
    bool operator==(const Matrix4 &rhs) const;
    bool operator!=(const Matrix4 &rhs) const;

    float get(int row,int col){
        return this->data[col].get(row);
    };
    template<int row, int col> float get(){
        return this->data[col].get<row>(); //data = column based
    };


    template<int row, int col> float set(float value){
        this->data[col].set<row>(value);
    }
    void set(int col, const Vec4 &vec){
        this->data[col] = vec; //data = column based
    }
    template<int row> void set(const Vec4 &vec){
        //data = column based
        this->data[0].set<row>(vec.get(0));
        this->data[1].set<row>(vec.get(1));
        this->data[2].set<row>(vec.get(2));
        this->data[3].set<row>(vec.get(3));
    }

    //todo: change to column major instead of row major:
    Matrix4& operator *=(const Matrix4& rhs); // matrix multiplication
    Vec4 operator *(const Vec4& rhs) const;  //matrix * vector

    friend std::ostream &operator<<(std::ostream &os, const Matrix4 &matrix4);

private:
    Vec4& operator[](int index);

    Vec4 data[4];
    friend Vec2;
    friend Vec3;
    friend Vec4;
};

#endif //I_COMPUTERGRAPHICS_MATRIX_H
