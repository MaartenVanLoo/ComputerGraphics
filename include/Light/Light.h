//
// Created by Maarten Van Loo on 2/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_LIGHT_H
#define I_COMPUTERGRAPHICS_LIGHT_H

#include <LinearAlgebra/Vector.h>
#include <Ray.h>
#include <Light/Color3.h>

namespace MRay {
//https://learnopengl.com/Lighting/Light-casters
//http://learnwebgl.brown37.net/09_lights/lights_combined.html
    struct Light {
        virtual Ray getRay(const Vec4 &point) const = 0;

        virtual float getDist(const Vec4 &point) const = 0;

        virtual Vec4 getVec(const Vec4 &point) const = 0;

        virtual ~Light();

        //Color3 color = Color3(255, 255, 255); //white
        Color3 color = Color3(122, 122,122); //white
    };
}

#endif //I_COMPUTERGRAPHICS_LIGHT_H
