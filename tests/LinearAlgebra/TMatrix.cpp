//
// Created by Maarten Van Loo on 5/10/2022.
//

#include <catch2/catch_all.hpp>
#include <iostream>
#include <Utils/Stopwatch.h>
#include <LinearAlgebra/Matrix.h>

#define benchmark false
using namespace MRay;
TEST_CASE("tMatrix"){
    Matrix4 mat1;
    Matrix4 mat2;
    Matrix4 target1;
    Vec4 vec1;
    Vec4 targetVec1;
    SECTION("Getter & setters"){
        mat1.set<0>( 1, 2, 3, 4);
        mat1.set<1>( 5, 6, 7, 8);
        mat1.set<2>( 9,10,11,12);
        mat1.set<3>(13,14,15,16);
        CHECK(mat1.get(0,0) ==  1); CHECK(mat1.get(0,1) ==  2); CHECK(mat1.get(0,2) ==  3);CHECK(mat1.get(0,3) ==  4);
        CHECK(mat1.get(1,0) ==  5); CHECK(mat1.get(1,1) ==  6); CHECK(mat1.get(1,2) ==  7);CHECK(mat1.get(1,3) ==  8);
        CHECK(mat1.get(2,0) ==  9); CHECK(mat1.get(2,1) == 10); CHECK(mat1.get(2,2) == 11);CHECK(mat1.get(2,3) == 12);
        CHECK(mat1.get(3,0) == 13); CHECK(mat1.get(3,1) == 14); CHECK(mat1.get(3,2) == 15);CHECK(mat1.get(3,3) == 16);

        mat1.set<0>( Vec4(11 , 12, 13, 14));
        mat1.set<1>( Vec4(15 , 16, 17, 18));
        mat1.set<2>( Vec4(19 ,110,111,112));
        mat1.set<3>( Vec4(113,114,115,116));
        CHECK(mat1.get<0,0>() ==  11); CHECK(mat1.get<0,1>() ==  12); CHECK(mat1.get<0,2>() ==  13);CHECK(mat1.get<0,3>() ==  14);
        CHECK(mat1.get<1,0>() ==  15); CHECK(mat1.get<1,1>() ==  16); CHECK(mat1.get<1,2>() ==  17);CHECK(mat1.get<1,3>() ==  18);
        CHECK(mat1.get<2,0>() ==  19); CHECK(mat1.get<2,1>() == 110); CHECK(mat1.get<2,2>() == 111);CHECK(mat1.get<2,3>() == 112);
        CHECK(mat1.get<3,0>() == 113); CHECK(mat1.get<3,1>() == 114); CHECK(mat1.get<3,2>() == 115);CHECK(mat1.get<3,3>() == 116);
    }

    SECTION("Operators"){
        // Matrix * Vec4
        mat1.set<0>( 1, 2, 3, 4);
        mat1.set<1>( 5, 6, 7, 8);
        mat1.set<2>( 9,10,11,12);
        mat1.set<3>(13,14,15,16);
        vec1 = Vec4(4,8,12,1);
        targetVec1 = Vec4(60, 160,260,360);
        vec1 = mat1 * vec1;
        CHECK((vec1.get<0>() - targetVec1.get<0>()) < 5e-6);
        CHECK((vec1.get<1>() - targetVec1.get<1>()) < 5e-6);
        CHECK((vec1.get<2>() - targetVec1.get<2>()) < 5e-6);
        CHECK((vec1.get<3>() - targetVec1.get<3>()) < 5e-6);

        // Mat4 * Mat4
        mat1.set<0>(5 ,    7 ,    7 ,    7);
        mat1.set<1>(10,     1,     8,     2);
        mat1.set<2>(8 ,    9 ,    8 ,    8);
        mat1.set<3>(10,    10,     4,     1);

        mat2.set<0>(3,     7,     5,     2);
        mat2.set<1>(1,     4,     4,     5);
        mat2.set<2>(1,    10,     8,     5);
        mat2.set<3>(9,     1,     8,     7);

        target1.set<0>(92 ,  140 ,  165 ,   129);
        target1.set<1>(57 ,  156 ,  134 ,   79 );
        target1.set<2>(113,   180,   204,   157);
        target1.set<3>(53 ,  151 ,  130 ,   97 );
        mat1 = mat1 * mat2;
        for (int i =0; i < 16; i ++){
            CHECK(std::abs(mat1.get(i%4,i/4) - target1.get(i%4,i/4)) < 5e-6);
        }

        // Mat4 *= Mat4
        mat1.set<0>(5 ,    7 ,    7 ,    7);
        mat1.set<1>(10,     1,     8,     2);
        mat1.set<2>(8 ,    9 ,    8 ,    8);
        mat1.set<3>(10,    10,     4,     1);

        mat2.set<0>(3,     7,     5,     2);
        mat2.set<1>(1,     4,     4,     5);
        mat2.set<2>(1,    10,     8,     5);
        mat2.set<3>(9,     1,     8,     7);

        target1.set<0>(92 ,  140 ,  165 ,   129);
        target1.set<1>(57 ,  156 ,  134 ,   79 );
        target1.set<2>(113,   180,   204,   157);
        target1.set<3>(53 ,  151 ,  130 ,   97 );
        mat1 *= mat2;
        for (int i =0; i < 16; i ++){
            CHECK(std::abs(mat1.get(i%4,i/4) - target1.get(i%4,i/4)) < 5e-6);
        }
    }
}

#if benchmark
TEST_CASE("tMatrixBenchmark"){
    Matrix4 mat1;
    Matrix4 mat2;
    Vec4 vec1;
    Stopwatch stopwatch;

    SECTION("Matrix multiplications"){
        //templated getter and setters
        BENCHMARK_ADVANCED("Mat4*Vec4")(Catch::Benchmark::Chronometer meter) {
                mat1.set<0>( 1, 2, 3, 4);
                mat1.set<1>( 5, 6, 7, 8);
                mat1.set<2>( 9,10,11,12);
                mat1.set<3>(13,14,15,16);
                vec1 = Vec4(4,8,12,1);
                meter.measure([mat1,vec1] { return mat1*vec1; });
            };

        BENCHMARK_ADVANCED("Mat4*Mat4")(Catch::Benchmark::Chronometer meter) {
                mat1.set<0>(5 ,    7 ,    7 ,    7);
                mat1.set<1>(10,     1,     8,     2);
                mat1.set<2>(8 ,    9 ,    8 ,    8);
                mat1.set<3>(10,    10,     4,     1);

                mat2.set<0>(3,     7,     5,     2);
                mat2.set<1>(1,     4,     4,     5);
                mat2.set<2>(1,    10,     8,     5);
                mat2.set<3>(9,     1,     8,     7);
                meter.measure([mat1,mat2] { return mat1*mat2; });
            };


    }
}
#endif
