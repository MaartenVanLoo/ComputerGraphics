//
// Created by maart on 12/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_INTERSECTION_H
#define I_COMPUTERGRAPHICS_INTERSECTION_H

#include "Hit.h"
namespace MRay{
    struct Intersection {
        std::vector<Hit> hit;

        void clear();
    };
}
#endif //I_COMPUTERGRAPHICS_INTERSECTION_H
