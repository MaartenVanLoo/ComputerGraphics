//
// Created by Maarten Van Loo on 7/10/2022.
//

#include "Materials/Material.h"
using namespace MRay;


Material::Material() {
    this->ambient  = Vec3(0 ,0 ,0);
    this->diffuse  = Vec3(0,0,0);
    this->specular = Vec3(0,0,0);
    this->specularExponent = 0;
    this->shininess = 0;
}
Material::Material(float ambR, float ambG, float ambB, float diffR, float diffG, float diffB, float specR, float specG,
                   float specB, float shininess, float nR, float nG, float nB) {
    this->ambient  = Vec3(ambR ,ambG ,ambB);
    this->diffuse  = Vec3(diffR,diffG,diffB);
    this->specular = Vec3(specR,specG,specB);
    this->specularExponent = shininess;
    this->fresnell = Vec4(nR,nG,nB,0);
    this->shininess = shininess/128;
}
Material::Material(double ambR, double ambG, double ambB, double diffR, double diffG, double diffB, double specR, double specG,
                   double specB, double shininess, double nR, double nG, double nB) {
    this->ambient  = Vec3(float(ambR ),float(ambG ),float(ambB));
    this->diffuse  = Vec3(float(diffR),float(diffG),float(diffB));
    this->specular = Vec3(float(specR),float(specG),float(specB));
    this->specularExponent = float(shininess);
    this->fresnell = Vec4(float(nR),float(nG),float(nB),0.0f);
    this->shininess = float(shininess/128);
}

Material::Material(PhongMaterial &phong, CookTorrenceMaterial &cook): phongMaterial(phong), cookTorrenceMaterial((cook)){}

