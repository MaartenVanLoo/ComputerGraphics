//
// Created by Maarten Van Loo on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_CAMERAUTILS_H
#define I_COMPUTERGRAPHICS_CAMERAUTILS_H

#include <string>
#include <stdexcept>
#include <ostream>

namespace MRay {
    enum Screensize {
        _240p,
        _360p,
        _480p,
        _720p, _HD,
        _1080p, _FHD,
        _1440p, _QHD,
        _2160p, _UHD, _4K,
        _4320p, _8K_UHD, _8K,
        _8640p, _16K_UHD, _16K,
        _17280p, _32K,
        _34560p, _64K
    };
    static int getWidth(Screensize size){
        switch(size){
            case _240p:
                return 352;
            case _360p:
                return 480;
            case _480p:
                return 858;
            case _720p : case _HD:
                return 1280;
            case _1080p: case _FHD:
                return 1920;
            case _1440p: case _QHD:
                return 2560;
            case _2160p: case _UHD: case _4K:
                return 3860;
            case _4320p: case _8K_UHD: case _8K:
                return 7680;
            case _8640p: case _16K_UHD: case _16K:
                return 15360;
            case _17280p: case _32K:
                return 30720;
            case _34560p: case _64K:
                return 61440;
            default:
                throw std::invalid_argument("Unrecognized screensize");
        }
    }
    static int getHeight(Screensize size){
        switch(size){
            case _240p:
                return 240;
            case _360p:
                return 360;
            case _480p:
                return 480;
            case _720p : case _HD:
                return 720;
            case _1080p: case _FHD:
                return 1080;
            case _1440p: case _QHD:
                return 1440;
            case _2160p: case _UHD: case _4K:
                return 2160;
            case _4320p: case _8K_UHD: case _8K:
                return 4320;
            case _8640p: case _16K_UHD: case _16K:
                return 8640;
            case _17280p: case _32K:
                return 17280;
            case _34560p: case _64K:
                return 34560;
            default:
                throw std::invalid_argument("Unrecognized screensize");
        }
    }

    struct Sensor {
        Sensor() {};

        Sensor(float width, float height);

        Sensor(Screensize screensize);

        Sensor(std::string ratio, float width);

        friend std::ostream &operator<<(std::ostream &os, const Sensor &sensor);

        float width = 160, height = 90;
    };

    struct Resolution {
        Resolution() {}

        Resolution(int width, int height);

        Resolution(std::string ratio, int width);

        Resolution(Screensize screensize);

        long long getPixels() const;

        friend std::ostream &operator<<(std::ostream &os, const Resolution &resolution);

        int width = 1920, height = 1080;
    };

}

#endif //I_COMPUTERGRAPHICS_CAMERAUTILS_H
