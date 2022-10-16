//
// Created by Maarten Van Loo on 16/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_BOUNDINGBOX_H
#define I_COMPUTERGRAPHICS_BOUNDINGBOX_H

#include <LinearAlgebra/Vector.h>
#include <LinearAlgebra/Matrix.h>
#include <Ray.h>

namespace MRay{
    class BoundingBox{
    public:
        BoundingBox();
        BoundingBox(const Vec3 &min, const Vec3 &max);
        void transform(const Matrix4  &transform);
        void add(const BoundingBox &box);
        void intersect(const BoundingBox &box);

        bool hit(const Ray &ray);

    private:
        Vec4 min = Vec4(0,0,0,0);
        Vec4 max = Vec4(0,0,0,0);
    };
}
#endif //I_COMPUTERGRAPHICS_BOUNDINGBOX_H
