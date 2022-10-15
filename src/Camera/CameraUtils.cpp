//
// Created by Maarten Van Loo on 30/09/2022.
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
   this->width = float(MRay::getWidth(screensize));
   this->height = float(MRay::getHeight(screensize));
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
    this->width = MRay::getWidth(screensize);
    this->height = MRay::getHeight(screensize);
}

long long Resolution::getPixels() const{
    return (long long)(this->width) * (long long)(this->height);
}



