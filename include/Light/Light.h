//
// Created by Maarten Van Loo on 2/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_LIGHT_H
#define I_COMPUTERGRAPHICS_LIGHT_H

#include <LinearAlgebra/Vector.h>
#include <Ray.h>
//https://learnopengl.com/Lighting/Light-casters
//http://learnwebgl.brown37.net/09_lights/lights_combined.html
struct Light {
    virtual Ray getRay(Vec4 &point) = 0;

    Vec3 position;

    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
};


#endif //I_COMPUTERGRAPHICS_LIGHT_H
