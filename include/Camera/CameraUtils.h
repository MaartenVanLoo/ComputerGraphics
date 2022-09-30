//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_CAMERAUTILS_H
#define I_COMPUTERGRAPHICS_CAMERAUTILS_H

#include <string>
#include <stdexcept>
#include <ostream>

struct Sensor{
    Sensor(){};
    Sensor(float width, float height);
    Sensor(std::string ratio, float width);

    friend std::ostream &operator<<(std::ostream &os, const Sensor &sensor);

    float width = 160, height = 90;
};


struct Resolution{
    Resolution(){}
    Resolution(int width, int height);
    Resolution(std::string ratio, int width);

    friend std::ostream &operator<<(std::ostream &os, const Resolution &resolution);

    int width = 1920, height = 1080;
};
#endif //I_COMPUTERGRAPHICS_CAMERAUTILS_H
