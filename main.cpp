#include <iostream>

#include "include/RenderEngineCore.h"

int main() {
    Camera camera = Camera();
    camera.setPosition(Vec4(0,0,0,1));
    camera.setDirection(Vec4(1,0,0, 0));
    camera.setSensor(Sensor("16:9",100));
    camera.setResolution(Resolution("16:9",200));
    camera.setFocalLength(35);
    Scene scene = Scene();

    Box box = Box();
    Sphere sphere = Sphere();
    Ray ray = Ray();
    std::cout << "Camera:" << camera << "\n";
    std::cout << "Scene:" << scene << "\n";
    std::cout << "Box:" << box << "\n";
    std::cout << "Sphere:" << sphere << "\n";
    std::cout << "Ray:" << ray << "\n";
    std::cout << "Hello, World!" << std::endl;
    for (int y = 0; y < camera.getResolution().height; y++){
        for (int x = 0; x < camera.getResolution().width; x++){
            std::cout << camera.getPrimaryRay(x,y) << std::endl;
        }
    }
    return 0;
}
