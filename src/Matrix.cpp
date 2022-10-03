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

Matrix4 &Matrix4::operator*=(Matrix4 &rhs) {
    Matrix4 tmp; //defaults to all zero's
    for (int i =0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            for (int k = 0; k < 4; k++){
                tmp[i][j] += this->data[i][k] * rhs.data[k][j];
            }
        }
    }
    this->data[0] = tmp.data[0];
    this->data[1] = tmp.data[1];
    this->data[2] = tmp.data[2];
    this->data[3] = tmp.data[3];
    return *this;
}

bool Matrix4::operator==(const Matrix4 &rhs) const {
    for (int i = 0; i < 4; i++){
        if (this->data[i] != rhs.data[i]) return false;
    }
    return true;
}

bool Matrix4::operator!=(const Matrix4 &rhs) const {
    return !(rhs == *this);
}
