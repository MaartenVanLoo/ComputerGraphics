//
// Created by Maarten Van Loo on 12/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_HIT_H
#define I_COMPUTERGRAPHICS_HIT_H
#include "Object.h"
namespace MRay {
    class Object;
    struct Hit {
        double t = DBL_MAX;
        Object *obj = nullptr;
        Vec4 point; // GCS point
        Vec4 normal; //LCS normal;
        int surface;
        bool entering = false;
        bool thinMaterial = false;

        bool operator<(const Hit &rhs) const {
            return t < rhs.t;
        }

        bool operator>(const Hit &rhs) const {
            return rhs < *this;
        }

        bool operator<=(const Hit &rhs) const {
            return !(rhs < *this);
        }

        bool operator>=(const Hit &rhs) const {
            return !(*this < rhs);
        }
    };
}
#endif //I_COMPUTERGRAPHICS_HIT_H
