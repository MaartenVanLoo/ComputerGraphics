//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_RENDERENGINECORE_H
#define I_COMPUTERGRAPHICS_RENDERENGINECORE_H

#undef RGB //Note test framework Catch2 already has an Color3 macro defined which causes havoc with our own Color3 class; this will disable the macro


#include "Ray.h"
#include "LinearAlgebra/Vector.h"

#include "Objects/ObjectCore.h"
#include "Camera/Camera.h"
#include "Scene/Scene.h"

#include "Screen/Screen.h"

#include "Transform/Transform.h"

#include "Utils/Options.h"

#endif //I_COMPUTERGRAPHICS_RENDERENGINECORE_H
