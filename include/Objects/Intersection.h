//
// Created by Maarten Van Loo on 12/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_INTERSECTION_H
#define I_COMPUTERGRAPHICS_INTERSECTION_H

#include "Hit.h"
namespace MRay{
    struct Intersection {
        std::vector<Hit> hit;

        //use in boolean objects
        Intersection* leftHit = nullptr;
        Intersection* rightHit = nullptr;

        virtual ~Intersection();

        void clear();
        bool empty();
        void sort();
    };
}
#endif //I_COMPUTERGRAPHICS_INTERSECTION_H
