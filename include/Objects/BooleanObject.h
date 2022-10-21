//
// Created by Maarten Van Loo on 13/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_BOOLEANOBJECT_H
#define I_COMPUTERGRAPHICS_BOOLEANOBJECT_H

#include <Objects/Object.h>
namespace MRay {
    class BooleanObject : public Object {
    public:
        BooleanObject(Object *left, Object *right);

        ~BooleanObject() override;
    protected:
        Object *left;
        Object *right;
    };
}
#endif //I_COMPUTERGRAPHICS_BOOLEANOBJECT_H
