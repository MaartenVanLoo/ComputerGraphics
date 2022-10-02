#include <iostream>

#include "include/RenderEngineCore.h"

int main() {
    Camera camera = Camera();
    camera.setPosition(Vec4(-5,0,0,1));
    camera.setDirection(Vec4(1,0,0, 0));
    camera.setSensor(Sensor(36,24));
    camera.setResolution(Resolution(Screensize::_1080p));
    camera.setFocalLength(35);

    Scene scene = Scene();
    //scene.addObject(new Sphere(Vec4(0,0,2,1),2));
    scene.addObject(new Box(Vec4(0,0,0,1),Vec4(1,1,1,0)));

    Box box = Box();
    Sphere sphere = Sphere();
    Ray ray = Ray();
    std::cout << "Camera:" << camera << "\n";
    std::cout << "Scene:" << scene << "\n";
    std::cout << "Box:" << box << "\n";
    std::cout << "Sphere:" << sphere << "\n";
    std::cout << "Ray:" << ray << "\n";
    std::cout << "Hello, World!" << std::endl;

    scene.Render();
    return 0;
}
