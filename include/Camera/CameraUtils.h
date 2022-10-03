//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_CAMERAUTILS_H
#define I_COMPUTERGRAPHICS_CAMERAUTILS_H

#include <string>
#include <stdexcept>
#include <ostream>

enum Screensize{
    _240p,
    _360p,
    _480p,
    _720p, _HD,
    _1080p,_FHD,
    _2160p, _UHD,_4K
};
struct Sensor{
    Sensor(){};
    Sensor(float width, float height);
    Sensor(Screensize screensize);
    Sensor(std::string ratio, float width);

    friend std::ostream &operator<<(std::ostream &os, const Sensor &sensor);

    float width = 160, height = 90;
};

struct Resolution{
    Resolution(){}
    Resolution(int width, int height);
    Resolution(std::string ratio, int width);
    Resolution(Screensize screensize);

    long getPixels() const;
    friend std::ostream &operator<<(std::ostream &os, const Resolution &resolution);

    int width = 1920, height = 1080;
};

struct RGB{
    RGB();
    RGB(int red, int green, int blue);
    uint8_t red=0;
    uint8_t green=0;
    uint8_t blue=0;
};

#endif //I_COMPUTERGRAPHICS_CAMERAUTILS_H
