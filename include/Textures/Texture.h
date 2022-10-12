//
// Created by maart on 12/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_TEXTURE_H
#define I_COMPUTERGRAPHICS_TEXTURE_H
#include <LinearAlgebra//Vector.h>
namespace MRay {
    class Texture {
    public:
        virtual Vec3 compute(float x, float y, float z, float scale) = 0;
    };
}
#endif //I_COMPUTERGRAPHICS_TEXTURE_H
