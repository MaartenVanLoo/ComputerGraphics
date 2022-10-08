#include "../../include/Ray.h"
#include "../../include/Objects/Box.h"


//
// Created by maart on 30/09/2022.
//

//https://iquilezles.org/articles/intersectors/
//https://www.shadertoy.com/view/ld23DV
//https://iquilezles.org/articles/boxfunctions/
bool Box::hitPoint(Ray &ray, Hit &hit1, Hit &hit2) {
// convert from world to box space
    Ray tr = ray.transform(this->invtransform);

    //Vec4 rd = ray.dir();
    Vec4 rad = Vec4(1,1,1,0); //this->halfSize;

    // ray-box intersection in box space
    Vec4 m = 1.0/tr.dir();
    Vec4 s = Vec4((tr.dir().get(0)<0.0)?1.0f:-1.0f,
                  (tr.dir().get(1)<0.0)?1.0f:-1.0f,
                  (tr.dir().get(2)<0.0)?1.0f:-1.0f,
                  0);
    Vec4 tN = m * (  s - tr.pos());
    Vec4 tF = m * (- s - tr.pos());

    hit1.t = tN.max3(); //std::max(std::max(tN[0], tN[1] ), tN[2]);
    hit2.t = tF.min3(); //std::min(std::min(tF[0], tF[1] ), tF[2]);

    if( hit1.t>hit2.t || hit2.t<0.0) return false;
    hit1.obj = this;
    hit1.point = tr.at(hit1.t);
    hit2.obj = this;
    hit2.point = tr.at(hit2.t);
    return true;
}

std::ostream &operator<<(std::ostream &os, const Box &box) {
    os << "Box: {}";
    return os;
}

Box::Box(const Vec4 &pos, const Vec4 &size) {
    this->scale(size.get<0>(), size.get<1>(),size.get<2>());
    this->translate(pos.get<0>(),pos.get<1>(),pos.get<2>());
}
