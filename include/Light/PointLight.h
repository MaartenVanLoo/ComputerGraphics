//
// Created by Maarten Van Loo on 7/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_POINTLIGHT_H
#define I_COMPUTERGRAPHICS_POINTLIGHT_H

#include <Light/Light.h>
#include <ostream>
namespace MRay {

    class PointLight : public Light {
    public:
        PointLight(float px=0.0, float py=0.0, float pz=0.0);
        PointLight(const Vec4 &position);

        void setPosition(double px, double py, double pz);
        void setPosition(const Vec4 &pos) override;

        friend std::ostream &operator<<(std::ostream &os, const PointLight &light);

    private:
        Ray getRay(const Vec4 &point) const override;

        float getDist(const Vec4 &point) const override;

        Vec4 getVec(const Vec4 &point) const override;

        Vec4 position = Vec4(0, 0, 0, 1);
    };
}


#endif //I_COMPUTERGRAPHICS_POINTLIGHT_H
