//
// Created by maart on 30/09/2022.
//

#include <iostream>
#include "../../include/Camera/Camera.h"


Camera::Camera(Vec3 position, Vec3 direction,Resolution resolution, Sensor s, float focalLength): resolution(resolution), sensor(sensor), focalLength(focalLength) {
    //this->position = Vec4(position, 1);
    //this->direction = Vec4(direction , 0);
    this->setUsableSensorSize();
}
Camera::Camera(Vec3 position, Vec3 direction,Screensize resolution, Sensor s, float focalLength): resolution(resolution), sensor(sensor), focalLength(focalLength) {
    //this->position = Vec4(position, 1);
    //this->direction = Vec4(direction , 0);
    this->setUsableSensorSize();
}


Ray Camera::getPrimaryRay(int x, int y) {
    //Todo: transformation, for now camera in a given point and pointing in positive x direction
    if (x < 0 || x > this->resolution.width) throw std::invalid_argument("X pixel is not on sensor");
    if (y < 0 || y > this->resolution.height) throw std::invalid_argument("y pixel is not on sensor");

    //Transform x and y from pixel space to sensor space
    float x_sensor = (float(x)+0.5f) * this->usableSensorWidth / float(this->resolution.width);
    float y_sensor = (float(y)+0.5f) * this->usableSensorHeight / float(this->resolution.height);

    //Transform from sensor space to local coordinate system (LCS)
    float lcs_X = this->focalLength;
    float lcs_y = this->usableSensorWidth/2 - x_sensor;
    float lcs_z = this->usableSensorHeight/2 - y_sensor;

    Ray ray = Ray();
    //ray.setPos(this->position); //translate ray to camera position but default position = (0,0,0,1)!
    ray.setDir(lcs_X, lcs_y, lcs_z); //set the direction of the ray
    // TODO: Transform ray according to camera direction.

    //transform ray from "camera-space" to "global-space"
    return ray.transform(this->transform);;
}


const Sensor &Camera::getSensor() const {
    return sensor;
}

void Camera::setSensor(const Sensor &sensor) {
    Camera::sensor = sensor;
    this->setUsableSensorSize();
}

const Resolution &Camera::getResolution() const {
    return resolution;
}

void Camera::setResolution(const Resolution &resolution) {
    this->resolution = resolution;
    this->setUsableSensorSize();
}
void Camera::setResolution(const Screensize &resolution) {
    this->resolution = Resolution(resolution);
}

/*const Vec4 &Camera::getPosition() const {
    return position;

    //TODO: experimental
    return this->transform.get<3>(p);
}*/

void Camera::setPosition(const Vec4 &position) {
    Vec4 p = position;
    p.set<3>(1); //make sure the bottom value equals 1 in case position doesn't (fool proofing)
    this->transform.set(3,p); //override third column of transform
    //compute inv transform:
    p = -p;
    p.set<3>(1);
    this->invtransform.set(3,p);
}

Vec4 Camera::getDirection() const {
    Vec4 xAxis = Vec4(1,0,0,0);
    return this->transform*xAxis; //compute direction from transformation matrix; result is not normalized;
}


float Camera::getFocalLength() const {
    return focalLength;
}

void Camera::setFocalLength(float focalLength) {
    Camera::focalLength = focalLength;
}

std::ostream &operator<<(std::ostream &os, const Camera &camera) {
    os << "Camera: {" << "focalLength: " << camera.focalLength << " sensor: " << camera.sensor << " resolution: " << camera.resolution << "}";
    return os;
}

void Camera::setUsableSensorSize() {
    //TODO: test function
    double h = this->sensor.width * (this->resolution.height/(double)this->resolution.width); //using full sensor width, this would be the vertical sensor size required
    double w = this->sensor.height * (this->resolution.width/(double)this->resolution.height); //using full sensor height, this would be the horizontal sensor size required

    if (h < this->sensor.height){
        //width will be maximal used, height will be cropped:
        this->usableSensorWidth = this->sensor.width;
        this->usableSensorHeight = float(h);
    }else{
        //width will be maximal used, height will be cropped:
        this->usableSensorWidth = float(w);
        this->usableSensorHeight = this->sensor.height ;
    }

}

float Camera::getUsableSensorWidth() const {
    return usableSensorWidth;
}

float Camera::getUsableSensorHeight() const {
    return usableSensorHeight;
}
