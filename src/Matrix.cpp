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
