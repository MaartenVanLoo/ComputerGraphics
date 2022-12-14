//
// Created by Maarten Van Loo on 2/10/2022.
//

#include <LinearAlgebra/Matrix.h>
#include <iostream>
#include <cassert>
using namespace MRay;

std::ostream &MRay::operator<<(std::ostream &os, const Matrix4 &matrix4) {
    os << "Matrix: " << "\n";
    os << "[" << matrix4.data[0].get<0>() <<", "<< matrix4.data[1].get<0>()<<", "<< matrix4.data[2].get<0>()<<", "<< matrix4.data[3].get<0>()<< "]\n";
    os << "[" << matrix4.data[0].get<1>() <<", "<< matrix4.data[1].get<1>()<<", "<< matrix4.data[2].get<1>()<<", "<< matrix4.data[3].get<1>()<< "]\n";
    os << "[" << matrix4.data[0].get<2>() <<", "<< matrix4.data[1].get<2>()<<", "<< matrix4.data[2].get<2>()<<", "<< matrix4.data[3].get<2>()<< "]\n";
    os << "[" << matrix4.data[0].get<3>() <<", "<< matrix4.data[1].get<3>()<<", "<< matrix4.data[2].get<3>()<<", "<< matrix4.data[3].get<3>()<< "]\n";
    return os;
}


//https://codereview.stackexchange.com/questions/208565/simd-product-of-a-4%C3%974-matrix-and-a-vector
Vec4 MRay::Matrix4::operator*(const Vec4 &rhs) const{
    Vec4 result; //init with all zero's
#if SSE_AVX_EXTENSIONS
    __m128 x = _mm_set1_ps(rhs.get<0>());
    __m128 y = _mm_set1_ps(rhs.get<1>());
    __m128 z = _mm_set1_ps(rhs.get<2>());
    __m128 w = _mm_set1_ps(rhs.get<3>());
#if SET_DATA
    __m128 p1 = _mm_mul_ps(x, this->data[0].data);
    __m128 p2 = _mm_mul_ps(y, this->data[1].data);
    __m128 p3 = _mm_mul_ps(z, this->data[2].data);
    __m128 p4 = _mm_mul_ps(w, this->data[3].data);
    result.data = _mm_add_ps(_mm_add_ps(p1, p2), _mm_add_ps(p3, p4));
#else
    __m128 p1 = _mm_mul_ps(x,_mm_set_ps(this->data[0].data[3],this->data[0].data[2],this->data[0].data[1],this->data[0].data[0]));
    __m128 p2 = _mm_mul_ps(y,_mm_set_ps(this->data[1].data[3],this->data[1].data[2],this->data[1].data[1],this->data[1].data[0]));
    __m128 p3 = _mm_mul_ps(z,_mm_set_ps(this->data[2].data[3],this->data[2].data[2],this->data[2].data[1],this->data[2].data[0]));
    __m128 p4 = _mm_mul_ps(w,_mm_set_ps(this->data[3].data[3],this->data[3].data[2],this->data[3].data[1],this->data[3].data[0]));
    _mm_store_ps(result.data, _mm_add_ps(_mm_add_ps(p1, p2), _mm_add_ps(p3, p4)));
#endif
    //data = float[4]
#else
    //no avx & no SSE
    for (int col = 0; col < 4; col ++){
        for(int row = 0; row < 4 ; row ++){
            result.data[row] += this->data[col].data[row] * rhs.data[col];
        }
    }
#endif
    return result;

}

//http://fhtr.blogspot.com/2010/02/4x4-float-matrix-multiplication-using.html
Matrix4 &MRay::Matrix4::operator*=(const Matrix4 &rhs) {
    Matrix4 tmp; //defaults to all zero's

    tmp.data[0] = (*this)*rhs.data[0];
    tmp.data[1] = (*this)*rhs.data[1];
    tmp.data[2] = (*this)*rhs.data[2];
    tmp.data[3] = (*this)*rhs.data[3];

    this->data[0] = tmp.data[0];
    this->data[1] = tmp.data[1];
    this->data[2] = tmp.data[2];
    this->data[3] = tmp.data[3];
    return *this;
}
Matrix4 MRay::operator*(Matrix4 lhs, const Matrix4 &rhs) {
    lhs*=rhs;
    return lhs;
}


bool MRay::Matrix4::operator==(const Matrix4 &rhs) const {
    for (int i = 0; i < 4; i++){
        if (this->data[i] != rhs.data[i]) return false;
    }
    return true;
}

bool MRay::Matrix4::operator!=(const Matrix4 &rhs) const {
    return !(rhs == *this);
}

Matrix4 MRay::Matrix4::identity() {
    Matrix4 mat4;
    mat4.data[0] = Vec4(1,0,0,0);
    mat4.data[1] = Vec4(0,1,0,0);
    mat4.data[2] = Vec4(0,0,1,0);
    mat4.data[3] = Vec4(0,0,0,1);
    return mat4;
}

Matrix4 Matrix4::getTransposed()const{
    Matrix4 transposed;
    transposed.set<0,0>(this->data[0].get<0>());
    transposed.set<0,1>(this->data[0].get<1>());
    transposed.set<0,2>(this->data[0].get<2>());
    transposed.set<0,3>(this->data[0].get<3>());
    transposed.set<1,0>(this->data[1].get<0>());
    transposed.set<1,1>(this->data[1].get<1>());
    transposed.set<1,2>(this->data[1].get<2>());
    transposed.set<1,3>(this->data[1].get<3>());
    transposed.set<2,0>(this->data[2].get<0>());
    transposed.set<2,1>(this->data[2].get<1>());
    transposed.set<2,2>(this->data[2].get<2>());
    transposed.set<2,3>(this->data[2].get<3>());
    transposed.set<3,0>(this->data[3].get<0>());
    transposed.set<3,1>(this->data[3].get<1>());
    transposed.set<3,2>(this->data[3].get<2>());
    transposed.set<3,3>(this->data[3].get<3>());
    return transposed;

}



