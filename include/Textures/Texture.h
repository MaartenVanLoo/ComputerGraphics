//
// Created by Maarten Van Loo on 12/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_TEXTURE_H
#define I_COMPUTERGRAPHICS_TEXTURE_H
#include <LinearAlgebra//Vector.h>
#include <unordered_map>
//wood?
//https://skybase.wordpress.com/2012/01/26/how-to-creating-super-simple-procedural-wood-textures-in-filter-forge/
namespace MRay {
    class Texture {
    public:
        virtual Vec3 compute(float u = 0.0, float v = 0.0, float w = 0.0) = 0;
        virtual Vec2 normalMap(float u = 0.0, float v = 0.0, float w = 0.0);

        const static std::vector<std::string> textureLibrary;
    };
}
#endif //I_COMPUTERGRAPHICS_TEXTURE_H
