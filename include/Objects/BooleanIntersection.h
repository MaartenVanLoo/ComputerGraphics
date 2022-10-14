//
// Created by maart on 13/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_BOOLEANINTERSECTION_H
#define I_COMPUTERGRAPHICS_BOOLEANINTERSECTION_H
#include <Objects/BooleanObject.h>
namespace MRay {
    class BooleanIntersection : public BooleanObject {
    public:
        BooleanIntersection(Object *left, Object *right);

        bool hitPoint(Ray &ray, Intersection &intersection) override;

        Vec4 normal(Vec4 &point) const override;
    };
}
#endif //I_COMPUTERGRAPHICS_BOOLEANINTERSECTION_H