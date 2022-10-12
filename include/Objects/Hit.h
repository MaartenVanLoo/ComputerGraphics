//
// Created by maart on 12/10/2022.
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
        bool entering = false;
    };
}
#endif //I_COMPUTERGRAPHICS_HIT_H
