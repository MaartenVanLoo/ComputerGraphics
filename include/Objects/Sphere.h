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
    Sphere(const Vec4 &position);
    Sphere(const Vec4 &position, float radius);

    bool hitPoint(Ray &ray, Hit &hit1, Hit &hit2) override;
    /// Compute the normal vector in a point on the circle.
    /// Doesn't check if the point is actually on the circle!
    /// \return
    Vec4 normal(Vec4 point);

    Vec4 normal(Ray &ray) override;

    friend std::ostream &operator<<(std::ostream &os, const Sphere &sphere);

protected:
    Vec4 position;
};


#endif //I_COMPUTERGRAPHICS_SPHERE_H
