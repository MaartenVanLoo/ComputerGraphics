//
// Created by maart on 11/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_PHONGSHADER_H
#define I_COMPUTERGRAPHICS_PHONGSHADER_H


#include "Shader.h"
#include "Scene.h"
namespace MRay {

    class PhongShader : public Shader {
    public:
        explicit PhongShader(Scene *scene);

        Color3 shade(int x, int y) override;

        Color3 shade(Ray &primaryRay) override;
    };
}
#endif //I_COMPUTERGRAPHICS_PHONGSHADER_H
