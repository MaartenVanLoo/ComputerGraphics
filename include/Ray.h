//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_RAY_H
#define I_COMPUTERGRAPHICS_RAY_H

#include <ostream>
#include "LinearAlgebra/Vector.h"
#include "LinearAlgebra/Matrix.h"

class Ray {
public:
    Ray(){};
    Ray(const Vec4 &position, const Vec4 &direction);

    const Vec4 &pos() const;
    const Vec4 &dir() const;
    Vec4 at(float t) const;

    void setPos(float x, float y, float z);
    void setPos(Vec4& pos);
    void setDir(float x, float y, float z);


    void normalizeDir();
    Ray transform(const Matrix4 &T) const;
    friend std::ostream &operator<<(std::ostream &os, const Ray &ray);

private:
    Vec4 position = Vec4(0,0,0,1);
    Vec4 direction = Vec4(0,0,0,0);;
};

class PrimaryRay: public Ray{};
class ShadowRay: public Ray{};


#endif //I_COMPUTERGRAPHICS_RAY_H
