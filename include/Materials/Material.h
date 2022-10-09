//
// Created by maart on 7/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_MATERIAL_H
#define I_COMPUTERGRAPHICS_MATERIAL_H

#include <Light/Color3.h>
#include <LinearAlgebra/Vector.h>
struct Material{
    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
    float specularExponent;
    Color3 emissive;

    //Color3 color = Color3(0, 0, 0);
};



#endif //I_COMPUTERGRAPHICS_MATERIAL_H
