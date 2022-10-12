//
// Created by maart on 30/09/2022.
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
        _4320p, _8K_UHD, _8K
    };

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
