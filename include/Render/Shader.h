//
// Created by Maarten Van Loo on 11/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_SHADER_H
#define I_COMPUTERGRAPHICS_SHADER_H

#include <Light/Color3.h>
#include "Scene/Scene.h"

namespace MRay {

    class Shader {
    public:
        Shader(Scene *scene, Camera* camera, Options& options) : scene(scene), camera(camera), options(options) {}

        virtual ~Shader() {}

        virtual Color3 shade(int x, int y, Intersection &intersection) = 0;
        virtual Color3 shade(Ray &primaryRay, Intersection &intersection) = 0;
        virtual Color3 shade(int x, int y) = 0;
        virtual Color3 shade(Ray &primaryRay) = 0;

        bool getFirstHit(Ray &ray, Hit &best, Intersection &intersect, const Object *ignore = nullptr) const {
            bool flag = false;
            for (auto obj: scene->getObjects()) {
                //if (obj == ignore) continue;
                intersect.clear();
                if (obj->hitPoint(ray, intersect, this->options)) {
                    for (auto& hit :intersect.hit) {
                        if (best.t > hit.t && hit.t >= 0.0001){// || hit.obj != ignore)) {
                            best = hit;
                            flag = true;
                        }
                    }
                }
            }
            return flag;
        }

        template<ShaderTypes T>
        double shadowFactor(const Vec4 &point, const Object *ignore, const Light *light, Intersection &intersect) const {
            double factor = 1.0;

            //ray to light source
            Ray ray = light->getRay(point);

            //get distance between point and light:
            float dist = light->getDist(point); //square of the distance!

            //look for intersections:
            intersect.clear();
            for (auto obj: scene->getObjects()){
                if (obj->hitPoint(ray, intersect, this->options)){
                    for (const auto& h: intersect.hit){
                        if (h.obj == ignore){
                            Vec4 p = h.point - point;
                            if (p.dot(p) < 1e-4)
                                continue; //this is the original point
                        }
                        if (dist > h.t * h.t && h.t > 0.001 && !h.entering)
                            factor *= h.obj->getMaterial().getTransparancy<T>();
                            if (factor == 0.0) return factor; //object between point and light
                    }
                }
            }
            //no object found between point and light => not in shadow
            return factor;
        }

        int getMaxBounces() const {
            return maxBounces;
        }

    protected:
        Scene *scene;       //reference to, not owner
        Camera* camera;     //reference to, not owner
        Options options;

        int maxBounces = -1;
    };
}
#endif //I_COMPUTERGRAPHICS_SHADER_H
