//
// Created by Maarten Van Loo on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_OBJECT_H
#define I_COMPUTERGRAPHICS_OBJECT_H

#include "../Ray.h"
#include "LinearAlgebra/Vector.h"
#include <cmath>
#include <algorithm>
#include <ostream>
#include <Materials/Material.h>
#include <vector>
#include <Textures/Texture.h>
#include "Camera/CameraUtils.h"
#include "Transform/Transform.h"
#include "Intersection.h"
#include "BoundingBox.h"

namespace MRay {
    struct Hit;
    struct Intersection;
    class Object;

    class Object : public Transform {
    public:
        virtual ~Object();

        virtual bool hitPoint(Ray &ray, Intersection &intersection) = 0;

        virtual void computeBoundingBox(){};
        void setMaterial(Material mtrl);
        void setTexture(Texture *texture);

        /// Transform normal from LCS to GCS
        /// \param normal Normal vector
        Vec4 transformNormal(Vec4 normal) const;

        Material &getMaterial();
        BoundingBox &getBoundingBox();
        Texture *getTexture();
    protected:
        Material mtrl;
        Texture* texture=nullptr;
        BoundingBox bb;
    };

}
#endif //I_COMPUTERGRAPHICS_OBJECT_H
