//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_SPHERE_H
#define I_COMPUTERGRAPHICS_SPHERE_H

#include <ostream>
#include "Object.h"
class Sphere : public Object{
public:
    Sphere(){};
    Sphere(const Vec4 &position, float radius);

    bool hitPoint(Ray &ray, float &t1, float&t2) override;
    /// Compute the normal vector in a point on the circle.
    /// Doesn't check if the point is actually on the circle!
    /// \return
    Vec4 normal(Vec4 point);

    Vec4 normal(Ray &ray) override;

    friend std::ostream &operator<<(std::ostream &os, const Sphere &sphere);

private:
    Vec4 position;
    float radius = 1.0;
};


#endif //I_COMPUTERGRAPHICS_SPHERE_H
