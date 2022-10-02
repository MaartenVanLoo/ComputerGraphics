//
// Created by Maarten Van Loo on 2/10/2022.
//

#include <Matrix.h>

Vec4& Matrix4::operator[](int index){
    if (index > 3 || index < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    return this->data[index];
}

std::ostream &operator<<(std::ostream &os, const Matrix4 &matrix4) {

    os << "Matrix: " << "\n";
    os << matrix4.data[0] << "\n";
    os << matrix4.data[1] << "\n";
    os << matrix4.data[2] << "\n";
    os << matrix4.data[3] << "\n";

    return os;
}
