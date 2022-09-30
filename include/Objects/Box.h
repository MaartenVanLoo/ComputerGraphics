//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_BOX_H
#define I_COMPUTERGRAPHICS_BOX_H

#include <ostream>
#include "Object.h"

//aligned box
class Box : public Object{
public:
    bool hitPoint(Ray &ray, float &t1, float &t2) override;

    friend std::ostream &operator<<(std::ostream &os, const Box &box);

private:
    Vec4 min;
    Vec4 max;
};
#endif //I_COMPUTERGRAPHICS_BOX_H
