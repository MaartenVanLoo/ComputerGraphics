//
// Created by Maarten Van Loo on 2/11/2022.
//
#include <Textures/Texture.h>

MRay::Vec2 MRay::Texture::normalMap(float u, float v, float w) {
    return Vec2(0.0,0.0); //no deviation of normal
}

//note: all lower case!
const std::vector<std::string> MRay::Texture::textureLibrary ={
        "checkboard",
        "water", //synonym for waterTexture
        "watertexture"
};