//
// Created by Maarten Van Loo on 12/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_TEXTURE_H
#define I_COMPUTERGRAPHICS_TEXTURE_H
#include <LinearAlgebra//Vector.h>

//wood?
//https://skybase.wordpress.com/2012/01/26/how-to-creating-super-simple-procedural-wood-textures-in-filter-forge/
namespace MRay {
    class Texture {
    public:
        virtual Vec3 compute(float x, float y, float z, float scale) = 0;
    };
}
#endif //I_COMPUTERGRAPHICS_TEXTURE_H
