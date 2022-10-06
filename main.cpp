#include <iostream>
#include <Utils/Stopwatch.h>

#include "include/RenderEngineCore.h"

int main() {
    Stopwatch stopwatch = Stopwatch();
    stopwatch.start();
    for (int i = 0; i< 1e6; i++) {
        Vec4 v1 = Vec4(rand() % 8, rand() % 8, rand() % 8, 0);
        Vec4 v2 = Vec4(rand() % 8, rand() % 8, rand() % 8, 0);
        Vec4 res = v1.cross(v2);
    }
    stopwatch.stop();
    std::cout << stopwatch << std::endl;
    Vec4 v = Vec4(1,2,3,4);
    v.set<2>(5);

    Camera camera = Camera();
    camera.setPosition(Vec4(-5,0,0,1));
    camera.setDirection(Vec4(1,0,0, 0));
    camera.setSensor(Sensor(36,24));
    camera.setResolution(Resolution(Screensize::_1080p));
    camera.setFocalLength(35);

    Scene scene = Scene();
    scene.addObject(new Sphere(Vec4(0,-3,-2,1),1.5));
    scene.addObject(new Box(Vec4(0,0,0,1),Vec4(1,1,1,0)));
    scene.addObject(new Box(Vec4(0,2,1,1),Vec4(1,1,1,0)));

    Box box = Box();
    Sphere sphere = Sphere();
    Ray ray = Ray();
    std::cout << "Camera:" << camera << "\n";
    std::cout << "Scene:" << scene << "\n";
    std::cout << "Box:" << box << "\n";
    std::cout << "Sphere:" << sphere << "\n";
    std::cout << "Ray:" << ray << "\n";
    std::cout << "Hello, World!" << std::endl;

    Options options;

    scene.Render(options);
    system("pause");
    return 0;
}
