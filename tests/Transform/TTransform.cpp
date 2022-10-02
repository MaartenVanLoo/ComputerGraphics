//
// Created by Maarten Van Loo on 2/10/2022.
//

#include <catch2/catch_all.hpp>
#include <iostream>
#include "../../include/RenderEngineCore.h"

TEST_CASE("tTransform") {
    SECTION("Rotate XYZ"){
        Matrix4 mat4;
        Transform::rotateX(mat4, 0.174532925199433); //10degree
        std::cout << mat4 << std::endl;
        Transform::rotateY(mat4, 0.174532925199433); //10degree
        std::cout << mat4 << std::endl;
        Transform::rotateZ(mat4, 0.174532925199433); //10degree
        std::cout << mat4 << std::endl;
        Transform::rotate(mat4, 0.174532925199433,0.174532925199433,0.174532925199433); //10degree on all axis
        std::cout << mat4 << std::endl;

    }
}