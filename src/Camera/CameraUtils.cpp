//
// Created by maart on 30/09/2022.
//

#include "../../include/Camera/CameraUtils.h"


Sensor::Sensor(float width, float height): width(width), height(height){}

Sensor::Sensor(std::string ratio, float width) {
        if (ratio == "4:3"){
            this->width = width;
            this->height = width * 3.0 / 4.0;
        }
        else if (ratio=="16:9"){
            this->width = width;
            this->height = width * 9.0 / 16.0;
        }
        else{
            throw std::invalid_argument("Unrecognized sensor aspect ratio");
        }
}

std::ostream &operator<<(std::ostream &os, const Sensor &sensor) {
    os << "w: " << sensor.width << " h: " << sensor.height;
    return os;
}

Resolution::Resolution(int width, int height): width(width), height(height){}

Resolution::Resolution(std::string ratio, int width) {
    if (ratio == "4:3"){
        this->width = width;
        this->height = int(width * 3.0 / 4.0);
    }
    else if (ratio =="16:9"){
        this->width = width;
        this->height = int(width * 9.0 / 16.0);
    }
    else{
        throw std::invalid_argument("Unrecognized resolution");
    }
}

std::ostream &operator<<(std::ostream &os, const Resolution &resolution) {
    os << "w: " << resolution.width << " h: " << resolution.height;
    return os;
}
