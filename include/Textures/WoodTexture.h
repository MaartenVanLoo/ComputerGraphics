//
// Created by maart on 29/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_WOODTEXTURE_H
#define I_COMPUTERGRAPHICS_WOODTEXTURE_H

#include "Texture.h"
#include "Perlin.h"

namespace MRay {
    class WoodTexture: public Texture {
    public:
        WoodTexture();

        Vec3 compute(float u, float v, float w) override;

        void preview(double x0 = 0, double x1 = 1, double y0 = 0, double y1 = 1);
    private:
        Perlin3D noise1;
        Perlin3D turbulence;
    };
}

#endif //I_COMPUTERGRAPHICS_WOODTEXTURE_H
