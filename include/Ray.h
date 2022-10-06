//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_RAY_H
#define I_COMPUTERGRAPHICS_RAY_H

#include <ostream>
#include "LinearAlgebra/Vector.h"
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
    friend std::ostream &operator<<(std::ostream &os, const Ray &ray);

private:
    Vec4 position;
    Vec4 direction;

};


#endif //I_COMPUTERGRAPHICS_RAY_H
