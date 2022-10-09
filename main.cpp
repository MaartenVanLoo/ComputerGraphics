#include <iostream>
#include <Utils/Stopwatch.h>

#include "include/RenderEngineCore.h"

int main() {
    Stopwatch stopwatch = Stopwatch();
    stopwatch.start();
    for (int i = 0; i< 1e6; i++) {
        Vec4 v1 = Vec4((float)(rand() % 8), (float)(rand() % 8), (float)(rand() % 8), 0.0f);
        Vec4 v2 = Vec4((float)(rand() % 8), (float)(rand() % 8), (float)(rand() % 8), 0.0f);
        Vec4 res = v1.cross(v2);
    }
    stopwatch.stop();
    std::cout << stopwatch << std::endl;
    Vec4 v = Vec4(1,2,3,4);
    v.set<2>(5);


    Material material = Material();
    material.specularExponent = 100;
    material.specular = Vec3(0.99,0.99,0.99);

    Object* obj = nullptr;

    Scene scene = Scene();
    obj = new Plane(Vec4(0,0,-2,0),Vec4(0,0,1,0));
    material.emissive = Color3(5, 5,5);
    material.diffuse = Vec3(0.9,0.9,0.9);
    obj->setMaterial(material);
    scene.addObject(obj);

    obj = new  Sphere(Vec4(0,0,0,1),1);
    material.emissive = Color3(5,0,0);
    material.diffuse = Vec3(0.9,0.1,0.1);
    obj->setMaterial(material);
    scene.addObject(obj);

    /* creates problems
    obj = new  Sphere(Vec4(4,1,5,1),1);
    obj->scale(.01,1,1);
    material.emissive = Color3(5,0,0);
    material.diffuse = Vec3(0.9,0.1,0.1);
    obj->setMaterial(material);
    scene.addObject(obj);
    */

    obj = new Box(Vec4(2,-0.5,0.5,1),Vec4(1,1,1,0));
    material.emissive = Color3(0, 5,0);
    material.diffuse = Vec3(0.1,0.9,0.1);
    obj->setMaterial(material);
    scene.addObject(obj);

    obj = new Box(Vec4(4,0,1,1),Vec4(1,1,1,0));
    material.emissive = Color3(0, 0,5);
    material.diffuse = Vec3(0.1,0.1,0.9);
    obj->setMaterial(material);
    obj->rotate(0.0,0.0,0.5);
    scene.addObject(obj);

    Light* light = new PointLight(Vec4(-3,-10,10,1));
    light->diffuse = Vec3(0.9,0.9,0.9);
    scene.addLight(light);
    light = new PointLight(Vec4(-5,4,6,1));
    light->diffuse = Vec3(0.9,0.9,0.9);
    scene.addLight(light);

    Box box = Box();
    Sphere sphere = Sphere();
    Ray ray = Ray();
    std::cout << "Scene:" << scene << "\n";
    std::cout << "Box:" << box << "\n";
    std::cout << "Sphere:" << sphere << "\n";
    std::cout << "Ray:" << ray << "\n";
    std::cout << "Hello, World!" << std::endl;

    Options options;
    options.enableGui = true;
    options.multicore = true;
    scene.Render(options);
    system("pause");
    return 0;
}
