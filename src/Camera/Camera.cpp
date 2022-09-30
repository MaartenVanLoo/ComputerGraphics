//
// Created by maart on 30/09/2022.
//

#include "../../include/Camera/Camera.h"

std::ostream &operator<<(std::ostream &os, const Camera &camera) {
    os << "Camera: {" << "focalLength: " << camera.focalLength << " sensor: " << camera.sensor << " resolution: " << camera.resolution << "}";
    return os;
}

Ray Camera::getPrimaryRay(int x, int y) {
    //Todo: transformation, for now camera in a given point and pointing in positive x direction
    if (x < 0 || x > this->resolution.width) throw std::invalid_argument("X pixel is not on sensor");
    if (y < 0 || y > this->resolution.height) throw std::invalid_argument("y pixel is not on sensor");

    Ray ray = Ray();
    ray.setPos(this->position); //translate ray to camera position
    // TODO: check how to convert from pixel coordinates to y and z coordinates
    ray.setDir(this->focalLength, this->sensor.width/2-float(x), this->sensor.width/2-float(y)); //compute the direction of the ray
    // TODO: Transform ray according to camera direction.
    return ray;
}

Camera::Camera(Vec3 position, Vec3 direction,Resolution resolution, Sensor s, float focalLength): resolution(resolution), sensor(sensor), focalLength(focalLength) {
    this->position = Vec4(position.x, position.y,position.z, 1);
    this->direction = Vec4(direction.x, direction.y,direction.z , 0);
}

const Sensor &Camera::getSensor() const {
    return sensor;
}

void Camera::setSensor(const Sensor &sensor) {
    Camera::sensor = sensor;
}

const Resolution &Camera::getResolution() const {
    return resolution;
}

void Camera::setResolution(const Resolution &resolution) {
    Camera::resolution = resolution;
}

const Vec4 &Camera::getPosition() const {
    return position;
}

void Camera::setPosition(const Vec4 &position) {
    Camera::position = position;
}

const Vec4 &Camera::getDirection() const {
    return direction;
}

void Camera::setDirection(const Vec4 &direction) {
    Camera::direction = direction;
}

float Camera::getFocalLength() const {
    return focalLength;
}

void Camera::setFocalLength(float focalLength) {
    Camera::focalLength = focalLength;
}
