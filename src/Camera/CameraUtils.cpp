//
// Created by maart on 30/09/2022.
//

#include "../../include/Camera/CameraUtils.h"
using namespace MRay;

MRay::Sensor::Sensor(float width, float height): width(width), height(height){}

MRay::Sensor::Sensor(std::string ratio, float width) {
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

std::ostream &MRay::operator<<(std::ostream &os, const Sensor &sensor) {
    os << "w: " << sensor.width << " h: " << sensor.height;
    return os;
}

MRay::Sensor::Sensor(Screensize screensize) {
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
        case _1440p: case _QHD:
            this->width  = 2560;
            this->height = 1440;
            break;
        case _2160p: case _UHD: case _4K:
            this->width  = 3860;
            this->height = 2160;
            break;
        case _4320p: case _8K_UHD: case _8K:
            this->width  = 7680;
            this->height = 4320;
            break;
        case _8640p: case _16K_UHD: case _16K:
            this->width  = 15360;
            this->height = 8640;
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

std::ostream &MRay::operator<<(std::ostream &os, const Resolution &resolution) {
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
        case _4320p: case _8K_UHD: case _8K:
            this->width  = 7680;
            this->height = 4320;
            break;
        case _8640p: case _16K_UHD: case _16K:
            this->width  = 15360;
            this->height = 8640;
            break;
        default:
            throw std::invalid_argument("Unrecognized screensize");
    }
}

long long Resolution::getPixels() const{
    return (long long)(this->width) * (long long)(this->height);
}



