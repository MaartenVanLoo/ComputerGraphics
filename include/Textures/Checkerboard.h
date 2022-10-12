//
// Created by maart on 12/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_CHECKERBOARD_H
#define I_COMPUTERGRAPHICS_CHECKERBOARD_H
#include "Texture.h"

namespace MRay {
    class Checkboard : public Texture {
    public:
        Checkboard(float sx, float sy, float sz);

        Vec3 compute(float x, float y, float z, float scale) override;

    private:
        float sx=0.0f, sy=0.0f, sz=0.0f;
    };
}
#endif //I_COMPUTERGRAPHICS_CHECKERBOARD_H
