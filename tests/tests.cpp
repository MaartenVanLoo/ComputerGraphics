#include <iostream>

#include "../include/RenderEngineCore.h"
#include <catch2/catch_all.hpp>


int main(int argc, char ** argv)
{
    Camera camera = Camera();
    camera.setPosition(Vec4(0,0,0,1));
    camera.setDirection(Vec4(1,0,0, 0));
    camera.setSensor(Sensor("16:9",100));
    camera.setResolution(Resolution("16:9",200));
    camera.setFocalLength(35);
    Scene scene = Scene();

    Sphere sphere = Sphere();
    Ray ray = Ray();
    //std::cout << "Camera:" << camera << "\n";
    //std::cout << "Scene:" << scene << "\n";
    //std::cout << "Box:" << box << "\n";
    //std::cout << "Sphere:" << sphere << "\n";
    //std::cout << "Ray:" << ray << "\n";
    //std::cout << "Hello, World!" << std::endl;

    // If the last argument is "-p", then pause after the tests are run.
    // This allows us to run "leaks" on Mac OS X to check for memory leaks.
    bool pause_after_test = false;
    if (argc && std::string(argv[argc - 1]) == "-p")
    {
        pause_after_test = true;
        argc--;
    }

    int result = Catch::Session().run(argc, argv);

    if (pause_after_test)
    {
        printf("Press any key to continue . . .");
        std::string s;
        std::getline(std::cin,s);
    }
    //system("pause");
    return result;
}