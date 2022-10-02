//
// Created by Maarten Van Loo on 2/10/2022.
//

#include "../../include/Transform/Transform.h"

Vec4 Transform::applyTransform(Matrix4 &T, Vec4 &vec) {
    //T = 4x4 matrix!
    Vec4 result;
    for (int row = 0; row < 4; row++){
        result[row] = Vec4::sum(T[row]*vec);
    }
    return result;
}


void Transform::rotatef(Matrix4 &T, float angle, float x, float y, float z) {
    //T must be a 4x4 matrix, each vec4 is a row
    float cosa = std::cos(angle);
    float sina = std::sin(angle);

    T[0] = Vec4(cosa + x * x *(1 - cosa),   x*y*(1-cosa)-z*sina,    x*z*(1-cosa) + y*sina , 0);
    T[1] = Vec4(x*y*(1-cosa+z*sina),       cosa + y*y*(1-cosa),    y*z*(1-cosa) - x*sina , 0);
    T[2] = Vec4(x*z*(1-cosa)-y*sina,       y*z*(1-cosa) + x*sina,  cosa + z*z * (1-cosa) , 0  );
    T[3] = Vec4(0,                         0,                      0,                      1);
}

void Transform::rotatef(Matrix4 &T, float angle, Vec3 axis) {
    //T must be a 4x4 matrix, each vec4 is a row
    float cosa = std::cos(angle);
    float sina = std::sin(angle);
    float x = axis[0];
    float y = axis[1];
    float z = axis[2];
    T[0] = Vec4(cosa + x * x *(1 - cosa),   x*y*(1-cosa)-z*sina,    x*z*(1-cosa) + y*sina , 0);
    T[1] = Vec4(x*y*(1-cosa+z*sina),       cosa + y*y*(1-cosa),    y*z*(1-cosa) - x*sina , 0);
    T[2] = Vec4(x*z*(1-cosa)-y*sina,       y*z*(1-cosa) + x*sina,  cosa + z*z * (1-cosa) , 0  );
    T[3] = Vec4(0,                         0,                      0,                      1);
}

void Transform::rotatef(Matrix4 &T, float angle, Vec4 axis) {
    //T must be a 4x4 matrix, each vec4 is a row
    float cosa = std::cos(angle);
    float sina = std::sin(angle);
    float x = axis[0];
    float y = axis[1];
    float z = axis[2];
    T[0] = Vec4(cosa + x * x *(1 - cosa),   x*y*(1-cosa)-z*sina,    x*z*(1-cosa) + y*sina , 0);
    T[1] = Vec4(x*y*(1-cosa+z*sina),       cosa + y*y*(1-cosa),    y*z*(1-cosa) - x*sina , 0);
    T[2] = Vec4(x*z*(1-cosa)-y*sina,       y*z*(1-cosa) + x*sina,  cosa + z*z * (1-cosa) , 0  );
    T[3] = Vec4(0,                         0,                      0,                      1);
}

