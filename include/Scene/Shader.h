//
// Created by maart on 11/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_SHADER_H
#define I_COMPUTERGRAPHICS_SHADER_H

#include <Light/Color3.h>
#include "Scene.h"

namespace MRay {

    class Shader {
    public:
        Shader(Scene *scene) : scene(scene) {}

        virtual Color3 shade(int x, int y) = 0;

        virtual Color3 shade(Ray &primaryRay) = 0;

        bool getFirstHit(Ray &ray, Hit &best, Intersection &intersect, const Object *ignore = nullptr) const {
            bool flag = false;
            for (auto obj: scene->getObjects()) {
                if (obj == ignore) continue;
                intersect.clear();
                if (obj->hitPoint(ray, intersect)) {
                    Hit hit = intersect.hit[0];
                    if (best.t > hit.t && hit.t >= 0) {
                        best = hit;
                        flag = true;
                    }
                }
            }
            return flag;
        }

        bool isInShadow(const Vec4 &point, const Object *ignore, const Light *light, Intersection &intersect) const {
            //ray to light source
            Ray ray = light->getRay(point);

            //look for intersections:
            Hit best;
            intersect.clear();
            if (!getFirstHit(ray, best, intersect, ignore)) return false; //no hit= not in shadow

            //get distance between point and light:
            float dist = light->getDist(point); //square of the distance!
            if (dist >= best.t * best.t) return true;
            return false;
        }

    protected:
        Scene *scene;
    };
}
#endif //I_COMPUTERGRAPHICS_SHADER_H
