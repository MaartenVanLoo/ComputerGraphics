//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_CAMERA_H
#define I_COMPUTERGRAPHICS_CAMERA_H


#include <ostream>
#include "../Vector.h"
#include "../Ray.h"
#include "CameraUtils.h"

class Camera {
public:
    Camera(){};
    Camera(Vec3 Position, Vec3 direction, Resolution resolution, Sensor s, float focalLength);

    Ray getPrimaryRay(int x, int y);


    const Sensor &getSensor() const;
    const Resolution &getResolution() const;
    const Vec4 &getPosition() const;
    const Vec4 &getDirection() const;
    float getFocalLength() const;

    void setSensor(const Sensor &sensor);
    void setResolution(const Resolution &resolution);
    void setPosition(const Vec4 &position);
    void setDirection(const Vec4 &direction);
    void setFocalLength(float focalLength);

    friend std::ostream &operator<<(std::ostream &os, const Camera &camera);

private:
    Vec4 position;
    Vec4 direction;

    float focalLength;      // in mm distance between eye and sensor in mm
    Sensor sensor;          // sensor size in mm!
    Resolution resolution;  // px width and height => used to divide the sensor
};


#endif //I_COMPUTERGRAPHICS_CAMERA_H
