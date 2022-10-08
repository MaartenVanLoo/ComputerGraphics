//
// Created by maart on 7/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_COLOR3_H
#define I_COMPUTERGRAPHICS_COLOR3_H

#include <cstdint>

struct Color3{
    Color3();
    Color3(int red, int green, int blue);
    uint8_t red=0;
    uint8_t green=0;
    uint8_t blue=0;
};
#endif //I_COMPUTERGRAPHICS_COLOR3_H
