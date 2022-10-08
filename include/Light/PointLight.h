//
// Created by maart on 7/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_POINTLIGHT_H
#define I_COMPUTERGRAPHICS_POINTLIGHT_H

#include <Light/Light.h>
class PointLight : Light{
    Ray getRay(Vec4 &point) override;

    Vec4 position;
};


#endif //I_COMPUTERGRAPHICS_POINTLIGHT_H
