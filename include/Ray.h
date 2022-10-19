//
// Created by Maarten Van Loo on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_RAY_H
#define I_COMPUTERGRAPHICS_RAY_H

#include <iostream>
#include "LinearAlgebra/Vector.h"
#include "LinearAlgebra/Matrix.h"

namespace MRay {

    class Ray {
    public:
        Ray() {};

        Ray(const Vec4 &position, const Vec4 &direction);

        const Vec4 &pos() const;

        const Vec4 &dir() const;

        Vec4 at(float t) const;

        void setPos(float x, float y, float z);

        void setPos(const Vec4& pos);

        void setDir(float x, float y, float z);
        void setDir(const Vec4 &dir);

        void normalizeDir();

        Ray transform(const Matrix4 &T) const;

        friend std::ostream &operator<<(std::ostream &os, const Ray &ray);

        void setDepth(int d);
        void increaseDepth();
        int getDepth() const;
    private:
        Vec4 position = Vec4(0, 0, 0, 1);
        Vec4 direction = Vec4(0, 0, 0, 0);;
        int depth = 0;
    };

    class PrimaryRay : public Ray {
    };

    class ShadowRay : public Ray {
    };
}

#endif //I_COMPUTERGRAPHICS_RAY_H
