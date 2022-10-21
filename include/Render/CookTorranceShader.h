//
// Created by Maarten Van Loo on 14/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_COOKTORRANCESHADER_H
#define I_COMPUTERGRAPHICS_COOKTORRANCESHADER_H
#include "Render/Shader.h"
#include "Scene/Scene.h"
namespace MRay {

    class CookTorranceShader : public Shader {
    public:
        explicit CookTorranceShader(Scene *scene, Camera* camera, Options &options);

        Color3 shade(int x, int y, Intersection &intersection) override;

        Color3 shade(Ray &primaryRay, Intersection &intersection) override;

        Color3 shade(int x, int y) override;

        Color3 shade(Ray &primaryRay) override;

    private:
        //F(angle, refraction)
        float fresnell(float refraction, Vec4 &m, Vec4 &s);
        Vec4 fresnell(Vec4 &refraction, Vec4 &m, Vec4 &s);
        Vec4 fresnell(Vec4 &refraction, float mDotS);
        //F(0, refraction)
        float fresnell(float refraction);
        Vec4 fresnell(Vec4 &refraction);

        double beckmannDistribution(double angle, double m);
    };
}
#endif //I_COMPUTERGRAPHICS_COOKTORRANCESHADER_H
