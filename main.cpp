#include <iostream>

#include "include/RenderEngineCore.h"

int main() {
    Camera camera = Camera();
    camera.setPosition(Vec4(0,0,0,1));
    camera.setDirection(Vec4(1,0,0, 0));
    camera.setSensor(Sensor("16:9",160));
    camera.setResolution(Resolution(Screensize::_4K));
    camera.setFocalLength(35);
    Scene scene = Scene();
    Image image = Image(camera.getResolution());
    Screen screen = Screen(image);
    screen.show();

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
        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
        for (int x = 0; x < camera.getResolution().width; x++){
            Ray primary =  camera.getPrimaryRay(x,y);
            image.setPixel(x, y, RGB(x, y, 0));
        }
    }
    screen.waitClose();
    return 0;
}
