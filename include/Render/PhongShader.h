//
// Created by Maarten Van Loo on 11/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_PHONGSHADER_H
#define I_COMPUTERGRAPHICS_PHONGSHADER_H


#include "Render/Shader.h"
#include "Scene/Scene.h"
namespace MRay {

    class PhongShader : public Shader {
    public:
        explicit PhongShader(Scene *scene, Camera* camera, Options &options);

        Color3 shade(int x, int y, Intersection &intersection) override;
        Color3 shade(Ray &primaryRay, Intersection &intersection) override;

        Color3 shade(int x, int y) override;
        Color3 shade(Ray &primaryRay) override;
    };
}
#endif //I_COMPUTERGRAPHICS_PHONGSHADER_H
