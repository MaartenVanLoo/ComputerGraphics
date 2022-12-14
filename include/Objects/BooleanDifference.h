//
// Created by Maarten Van Loo on 14/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_BOOLEANDIFFERENCE_H
#define I_COMPUTERGRAPHICS_BOOLEANDIFFERENCE_H
#include <Objects/BooleanObject.h>
namespace MRay {
    class BooleanDifference : public BooleanObject {
    public:
        BooleanDifference(Object *left, Object *right);

        bool hitPoint(Ray &ray, Intersection &intersection, const Options &options) override;

        void computeBoundingBox() override;

        Vec4 normal(Vec4 &point) const;

        void setMaterial(Material mtrl) override;
    };
}
#endif //I_COMPUTERGRAPHICS_BOOLEANDIFFERENCE_H
