//
// Created by Maarten Van Loo on 2/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_MATRIX_H
#define I_COMPUTERGRAPHICS_MATRIX_H

#include <Vector.h>
#include <ostream>

class Matrix4{
public:
    Vec4& operator[](int index);

    friend std::ostream &operator<<(std::ostream &os, const Matrix4 &matrix4);

private:
    Vec4 data[4];
};

#endif //I_COMPUTERGRAPHICS_MATRIX_H
