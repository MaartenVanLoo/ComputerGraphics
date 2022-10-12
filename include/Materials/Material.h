//
// Created by maart on 7/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_MATERIAL_H
#define I_COMPUTERGRAPHICS_MATERIAL_H

#include <Light/Color3.h>
#include <LinearAlgebra/Vector.h>

namespace MRay {
    class Material {
    public:
        Material();
        Material(float ambR, float ambG, float ambB,
                 float diffR,float diffG,float diffB,
                 float specR,float specG,float specB,
                 float shininess);
        Material(double ambR, double ambG, double ambB,
                 double diffR,double diffG,double diffB,
                 double specR,double specG,double specB,
                 double shininess);

        Vec3 ambient;
        Vec3 diffuse;
        Vec3 specular;
        float specularExponent;
        Color3 emissive = Color3();

        //Color3 color = Color3(0, 0, 0);
    };

}

#endif //I_COMPUTERGRAPHICS_MATERIAL_H
