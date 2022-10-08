//
// Created by maart on 7/10/2022.
//

#include <Light/PointLight.h>
Ray PointLight::getRay(Vec4 &point) {
    return Ray(point,this->position - point);
}

