//
// Created by Maarten Van Loo on 12/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_CHECKERBOARD_H
#define I_COMPUTERGRAPHICS_CHECKERBOARD_H
#include "Texture.h"

namespace MRay {
    class Checkboard : public Texture {
    public:
        Checkboard(float su = 1.0, float sv=1.0, float sw=1.0);

        Vec3 compute(float u, float v, float w) override;

    private:
        float su=1.0f, sv=1.0f, sw=1.0f;
    };
}
#endif //I_COMPUTERGRAPHICS_CHECKERBOARD_H
