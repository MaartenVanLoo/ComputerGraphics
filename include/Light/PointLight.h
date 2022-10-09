//
// Created by maart on 7/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_POINTLIGHT_H
#define I_COMPUTERGRAPHICS_POINTLIGHT_H

#include <Light/Light.h>
class PointLight : public Light{
public:
    PointLight(const Vec4 &position);

private:
    Ray getRay(const Vec4 &point) const override;
    float getDist(const Vec4 &point) const override;
    Vec4 getVec(const Vec4 &point) const override;

    Vec4 position = Vec4(-3,-10,10,1);
};


#endif //I_COMPUTERGRAPHICS_POINTLIGHT_H
