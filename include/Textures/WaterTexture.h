//
// Created by Maarten Van Loo on 2/11/2022.
//

#ifndef I_COMPUTERGRAPHICS_WATERTEXTURE_H
#define I_COMPUTERGRAPHICS_WATERTEXTURE_H

#include "Texture.h"
#include "Perlin.h"

namespace MRay {
    class WaterTexture : public Texture {
    public:
        explicit WaterTexture(double su=0.01, double sv=0.01);
        explicit WaterTexture(Vec3& scale);
        Vec3 compute(float u, float v, float w) override {
            return Vec3();
        }

        Vec2 normalMap(float u, float v, float w) override {
            Vec3 n = noise.computeGradient(u,v);
            return Vec2(n.get<1>(),n.get<2>());
        }
    private:
        Perlin2D noise = Perlin2D();
    };
}
#endif //I_COMPUTERGRAPHICS_WATERTEXTURE_H
