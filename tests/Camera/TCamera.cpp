//
// Created by Maarten Van Loo on 2/10/2022.
//
#include <catch2/catch_all.hpp>
#include <iostream>
#include <Camera/Camera.h>

#define DEBUG_PRINT false
using namespace MRay;
TEST_CASE("tCamera"){


    SECTION("usable space"){
        Camera camera = Camera();
        camera.setPosition(Vec4(0,0,0,1));
        camera.setSensor(Sensor(100,100));
        camera.setResolution(Resolution(200,100));
        camera.setFocalLength(35);

        CHECK(camera.getUsableSensorWidth() == 100);
        CHECK(camera.getUsableSensorHeight() == 50);

        camera.setSensor(Sensor(100,100));
        camera.setResolution(Resolution(100,200));

        CHECK(camera.getUsableSensorWidth() == 50);
        CHECK(camera.getUsableSensorHeight() == 100);

        camera.setSensor(Sensor(160,90));
        camera.setResolution(Resolution(160,90));
        CHECK(camera.getUsableSensorWidth() == 160);
        CHECK(camera.getUsableSensorHeight() == 90);

        camera.setSensor(Sensor(160,90));
        camera.setResolution(Resolution(320,180));
        CHECK(camera.getUsableSensorWidth() == 160);
        CHECK(camera.getUsableSensorHeight() == 90);

        camera.setSensor(Sensor("16:9",160));
        camera.setResolution(Resolution(Screensize::_4K));
        CHECK(camera.getUsableSensorWidth() == 160);
        CHECK(std::abs(camera.getUsableSensorHeight() - 89.5336787565f) < 5e-6);
    }

}