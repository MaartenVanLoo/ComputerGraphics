//
// Created by Maarten Van Loo on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_BOX_H
#define I_COMPUTERGRAPHICS_BOX_H

#include <ostream>
#include "Object.h"

namespace MRay {

//aligned box
    class Box : public Object {
    public:
        Box() {};

        Box(const Vec4 &pos, const Vec4 &size);

        bool hitPoint(Ray &ray, Intersection &intersection, const Options& options) override;

        void computeBoundingBox() override;

        Vec4 boxNormal(int surf);

        friend std::ostream &operator<<(std::ostream &os, const Box &box);

    private:
        //Vec4 pos;       // unit box has center at 0,0,0)
        // size of unit box = 2 (-1,-1,-1) => (1,1,1)
        //Vec4 size;      // size of the box
        //Vec4 halfSize;  // size of the box / 2
    };
}
#endif //I_COMPUTERGRAPHICS_BOX_H
