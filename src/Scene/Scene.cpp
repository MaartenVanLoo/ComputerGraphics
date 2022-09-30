//
// Created by maart on 30/09/2022.
//

#include "../../include/Scene/Scene.h"

std::ostream &operator<<(std::ostream &os, const Scene &scene) {
    os << "Scene: {" <<"objects: " << scene.objects.size() << "}";
    return os;
}
