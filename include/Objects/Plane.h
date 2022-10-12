//
// Created by maart on 7/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_PLANE_H
#define I_COMPUTERGRAPHICS_PLANE_H

#include <Objects/Object.h>
namespace MRay {

//TODO: test class!!

//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
/**
 * Class describing an infinite plane
 * Potential use: ground plane of scene
 */
    class Plane : public Object {
    public:
        Plane(const Vec4 &pos, const Vec4 &normal);

        Plane(float px, float py, float pz, float nx, float ny, float nz);

        Vec4 normal(Ray &ray) override;

        bool hitPoint(Ray &ray, Intersection &intersection) override;

    protected:
        Vec4 pos;    // position describes to translation of the plane
        Vec4 norm;   // normal vector fully describes the direction of a plane;
    };
}
#endif //I_COMPUTERGRAPHICS_PLANE_H
