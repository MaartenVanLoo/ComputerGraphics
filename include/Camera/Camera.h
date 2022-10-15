//
// Created by Maarten Van Loo on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_CAMERA_H
#define I_COMPUTERGRAPHICS_CAMERA_H


#include <ostream>
#include <Transform/Transform.h>
#include <LinearAlgebra/Vector.h>
#include <Ray.h>
#include <Camera/CameraUtils.h>

namespace MRay {
    class Camera : public Transform {
    public:
        Camera() {};

        Camera(Vec3 position, Resolution resolution, Sensor s, float focalLength);

        Camera(Vec3 position, Screensize screensize, Sensor s, float focalLength);

        Ray getPrimaryRay(int x, int y) const;

        Ray getPrimaryRay(int x, int y, float dx, float dy) const;

        const Sensor &getSensor() const;

        const Resolution &getResolution() const;

        //const Vec4 &getPosition() const;
        Vec4 getDirection() const;

        float getFocalLength() const;

        float getUsableSensorWidth() const;

        float getUsableSensorHeight() const;


        void setSensor(const Sensor &sensor);

        void setResolution(const Resolution &resolution);

        void setResolution(const Screensize &resolution);

        void setPosition(const Vec4 &position);

        void setFocalLength(float focalLength);

        friend std::ostream &operator<<(std::ostream &os, const Camera &camera);

    private:
        float focalLength;      // in mm distance between eye and sensor in mm
        Sensor sensor;          // sensor size in mm!
        Resolution resolution;  // px width and height => used to divide the sensor

        //Sensor aspect ratio != resolution aspect ratio => some parts of the sensor are unused, pixels always square!
        void setUsableSensorSize();

        float usableSensorWidth;
        float usableSensorHeight;
    };
}

#endif //I_COMPUTERGRAPHICS_CAMERA_H
