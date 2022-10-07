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
    Box(){this->pos = Vec4(0,0,0,1);};
    Box(const Vec4 &pos, const Vec4 &halfSize);

    bool hitPoint(Ray &ray, float &t1, float &t2) override;

    Vec4 normal(Ray &ray) override{return Vec4();};

    friend std::ostream &operator<<(std::ostream &os, const Box &box);

private:
    Vec4 pos;       // position of center box (unit box has center at 0,0,0)
    Vec4 size;      // size of the box
    Vec4 halfSize;  // size of the box / 2
};
#endif //I_COMPUTERGRAPHICS_BOX_H
