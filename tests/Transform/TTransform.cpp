//
// Created by Maarten Van Loo on 2/10/2022.
//

#include <catch2/catch_all.hpp>
#include <iostream>
#include "../../include/RenderEngineCore.h"

TEST_CASE("tTransform") {
    Matrix4 mat4;
    Matrix4 target;
    Vec4 vec, tvec, result;
    SECTION("Rotate XYZ"){
        Transform::rotateX(mat4, 0.174532925199433); //10degree
        target[0] = Vec4(1,                0,                0, 0);
        target[1] = Vec4(0,0.984807753012208,-0.17364817766693, 0);
        target[2] = Vec4(0, 0.17364817766693,0.984807753012208, 0);
        target[3] = Vec4(0,                0,                0, 1);
        for (int i =0; i < 16; i ++){
            CHECK(std::abs(mat4[i%4][i/4] - target[i%4][i/4]) < 5e-6);
        }

        Transform::rotateY(mat4, 0.174532925199433); //10degree
        target[0] = Vec4(0.984807753012208, -0.17364817766693,0, 0);
        target[1] = Vec4( 0.17364817766693, 0.984807753012208,0, 0);
        target[2] = Vec4(                0,                 0,1, 0);
        target[3] = Vec4(                0,                 0,0, 1);
        for (int i =0; i < 16; i ++){
            CHECK(std::abs(mat4[i%4][i/4] - target[i%4][i/4]) < 5e-6);
        }

        Transform::rotateZ(mat4, 0.174532925199433); //10degree
        target[0] = Vec4(0.984807753012208, 0,  0.17364817766693, 0);
        target[1] = Vec4(                0, 1,                 0, 0);
        target[2] = Vec4(-0.17364817766693, 0, 0.984807753012208, 0);
        target[3] = Vec4(                0, 0,                 0, 1);
        for (int i =0; i < 16; i ++){
            CHECK(std::abs(mat4[i%4][i/4] - target[i%4][i/4]) < 5e-6);
        }

    }

    SECTION("Rotate axis"){
        Transform::rotatef(mat4, 0.174532925199433,3,4,5); //10degree
        target[0] = Vec4(  0.987542357470011, -0.119141664691903,  0.102787917271516, 0);
        target[1] = Vec4(  0.126433943246043,  0.989669272048301,-0.0675957835862669, 0);
        target[2] = Vec4(-0.0936725690788407, 0.0797495811765005,  0.992403876506104, 0);
        target[3] = Vec4(                  0,                  0,                  0, 1);
        for (int i =0; i < 16; i ++){
            CHECK(std::abs(mat4[i%4][i/4] - target[i%4][i/4]) < 5e-6);
        }
    }

    SECTION("Apply transform"){
        vec = Vec4(1,2,3,0);
        Transform::rotateX(mat4, 0.174532925199433); //10degree
        tvec=Transform::applyTransform(mat4,vec);
        result = Vec4(1,1.44867097302363 ,3.30171961437048,0);
        for (int i = 0; i < 4 ; i ++) CHECK(std::abs(tvec[i]-result[i])<5e-6);

        Transform::rotateY(mat4, 0.174532925199433); //10degree
        tvec=Transform::applyTransform(mat4,vec);
        result = Vec4(0.637511397678347,2.14326368369135,3,0);
        for (int i = 0; i < 4 ; i ++) CHECK(std::abs(tvec[i]-result[i])<5e-6);

        Transform::rotateZ(mat4, 0.174532925199433); //10degree
        tvec = Transform::applyTransform(mat4,vec);
        result = Vec4(1.505752286013,2,2.78077508136969,0);
        for (int i = 0; i < 4 ; i ++) CHECK(std::abs(tvec[i]-result[i])<5e-6);

        Transform::rotatef(mat4, 0.174532925199433,3,4,5); //10degree
        tvec = Transform::applyTransform(mat4,vec);
        result = Vec4(1.05762277990075,1.90298513658385,3.04303822279247,0);
        for (int i = 0; i < 4 ; i ++) CHECK(std::abs(tvec[i]-result[i])<5e-6);

        Transform::rotatef(mat4, 0.174532925199433,Vec3(3,4,5)); //10degree
        tvec = Transform::applyTransform(mat4,vec);
        result = Vec4(1.05762277990075,1.90298513658385,3.04303822279247,0);
        for (int i = 0; i < 4 ; i ++) CHECK(std::abs(tvec[i]-result[i])<5e-6);

        Transform::rotatef(mat4, 0.174532925199433,Vec4(3,4,5,0)); //10degree
        tvec = Transform::applyTransform(mat4,vec);
        result = Vec4(1.05762277990075,1.90298513658385,3.04303822279247,0);
        for (int i = 0; i < 4 ; i ++) CHECK(std::abs(tvec[i]-result[i])<5e-6);

    }
}