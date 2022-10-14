//
// Created by maart on 13/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_BOOLEANOBJECT_H
#define I_COMPUTERGRAPHICS_BOOLEANOBJECT_H

#include <Objects/Object.h>
namespace MRay {
    class BooleanObject : public Object {
    public:
        BooleanObject(Object *left, Object *right);

        virtual bool hitPoint(Ray &ray, Intersection &intersection) =0;
        virtual Vec4 normal(Vec4 &point) const =0;

        ~BooleanObject() override;
    protected:
        Object *left;
        Object *right;
    };
}
#endif //I_COMPUTERGRAPHICS_BOOLEANOBJECT_H
