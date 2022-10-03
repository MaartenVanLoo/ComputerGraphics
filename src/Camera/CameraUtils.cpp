//
// Created by maart on 30/09/2022.
//

#include "../../include/Camera/CameraUtils.h"


Sensor::Sensor(float width, float height): width(width), height(height){}

Sensor::Sensor(std::string ratio, float width) {
        if (ratio == "4:3"){
            this->width = width;
            this->height = width * 3.0f / 4.0f;
        }
        else if (ratio=="16:9"){
            this->width = width;
            this->height = width * 9.0f / 16.0f;
        }
        else{
            throw std::invalid_argument("Unrecognized sensor aspect ratio");
        }
}

std::ostream &operator<<(std::ostream &os, const Sensor &sensor) {
    os << "w: " << sensor.width << " h: " << sensor.height;
    return os;
}

Sensor::Sensor(Screensize screensize) {
    switch(screensize){
        case _240p:
            this->width  = 352;
            this->height = 240;
            break;
        case _360p:
            this->width  = 480;
            this->height = 360;
            break;
        case _480p:
            this->width  = 858;
            this->height = 480;
            break;
        case _720p : case _HD:
            this->width  = 1280;
            this->height = 720;
            break;
        case _1080p: case _FHD:
            this->width  = 1920;
            this->height = 1080;
            break;
        case _2160p: case _UHD: case _4K:
            this->width  = 3860;
            this->height = 2160;
            break;
        default:
            throw std::invalid_argument("Unrecognized screensize");
    }
}

Resolution::Resolution(int width, int height): width(width), height(height){}

Resolution::Resolution(std::string ratio, int width) {
    if (ratio == "4:3"){
        this->width = width;
        this->height = int(width * 3.0f / 4.0f);
    }
    else if (ratio =="16:9"){
        this->width = width;
        this->height = int(width * 9.0f / 16.0f);
    }
    else{
        throw std::invalid_argument("Unrecognized resolution");
    }
}

std::ostream &operator<<(std::ostream &os, const Resolution &resolution) {
    os << "w: " << resolution.width << " h: " << resolution.height;
    return os;
}

Resolution::Resolution(Screensize screensize) {
    switch(screensize){
        case _240p:
            this->width  = 352;
            this->height = 240;
            break;
        case _360p:
            this->width  = 480;
            this->height = 360;
            break;
        case _480p:
            this->width  = 858;
            this->height = 480;
            break;
        case _720p : case _HD:
            this->width  = 1280;
            this->height = 720;
            break;
        case _1080p: case _FHD:
            this->width  = 1920;
            this->height = 1080;
            break;
        case _2160p: case _UHD: case _4K:
            this->width  = 3860;
            this->height = 2160;
            break;
        default:
            throw std::invalid_argument("Unrecognized screensize");
    }
}

long Resolution::getPixels() const{
    return this->width * this->height;
}


#pragma region RGB
RGB::RGB() {}

RGB::RGB(int red, int green, int blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

#pragma endregion
