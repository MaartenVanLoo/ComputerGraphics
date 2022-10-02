//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_RENDERENGINECORE_H
#define I_COMPUTERGRAPHICS_RENDERENGINECORE_H

#undef RGB //Note test framework Catch2 already has an RGB macro defined which causes havoc with our own RGB class; this will disable the macro

#include "Ray.h"
#include "Vector.h"

#include "Objects/ObjectCore.h"

#include "Camera/Camera.h"

#include "Scene/Scene.h"

#include "Screen/Screen.h"

#include "Transform/Transform.h"
#endif //I_COMPUTERGRAPHICS_RENDERENGINECORE_H
