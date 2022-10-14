//
// Created by maart on 11/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_SHADER_H
#define I_COMPUTERGRAPHICS_SHADER_H

#include <Light/Color3.h>
#include "Scene/Scene.h"

namespace MRay {

    class Shader {
    public:
        Shader(Scene *scene, Camera* camera, Options& options) : scene(scene), camera(camera), options(options) {}

        virtual Color3 shade(int x, int y, Intersection &intersection) = 0;
        virtual Color3 shade(Ray &primaryRay, Intersection &intersection) = 0;
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

            //get distance between point and light:
            float dist = light->getDist(point); //square of the distance!

            //look for intersections:
            Hit best;
            intersect.clear();
            for (auto obj: scene->getObjects()){
                if (obj->hitPoint(ray, intersect)){
                    for (const auto& h: intersect.hit){
                        if (h.obj == ignore){
                            Vec4 p = h.point - point;
                            if (p.dot(p) < 1e-6) continue; //this is the original point
                        }
                        if (dist > h.t * h.t)
                            return true; //object between point and light
                    }
                }
            }
            //no object found between point and light => not in shadow
            return false;
        }


    protected:
        Scene *scene;
        Camera* camera;
        Options options;
    };
}
#endif //I_COMPUTERGRAPHICS_SHADER_H