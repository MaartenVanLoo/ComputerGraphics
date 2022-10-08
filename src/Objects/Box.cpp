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
/*
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
*/
    double tHit, numer, denom;
    double tIn = DBL_MIN, tOut = DBL_MAX;
    int inSurf, outSurf;
#define X 0
#define Y 1
#define Z 2
    for (int i= 0; i < 6; i++) {
        switch (i) {
            case 0:
                numer = 1.0 - tr.pos().get<Y>();
                denom = tr.dir().get<Y>();
                break;
            case 1:
                numer = 1.0 + tr.pos().get<Y>();
                denom = -tr.dir().get<Y>();
                break;
            case 2:
                numer = 1.0 - tr.pos().get<X>();
                denom = tr.dir().get<X>();
                break;
            case 3:
                numer = 1.0 + tr.pos().get<X>();
                denom = -tr.dir().get<X>();
                break;
            case 4:
                numer = 1.0 - tr.pos().get<Z>();
                denom = tr.dir().get<Z>();
                break;
            case 5:
                numer = 1.0 + tr.pos().get<Z>();
                denom = -tr.dir().get<Z>();
                break;
            default:
                return false;
        }

        if (std::fabs(denom) < 0.00001) { //ray is parallel
            if (numer < 0) return false; // ray is out;
            else;                        // ray inside, no change to tIn, tOut
        }
        else { //ray is not parrellel
            tHit = numer /denom;
            if(denom > 0){ //exiting
                if (tHit < tOut){ // a new earlier exit
                    tOut = tHit, outSurf = i;
                }
            }
            else { //denom is negative: entering
                if (tHit > tIn){ // a new later entrance
                    tIn = tHit; inSurf = i;
                }
            }
        }
        if (tIn >= tOut) return false; // it's a miss - early out)
    } //end of for loop
    int num = 0; //no positive hits yet;
    if (tIn > 0.00001) {// first hit in front of eye
        hit1.t = tIn;
        hit1.obj = this;
        hit1.point = tr.at(float(tIn));
        num++;
    }
    if (tOut > 0.0001){  //hit in front of eye
        if (num == 1){
            hit2.t = tOut;
            hit2.obj = this;
            hit2.point = tr.at(float(tOut));
        }else{
            hit1.t = tOut;
            hit1.obj = this;
            hit1.point = tr.at(float(tOut));
            hit2 = hit1;
        }
        num++;
    }
    return (num > 0);
}

std::ostream &operator<<(std::ostream &os, const Box &box) {
    os << "Box: {}";
    return os;
}

Box::Box(const Vec4 &pos, const Vec4 &size) {
    this->scale(size.get<0>(), size.get<1>(),size.get<2>());
    this->translate(pos.get<0>(),pos.get<1>(),pos.get<2>());
}
