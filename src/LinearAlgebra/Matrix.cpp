//
// Created by Maarten Van Loo on 2/10/2022.
//

#include <LinearAlgebra/Matrix.h>
#include <iostream>

Vec4& Matrix4::operator[](int index){
    if (index > 3 || index < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    return this->data[index];
}

std::ostream &operator<<(std::ostream &os, const Matrix4 &matrix4) {

    os << "Matrix: " << "\n";
    os << matrix4.data[0] << "\n";
    os << matrix4.data[1] << "\n";
    os << matrix4.data[2] << "\n";
    os << matrix4.data[3] << "\n";

    return os;
}


//https://codereview.stackexchange.com/questions/208565/simd-product-of-a-4%C3%974-matrix-and-a-vector
Vec4 Matrix4::operator*(const Vec4 &rhs) const{
    //should work both for _m128 and float[4] => //TODO:check, still something wrong
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
    //no avx & SSE
    for (int col = 0; col < 4; col ++){
        for(int row = 0; row < 4 ; row ++){
            result.data[row] += this->data[col].data[row] * rhs.data[col];
        }
    }
#endif
    return result;

}

//http://fhtr.blogspot.com/2010/02/4x4-float-matrix-multiplication-using.html
Matrix4 &Matrix4::operator*=(const Matrix4 &rhs) {
    Matrix4 tmp; //defaults to all zero's
#if SSE_AVX_EXTENSIONS
    //TODO: does this always work?
    tmp.data[0] = (*this)*rhs.data[0];
    tmp.data[1] = (*this)*rhs.data[1];
    tmp.data[2] = (*this)*rhs.data[2];
    tmp.data[3] = (*this)*rhs.data[3];

    //TODO: not used, check if correct and profile
    /*for (int i =0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            tmp[i] = Vec4(
                    tmp[j].get(i) + this->data[j].get(0) * rhs.data[0].get(i),
                    tmp[j].get(i) + this->data[j].get(1) * rhs.data[1].get(i),
                    tmp[j].get(i) + this->data[j].get(2) * rhs.data[2].get(i),
                    tmp[j].get(i) + this->data[j].get(3) * rhs.data[3].get(i)
                    );
        }
    }*/
#else
    for (int i =0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            for (int k = 0; k < 4; k++){
                tmp[j].data[i] += this->data[j].data[k] * rhs.data[k].data[i];
            }
        }
    }
#endif
    this->data[0] = tmp.data[0];
    this->data[1] = tmp.data[1];
    this->data[2] = tmp.data[2];
    this->data[3] = tmp.data[3];
    return *this;
}

bool Matrix4::operator==(const Matrix4 &rhs) const {
    for (int i = 0; i < 4; i++){
        if (this->data[i] != rhs.data[i]) return false;
    }
    return true;
}

bool Matrix4::operator!=(const Matrix4 &rhs) const {
    return !(rhs == *this);
}



Vec4 operator*(Matrix4 lhs, Vec4 &rhs) {

    return Vec4();
}


