//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_SCENE_H
#define I_COMPUTERGRAPHICS_SCENE_H


#include <vector>
#include <ostream>
#include "../Objects/Object.h"
class Scene {
public:
    friend std::ostream &operator<<(std::ostream &os, const Scene &scene);

private:
    std::vector<Object> objects;
};


#endif //I_COMPUTERGRAPHICS_SCENE_H
