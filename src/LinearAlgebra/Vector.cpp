//
// Created by Maarten Van Loo on 30/09/2022.
//

#include <iostream>
#include "LinearAlgebra/Vector.h"
using namespace MRay;
//https://stackoverflow.com/questions/49941645/get-sum-of-values-stored-in-m256d-with-sse-avx/49943540#49943540
inline
double hsum_double_avx(__m256d v) {
    __m128d vlow  = _mm256_castpd256_pd128(v);
    __m128d vhigh = _mm256_extractf128_pd(v, 1); // high 128
    vlow  = _mm_add_pd(vlow, vhigh);     // reduce down to 128

    __m128d high64 = _mm_unpackhi_pd(vlow, vlow);
    return  _mm_cvtsd_f64(_mm_add_sd(vlow, high64));  // reduce to scalar
}

#pragma region Vec2
MRay::Vec2::Vec2(float x, float y) {
    this->data[0] = x;
    this->data[1] = y;
}

float MRay::Vec2::get(int index) const {
    assert(index <= 1 & index >= 0);
    return this->data[index];
}

float MRay::Vec2::dot(const Vec2 &rhs) const {
    return this->data[0] * rhs.data[0] + this->data[1] * rhs.data[1];
}

float MRay::Vec2::dot(const Vec2 &lhs, const Vec2 &rhs) {
    return lhs.dot(rhs);
}

#pragma region MRay::operators
bool MRay::Vec2::operator==(const Vec2 &rhs) const {
    return this->data[0] == rhs.data[0] &&
           this->data[1] == rhs.data[1];
}
bool MRay::Vec2::operator!=(const Vec2 &rhs) const {
    return !(rhs == *this);
}

Vec2 MRay::Vec2::operator-() const {
    Vec2 res = *this;
    res.data[0] = -res.data[0];
    res.data[1] = -res.data[1];
    return res;
}
Vec2& MRay::Vec2::operator+=(const Vec2& rhs) {
    this->data[0]+=rhs.data[0];
    this->data[1]+=rhs.data[1];
    return *this;
}
Vec2& MRay::Vec2::operator-=(const Vec2& rhs) {
    this->data[0]-=rhs.data[0];
    this->data[1]-=rhs.data[1];
    return *this;
}
Vec2 &MRay::Vec2::operator*=(const float rhs) {
    this->data[0]*=rhs;
    this->data[1]*=rhs;
    return *this;
}
Vec2 &MRay::Vec2::operator*=(const Vec2& rhs) {
    this->data[0]*=rhs.data[0];
    this->data[1]*=rhs.data[1];
    return *this;
}
Vec2 &MRay::Vec2::operator/=(const float rhs) {
    this->data[0]/=rhs;
    this->data[1]/=rhs;
    return *this;
}
Vec2 &MRay::Vec2::operator/=(const Vec2& rhs) {
    this->data[0]/=rhs.data[0];
    this->data[1]/=rhs.data[1];
    return *this;
}

Vec2 MRay::operator+(Vec2 lhs, const Vec2 &rhs) {
    lhs += rhs;
    return lhs;
}
Vec2 MRay::operator-(Vec2 lhs, const Vec2 &rhs) {
    lhs-=rhs;
    return lhs;
}
Vec2 MRay::operator*(const float &lhs, Vec2 rhs) {
    rhs*=lhs;
    return rhs;
}
Vec2 MRay::operator*(Vec2 lhs, const float &rhs) {
    lhs*=rhs;
    return lhs;
}
Vec2 MRay::operator*(Vec2 lhs, const Vec2 &rhs) {
    lhs*=rhs;
    return lhs;
}
Vec2 MRay::operator/(Vec2 lhs, const float &rhs) {
    lhs/=rhs;
    return lhs;
}
Vec2 MRay::operator/(const float &lhs, Vec2 rhs ) {
    rhs.data[0] = lhs/rhs.data[0];
    rhs.data[1] = lhs/rhs.data[1];
    return rhs;
}
Vec2 MRay::operator/(Vec2 lhs, const Vec2 &rhs) {
    lhs/=rhs;
    return lhs;
}
#pragma endregion

std::ostream &MRay::operator<<(std::ostream &os, const Vec2 &vec2) {
    os <<"[" << vec2.data[0] << ", " << vec2.data[1] << "]";
    return os;
}


#pragma endregion

#pragma region Vec3

MRay::Vec3::Vec3(float x, float y, float z) {
    this->data[0] = x;
    this->data[1] = y;
    this->data[2] = z;
}
float MRay::Vec3::get(int index) const {
    assert(index <= 2 & index >= 0);
    return this->data[index];
}

float MRay::Vec3::dot(const Vec3 &rhs) const {
    return this->data[0] * rhs.data[0] + this->data[1] * rhs.data[1] +  this->data[2] * rhs.data[2];
}
float MRay::Vec3::dot(const Vec3 &lhs, const Vec3 &rhs) {
    return lhs.dot(rhs);
}

Vec3 MRay::Vec3::cross(const Vec3& rhs) const {
    return Vec3(this->data[1]*rhs.data[2] - this->data[2]*rhs.data[1],
                this->data[2]*rhs.data[0] - this->data[0]*rhs.data[2],
                this->data[0]*rhs.data[1] - this->data[1]*rhs.data[0]);
}

Vec3 MRay::Vec3::cross(const Vec3& lhs, const Vec3& rhs) {
    return Vec3(lhs.data[1]*rhs.data[2] - lhs.data[2]*rhs.data[1],
                lhs.data[2]*rhs.data[0] - lhs.data[0]*rhs.data[2],
                lhs.data[0]*rhs.data[1] - lhs.data[1]*rhs.data[0]);
}

#pragma region MRay::operators
bool MRay::Vec3::operator==(const Vec3 &rhs) const {
    return this->data[0] == rhs.data[0] &&
           this->data[1] == rhs.data[1] &&
           this->data[2] == rhs.data[2];
}
bool MRay::Vec3::operator!=(const Vec3 &rhs) const {
    return !(rhs == *this);
}

Vec3 MRay::Vec3::operator-() const {
    Vec3 res = *this;
    res.data[0] = -res.data[0];
    res.data[1] = -res.data[1];
    res.data[2] = -res.data[2];
    return res;
}
Vec3& MRay::Vec3::operator+=(const Vec3& rhs) {
    this->data[0]+=rhs.data[0];
    this->data[1]+=rhs.data[1];
    this->data[2]+=rhs.data[2];
    return *this;
}
Vec3& MRay::Vec3::operator-=(const Vec3& rhs) {
    this->data[0]-=rhs.data[0];
    this->data[1]-=rhs.data[1];
    this->data[2]-=rhs.data[2];
    return *this;
}
Vec3 &MRay::Vec3::operator*=(const float rhs) {
    this->data[0]*=rhs;
    this->data[1]*=rhs;
    this->data[2]*=rhs;
    return *this;
}
Vec3 &MRay::Vec3::operator*=(const Vec3& rhs) {
    this->data[0]*=rhs.data[0];
    this->data[1]*=rhs.data[1];
    this->data[2]*=rhs.data[2];
    return *this;
}
Vec3 &MRay::Vec3::operator/=(const float rhs) {
    this->data[0]/=rhs;
    this->data[1]/=rhs;
    this->data[2]/=rhs;
    return *this;
}
Vec3 &MRay::Vec3::operator/=(const Vec3& rhs) {
    this->data[0]/=rhs.data[0];
    this->data[1]/=rhs.data[1];
    this->data[2]/=rhs.data[2];
    return *this;
}

Vec3 MRay::operator+(Vec3 lhs, const Vec3 &rhs) {
    lhs += rhs;
    return lhs;
}
Vec3 MRay::operator-(Vec3 lhs, const Vec3 &rhs) {
    lhs-=rhs;
    return lhs;
}
Vec3 MRay::operator*(const float &lhs, Vec3 rhs) {
    rhs*=lhs;
    return rhs;
}
Vec3 MRay::operator*(Vec3 lhs, const float &rhs) {
    lhs*=rhs;
    return lhs;
}
Vec3 MRay::operator*(Vec3 lhs, const Vec3 &rhs) {
    lhs*=rhs;
    return lhs;
}
Vec3 MRay::operator/(Vec3 lhs, const float &rhs) {
    lhs/=rhs;
    return lhs;
}
Vec3 MRay::operator/(const float &lhs, Vec3 rhs ) {
    rhs.data[0] = lhs/rhs.data[0];
    rhs.data[1] = lhs/rhs.data[1];
    rhs.data[2] = lhs/rhs.data[2];
    return rhs;
}
Vec3 MRay::operator/(Vec3 lhs, const Vec3 &rhs) {
    lhs/=rhs;
    return lhs;
}
#pragma endregion

std::ostream &MRay::operator<<(std::ostream &os, const Vec3 &vec3) {
    os <<"[" << vec3.data[0] << ", " << vec3.data[0] << ", " << vec3.data[0] << "]";
    return os;
}



#pragma endregion


#pragma region Vec4
MRay::Vec4::Vec4(float x, float y, float z, float w) {
#if SET_DATA
    // this->data = _mm256_set_pd (w,z,y,x); //double
    this->data = _mm_set_ps (w,z,y,x); //float
#else
    this->data[0] = x;
    this->data[1] = y;
    this->data[2] = z;
    this->data[3] = w;
#endif

}
MRay::Vec4::Vec4(Vec3 &vec3, float w) {
#if SET_DATA
    //double:
    //this->data = _mm256_set_pd(w, vec3.data[2],vec3.data[1],vec3.data[0]); //double

    //float:
    this->data = _mm_set_ps(w, vec3.data[2],vec3.data[1],vec3.data[0]); //float
#else
    this->data[0] = vec3.data[0];
    this->data[1] = vec3.data[1];
    this->data[2] = vec3.data[2];
    this->data[3] = w;
#endif

}

MRay::Vec4::Vec4(const Vec4 &p1) {
#if SET_DATA
    //float && double:
    this->data = p1.data;
#else
    this->data[0] = p1.data[0];
    this->data[1] = p1.data[1];
    this->data[2] = p1.data[2];
    this->data[3] = p1.data[3];
#endif

}

float MRay::Vec4::get(const int index) const{
    assert(index <= 3 & index >= 0);
#if SET_DATA
    // double:
    //return _mm256_cvtsd_f64(_mm256_shuffle_pd(this->data,this->data, _MM_SHUFFLE(0, 0, 0, index)));
    //float:
    //_mm_cvtss_f32(_mm_shuffle_ps(this->getData(),this->getData(), _MM_SHUFFLE(0, 0, 0, index)));

    float tmp[4];
    _mm_store_ps(tmp, this->data);
    return tmp[index];
#else
    return this->data[index];
#endif
}


#pragma region Vector operations
float MRay::Vec4::dot(const Vec4 &rhs) const {
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    __m128 temp = _mm_dp_ps(this->data,rhs.data,0x71); //store result in lowest bits, use only the first 3 values (lowest 96 bits);
    return _mm_cvtss_f32(temp);
#else
    __m128 lhs_ps = _mm_set_ps(this->data[3], this->data[2], this->data[1], this->data[0]); //float
    __m128 rhs_ps = _mm_set_ps(rhs.data[3],rhs.data[2],rhs.data[1],rhs.data[0]); //float
    //double:
    //__m256d temp = _mm256_mul_pd(this->data, rhs.data);
    //return hsum_double_avx(temp);

    //float:
    __m128 temp = _mm_dp_ps(lhs_ps,rhs_ps,0x71); //store result in lowest bits, use only the first 3 values (lowest 96 bits);
    return _mm_cvtss_f32(temp);
#endif
#else
    return
        this->data[0] * rhs.data[0] +
        this->data[1] * rhs.data[1] +
        this->data[2] * rhs.data[2];
#endif


}
float MRay::Vec4::dot(const Vec4 &lhs, const Vec4 &rhs) {
    return lhs.dot(rhs);
}

Vec4 MRay::Vec4::cross(const Vec4 &rhs) const {
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    __m128 tmp0 = _mm_shuffle_ps(this->data,this->data,_MM_SHUFFLE(3,0,2,1));
    __m128 tmp1 = _mm_shuffle_ps(rhs.data,rhs.data,_MM_SHUFFLE(3,1,0,2));
    __m128 tmp2 = _mm_mul_ps(tmp0,rhs.data);
    __m128 tmp3 = _mm_mul_ps(tmp0,tmp1);
    __m128 tmp4 = _mm_shuffle_ps(tmp2,tmp2,_MM_SHUFFLE(3,0,2,1));
    Vec4 res;
    res.data = _mm_sub_ps(tmp3,tmp4);
    return res;
#else
    // float
    // https://geometrian.com/programming/tutorials/cross-product/index.php
    __m128 data_ps = _mm_set_ps(this->data[3],this->data[2],this->data[1],this->data[0]);
    __m128 rhs_ps = _mm_set_ps(rhs.data[3],rhs.data[2],rhs.data[1],rhs.data[0]);
    __m128 tmp0 = _mm_shuffle_ps(data_ps,data_ps,_MM_SHUFFLE(3,0,2,1));
    __m128 tmp1 = _mm_shuffle_ps(rhs_ps,rhs_ps,_MM_SHUFFLE(3,1,0,2));
    __m128 tmp2 = _mm_mul_ps(tmp0,rhs_ps);
    __m128 tmp3 = _mm_mul_ps(tmp0,tmp1);
    __m128 tmp4 = _mm_shuffle_ps(tmp2,tmp2,_MM_SHUFFLE(3,0,2,1));
    Vec4 res;
    _mm_store_ps (res.data, _mm_sub_ps(tmp3,tmp4));
    return res;
#endif
#else
    return Vec4(this->data[1]*rhs.data[2] - this->data[2]*rhs.data[1],
                this->data[2]*rhs.data[0] - this->data[0]*rhs.data[2],
                this->data[0]*rhs.data[1] - this->data[1]*rhs.data[0],
                this->data[3]);
#endif

}

Vec4 MRay::Vec4::cross(const Vec4 &lhs, const Vec4 &rhs) {
    return lhs.cross(rhs);
}

float MRay::Vec4::angle(const Vec4 &rhs) const {
    return this->dot(rhs)/(this->abs()*abs(rhs));;
}
float MRay::Vec4::angle(const Vec4 &v1, const Vec4 &v2) {
    return v1.angle(v2);
}
#pragma endregion

#pragma region math
float MRay::Vec4::abs() const {
    /*return std::sqrt(this->data[0] * this->data[0] +
                     this->data[1] * this->data[1] +
                     this->data[2] * this->data[2] +
                     this->data[3] * this->data[3]);*/
    return std::sqrt(this->dot(*this));
}

float MRay::Vec4::abs(const Vec4 &vec) {
    return vec.abs();
}

float MRay::Vec4::sum() const{
#if SSE_AVX_EXTENSIONS
    return this->get(0)+this->get(1)+this->get(2)+this->get(3);
#else
    return this->data[0] + this->data[1] + this->data[2] + this->data[3];
#endif
}
float MRay::Vec4::sum(const Vec4 &vec) {
    return vec.sum();
}

float MRay::Vec4::sum3() const {
#if SSE_AVX_EXTENSIONS
    return this->get(0)+this->get(1)+this->get(2);
#else
    return this->data[0] + this->data[1] + this->data[2];
#endif
}

float MRay::Vec4::sum3(const Vec4 &vec) {
    return vec.sum3();
}

float MRay::Vec4::max() const {
#if SSE_AVX_EXTENSIONS
    //float tmp[4]
    //_mm_store_ps (this->data, tmp);
    //return std::min(std::min(tmp.data[0],tmp.data[1]),std::min(tmp.data[2],tmp.data[3])); //other option if get doesn't work fine
    //notice, only 1 cycle latency for get in avx, without avx it is equivalent to [] => probably fine?
    return std::max(std::max(this->get(0),this->get(1)),std::max(this->get(2),this->get(3)));
#else
    return std::max(std::max(this->data[0],this->data[1]),std::max(this->data[2],this->data[3]));
#endif
}
float MRay::Vec4::max(const Vec4 &vec) {
    return vec.max();
}

float MRay::Vec4::max3() const {
#if SSE_AVX_EXTENSIONS
    //notice, only 1 cycle latency for get in avx, without avx it is equivalent to [] => probably fine?
    return std::max(std::max(this->get(0),this->get(1)),this->get(2));
#else
    return std::max(std::max(this->data[0],this->data[1]),this->data[2]);
#endif
}
float MRay::Vec4::max3(const Vec4 &vec) {
    return vec.max3();
}

float MRay::Vec4::min() const {
#if SSE_AVX_EXTENSIONS
    //float tmp[4]
    //_mm_store_ps (this->data, tmp);
    //return std::min(std::min(tmp.data[0],tmp.data[1]),std::min(tmp.data[2],tmp.data[3])); //other option if get doesn't work fine
    //notice, only 1 cycle latency for get in avx, without avx it is equivalent to [] => probably fine?
    return std::min(std::min(this->get(0),this->get(1)),std::min(this->get(2),this->get(3)));
#else
    return std::min(std::min(this->data[0],this->data[1]),std::min(this->data[2],this->data[3]));
#endif
}
float MRay::Vec4::min(const Vec4 &vec) {
    return vec.min();
}
float MRay::Vec4::min3() const {
#if SSE_AVX_EXTENSIONS
    //notice, only 1 cycle latency for get in avx, without avx it is equivalent to [] => probably fine?
    return std::min(std::min(this->get(0),this->get(1)),this->get(2));
#else
    return std::min(std::min(this->data[0],this->data[1]),this->data[2]);
#endif
}
float MRay::Vec4::min3(const Vec4 &vec) {
    return vec.min3();
}
#pragma endregion

#pragma region MRay::operators
bool MRay::Vec4::operator==(const Vec4 &rhs) const {
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    __m128 comp = _mm_cmpeq_ps(this->data,rhs.data);
    return !_mm_testz_ps(comp,comp); //Test not all zero's (value = -1 when equal, 0 otherwise)
#else
    __m128 lhs_ps = _mm_set_ps(this->data[3], this->data[2], this->data[1], this->data[0]); //float
    __m128 rhs_ps = _mm_set_ps(rhs.data[3],rhs.data[2],rhs.data[1],rhs.data[0]);
    rhs_ps = _mm_cmpeq_ps(lhs_ps,rhs_ps);
    return !_mm_testz_ps(rhs_ps,rhs_ps); //Test not all zero's (value = -1 when equal, 0 otherwise)
#endif
#else
    return this->data[0] == rhs.data[0] &&
            this->data[1] == rhs.data[1] &&
            this->data[2] == rhs.data[2] &&
            this->data[3] == rhs.data[3];
#endif
}
bool MRay::Vec4::operator!=(const Vec4 &rhs) const {
    return !(rhs == *this);
}

Vec4 MRay::Vec4::operator-() const {
    Vec4 res = *this;
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    __m128 negate_ps = _mm_set_ps(-1.0f, -1.0f, -1.0f, -1.0f); //float
    res.data = _mm_mul_ps (res.data, negate_ps);
#else
    // __m256d negate_pd = _mm256_set_pd (-1.0,-1.0,-1.0,-1.0); //double
    // res.data = _mm256_mul_pd(res.data, negate_pd);
    __m128 negate_ps = _mm_set_ps(-1.0f, -1.0f, -1.0f, -1.0f); //float
    __m128 res_ps = _mm_set_ps(res.data[3],res.data[2],res.data[1],res.data[0]);
    res_ps = _mm_mul_ps (res_ps, negate_ps);
    _mm_store_ps (res.data, res_ps);
#endif
#else
    res.data[0] = -res.data[0];
    res.data[1] = -res.data[1];
    res.data[2] = -res.data[2];
    res.data[3] = -res.data[3];
#endif
    return res;



}
Vec4& MRay::Vec4::operator+=(const Vec4& rhs) {
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    this->data = _mm_add_ps(this->data,rhs.data); //float
#else
    // this->data = _mm_add256_pd(this->data, rhs.data); //double
    __m128 lhs_ps = _mm_set_ps(this->data[3], this->data[2], this->data[1], this->data[0]); //float
    __m128 rhs_ps = _mm_set_ps(rhs.data[3],rhs.data[2],rhs.data[1],rhs.data[0]);
    rhs_ps = _mm_add_ps(lhs_ps,rhs_ps); //float
    _mm_store_ps (this->data, rhs_ps);
#endif
#else
    this->data[0]+=rhs.data[0];
    this->data[1]+=rhs.data[1];
    this->data[2]+=rhs.data[2];
    this->data[3]+=rhs.data[3];
#endif
    return *this;

}
Vec4& MRay::Vec4::operator-=(const Vec4& rhs) {
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    this->data = _mm_sub_ps(this->data,rhs.data); //float
#else
    // this->data = _mm_sub256_pd(this->data, rhs.data); //double
    __m128 lhs_ps = _mm_set_ps(this->data[3], this->data[2], this->data[1], this->data[0]); //float
    __m128 rhs_ps = _mm_set_ps(rhs.data[3],rhs.data[2],rhs.data[1],rhs.data[0]);
    rhs_ps = _mm_sub_ps(lhs_ps, rhs_ps), //float
    _mm_store_ps (this->data, rhs_ps);
#endif
#else
    this->data[0]-=rhs.data[0];
    this->data[1]-=rhs.data[1];
    this->data[2]-=rhs.data[2];
    this->data[3]-=rhs.data[3];
#endif
    return *this;


}
Vec4 &MRay::Vec4::operator*=(const float rhs) {
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    __m128 rhs_ps = _mm_set_ps(rhs, rhs, rhs, rhs); //float
    this->data = _mm_mul_ps(this->data,rhs_ps); //float
#else
    // __m256d rhs_pd = _mm256_set_pd (rhs,rhs,rhs,rhs); //double
    // this->data = _mm256_mul_pd(res.data, rhs_pd);
    __m128 lhs_ps = _mm_set_ps(this->data[3], this->data[2], this->data[1], this->data[0]); //float
    __m128 rhs_ps = _mm_set_ps(rhs, rhs, rhs, rhs); //float
    rhs_ps = _mm_mul_ps (lhs_ps , rhs_ps);
    _mm_store_ps (this->data, rhs_ps);
#endif
#else
    this->data[0]*=rhs;
    this->data[1]*=rhs;
    this->data[2]*=rhs;
    this->data[3]*=rhs;
#endif
    return *this;



}
Vec4 &MRay::Vec4::operator*=(const Vec4& rhs) {
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    this->data = _mm_mul_ps(this->data,rhs.data); //float
#else
    __m128 lhs_ps = _mm_set_ps(this->data[3], this->data[2], this->data[1], this->data[0]); //float
    __m128 rhs_ps = _mm_set_ps(rhs.data[3],rhs.data[2],rhs.data[1],rhs.data[0]);
    // __m256d rhs_pd = _mm256_set_pd (rhs,rhs,rhs,rhs); //double
    // this->data = _mm256_mul_pd(res.data, rhs.data);
    rhs_ps = _mm_mul_ps (lhs_ps , rhs_ps);
    _mm_store_ps (this->data, rhs_ps);
#endif
#else
    this->data[0]*=rhs.data[0];
    this->data[1]*=rhs.data[1];
    this->data[2]*=rhs.data[2];
    this->data[3]*=rhs.data[3];
#endif
    return *this;


}
Vec4 &MRay::Vec4::operator/=(const float rhs) {
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    __m128 rhs_ps = _mm_set_ps(rhs, rhs, rhs, rhs); //float
    this->data = _mm_div_ps(this->data,rhs_ps); //float
#else
    __m128 lhs_ps = _mm_set_ps(this->data[3], this->data[2], this->data[1], this->data[0]); //float
    __m128 rhs_ps = _mm_set_ps(rhs,rhs,rhs,rhs);
    // __m256d rhs_pd = _mm256_set_pd (rhs,rhs,rhs,rhs); //double
    // this->data = _mm256_div_pd(this->data, rhs_pd);
    rhs_ps = _mm_div_ps(lhs_ps, rhs_ps);   // float
    _mm_store_ps (this->data, rhs_ps);
#endif
#else
    this->data[0]/=rhs;
    this->data[1]/=rhs;
    this->data[2]/=rhs;
    this->data[3]/=rhs;
#endif
    return *this;

}
Vec4 &MRay::Vec4::operator/=(const Vec4& rhs) {
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    this->data = _mm_div_ps(this->data,rhs.data); //float
#else
    __m128 lhs_ps = _mm_set_ps(this->data[3], this->data[2], this->data[1], this->data[0]); //float
    __m128 rhs_ps = _mm_set_ps(rhs.data[3],rhs.data[2],rhs.data[1],rhs.data[0]);
    // this->data = _mm256_div_pd(this->data, rhs.data); // double
    rhs_ps = _mm_div_ps(lhs_ps, rhs_ps);   // float
    _mm_store_ps (this->data, rhs_ps);
#endif
#else
    this->data[0]/=rhs.data[0];
    this->data[1]/=rhs.data[1];
    this->data[2]/=rhs.data[2];
    this->data[3]/=rhs.data[3];
#endif
    return *this;
}

Vec4 MRay::operator+(Vec4 lhs, const Vec4 &rhs) {
    lhs += rhs;
    return lhs;
}
Vec4 MRay::operator+(Vec4 lhs, const float rhs) {
    lhs += Vec4(rhs,rhs,rhs,rhs);
    return lhs;
}
Vec4 MRay::operator+(const float lhs, Vec4 rhs) {
    rhs += Vec4(lhs,lhs,lhs,lhs);
    return rhs;
}
Vec4 MRay::operator-(Vec4 lhs, const Vec4 &rhs) {
    lhs-=rhs;
    return lhs;
}
Vec4 MRay::operator-(Vec4 lhs, const float rhs) {
    lhs -= Vec4(rhs,rhs,rhs,rhs);
    return lhs;
}
Vec4 MRay::operator-(const float lhs, Vec4 rhs) {
    rhs -= Vec4(lhs,lhs,lhs,lhs);
    return rhs;
}
Vec4 MRay::operator*(const float &lhs, Vec4 rhs) {
    rhs*=lhs;
    return rhs;
}
Vec4 MRay::operator*(Vec4 lhs, const float &rhs) {
    lhs*=rhs;
    return lhs;
}
Vec4 MRay::operator*(Vec4 lhs, const Vec4 &rhs) {
    lhs*=rhs;
    return lhs;
}
Vec4 MRay::operator/(Vec4 lhs, const float &rhs) {
    lhs/=rhs;
    return lhs;
}
Vec4 MRay::operator/(const float &lhs, MRay::Vec4 rhs ) {
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    __m128 lhs_ps = _mm_set_ps(lhs, lhs, lhs, lhs); //float
    rhs.data = _mm_div_ps(lhs_ps, rhs.data);
#else
    // __m256d lhs_pd = _mm256_set_pd (lhs, lhs, lhs, lhs); //double
    // this->data = _mm256_div_pd(lhs_pd, this->data);
     __m128 lhs_ps = _mm_set_ps(lhs, lhs, lhs, lhs); //float
     __m128 rhs_ps = _mm_set_ps(rhs.data[3],rhs.data[2],rhs.data[1],rhs.data[0]);
     rhs_ps = _mm_div_ps(lhs_ps, rhs_ps);
    _mm_store_ps (rhs.data, rhs_ps);
#endif
#else
    rhs.data[0] = lhs/rhs.data[0];
    rhs.data[1] = lhs/rhs.data[1];
    rhs.data[2] = lhs/rhs.data[2];
    rhs.data[3] = lhs/rhs.data[3];
#endif
    return rhs;
}
Vec4 MRay::operator/(Vec4 lhs, const Vec4 &rhs) {
    lhs/=rhs;
    return lhs;
}

#pragma endregion

std::ostream &MRay::operator<<(std::ostream &os, const Vec4 &vec4) {
#if SET_DATA
    //AVX float:
    float tmp[4];
    _mm_store_ps (tmp,vec4.data);
    os <<"[" << tmp[0] << ", " << tmp[1] << ", " << tmp[2] << ", " << tmp[3] << "]";
#else
    os <<"[" << vec4.data[0] << ", " << vec4.data[1] << ", " << vec4.data[2] << ", " << vec4.data[3] << "]";
#endif
    return os;

}

Vec4 MRay::Vec4::xAxis() {
    return Vec4(1,0,0,0);
}
Vec4 MRay::Vec4::yAxis() {
    return Vec4(0,1,0,0);
}
Vec4 MRay::Vec4::zAxis() {
    return Vec4(0,0,1,0);
}

void MRay::Vec4::normalize() {
    (*this) = (*this)/this->abs();
}

Vec4 Vec4::sqrt(Vec4 &vec) {
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    Vec4 res;
    res.data = _mm_sqrt_ps(vec.data);
    return res;
#else
    return Vec4(std::sqrt(vec.data[0]),
                std::sqrt(vec.data[1]),
                std::sqrt(vec.data[2]),
                std::sqrt(vec.data[3]);
#endif
#else
    return Vec4(std::sqrt(vec.data[0]),
                std::sqrt(vec.data[1]),
                std::sqrt(vec.data[2]),
                std::sqrt(vec.data[3]);
#endif
}

Vec4 Vec4::sin(Vec4 &vec) {
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    Vec4 res;
    res.data = _mm_sin_ps(vec.data);
    return res;
#else
    return Vec4(std::sin(vec.data[0]),
                std::sin(vec.data[1]),
                std::sin(vec.data[2]),
                std::sin(vec.data[3]);
#endif
#else
    return Vec4(std::sin(vec.data[0]),
                std::sin(vec.data[1]),
                std::sin(vec.data[2]),
                std::sin(vec.data[3]);
#endif
}

Vec4 Vec4::cos(Vec4 &vec) {
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    Vec4 res;
    res.data = _mm_cos_ps(vec.data);
    return res;
#else
    return Vec4(std::cos(vec.data[0]),
                std::cos(vec.data[1]),
                std::cos(vec.data[2]),
                std::cos(vec.data[3]);
#endif
#else
    return Vec4(std::cos(vec.data[0]),
                std::cos(vec.data[1]),
                std::cos(vec.data[2]),
                std::cos(vec.data[3]);
#endif
}


Vec4 Vec4::acos(Vec4 &vec) {
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    Vec4 res;
    res.data = _mm_acos_ps(vec.data);
    return res;
#else
    return Vec4(std::acos(vec.data[0]),
                std::acos(vec.data[1]),
                std::acos(vec.data[2]),
                std::acos(vec.data[3]);
#endif
#else
    return Vec4(std::acos(vec.data[0]),
                std::acos(vec.data[1]),
                std::acos(vec.data[2]),
                std::acos(vec.data[3]);
#endif
}

Vec4 Vec4::tan(Vec4 &vec) {
#if SSE_AVX_EXTENSIONS
#if SET_DATA
    Vec4 res;
    res.data = _mm_tan_ps(vec.data);
    return res;
#else
    return Vec4(std::tan(vec.data[0]),
                std::tan(vec.data[1]),
                std::tan(vec.data[2]),
                std::tan(vec.data[3]);
#endif
#else
    return Vec4(std::tan(vec.data[0]),
                std::tan(vec.data[1]),
                std::tan(vec.data[2]),
                std::tan(vec.data[3]);
#endif
}




#pragma endregion










