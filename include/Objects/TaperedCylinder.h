//
// Created by Maarten Van Loo on 12/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_TAPEREDCYLINDER_H
#define I_COMPUTERGRAPHICS_TAPEREDCYLINDER_H

#include "Object.h"

namespace MRay {
    class TaperedCylinder : public Object {
        //generic tapered Cylinder
        // => circle with radius 1 = base in xy plane.
        // => circle with radius "s" = top circle size at z = 1
        // => s = 1: normal cylinder
        // => s = 0: normal cone
        // F(x,y;z = x² + y² - (1+ (s-1)z)² for 0 < z < 1

    public:
        explicit TaperedCylinder(float s = 0);

        bool hitPoint(Ray &ray, Intersection &intersection) override;

        Vec4 normal(Vec4 &point) const override;

    protected:
        float s;
    };
}

#endif //I_COMPUTERGRAPHICS_TAPEREDCYLINDER_H
