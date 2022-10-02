#include "../../include/Ray.h"
#include "../../include/Objects/Box.h"


//
// Created by maart on 30/09/2022.
//

//https://iquilezles.org/articles/intersectors/
//https://www.shadertoy.com/view/ld23DV
//https://iquilezles.org/articles/boxfunctions/
bool Box::hitPoint(Ray &ray, float &t1, float &t2) {
// convert from world to box space
    //vec4 rd = (txx*vec4(rdw,0.0)).xyz;
    //vec4 ro = (txx*vec4(row,1.0)).xyz;
    Vec4 rd = ray.dir();
    Vec4 ro = ray.pos() - this->pos;
    Vec4 rad = this->halfSize;

    // ray-box intersection in box space
    Vec4 m = 1.0/rd;
    Vec4 s = Vec4((rd[0]<0.0)?1.0:-1.0,
                  (rd[1]<0.0)?1.0:-1.0,
                  (rd[2]<0.0)?1.0:-1.0,
                  0);
    Vec4 tN = m * (-ro + s * rad);
    Vec4 tF = m * (-ro - s * rad);

    t1 = std::max(std::max(tN[0], tN[1] ), tN[2]);
    t2 = std::min(std::min(tF[0], tF[1] ), tF[2]);

    if( t1>t2 || t2<0.0) return false;

    return true;
}

std::ostream &operator<<(std::ostream &os, const Box &box) {
    os << "Box: {" << "pos: " << box.pos << " size: " << box.size << "}";
    return os;
}

Box::Box(const Vec4 &pos, const Vec4 &size): pos(pos), size(size), halfSize(size/2) {

}
