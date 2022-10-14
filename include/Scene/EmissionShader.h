//
// Created by maart on 11/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_EMISSIONSHADER_H
#define I_COMPUTERGRAPHICS_EMISSIONSHADER_H

#include "Render/Shader.h"
namespace MRay {

    class EmissionShader : public Shader {
    public:
        explicit EmissionShader(Scene *scene) : Shader(scene) {}

        Color3 shade(int x, int y) override {
            Ray primaryRay = scene->camera.getPrimaryRay(x, y);
            return this->shade(primaryRay);

        }

        Color3 shade(Ray &primaryRay) override {
            //only emissive model:
            Intersection intersect; //object to store intersections, can be reused!
            Color3 color;

            Hit first = Hit();
            if (!this->getFirstHit(primaryRay, first, intersect)) {
                //no hit, set background color:
                color = Color3(0x87, 0xCE, 0xFA);
            } else {
                color = first.obj->getMaterial().emissive;
            }
            color.closeTransaction();
            return color;
        }
    };
}
#endif //I_COMPUTERGRAPHICS_EMISSIONSHADER_H
