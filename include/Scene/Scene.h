//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_SCENE_H
#define I_COMPUTERGRAPHICS_SCENE_H


#include <vector>
#include <ostream>
#include <Camera/Camera.h>
#include <Light/Light.h>
#include <Screen/Screen.h>
#include "../Objects/Object.h"

class Scene {
public:
    Scene();

    virtual ~Scene();

    void addObject(Object* obj);
    friend std::ostream &operator<<(std::ostream &os, const Scene &scene);

    void Render();

private:

    Light light;
    Camera camera;
    std::vector<Object*> objects;

    //GUI
    Image* image = nullptr;
    Screen* screen = nullptr;
};


#endif //I_COMPUTERGRAPHICS_SCENE_H
