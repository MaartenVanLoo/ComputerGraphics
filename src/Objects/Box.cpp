#include "../../include/Ray.h"
#include "../../include/Objects/Box.h"


//
// Created by Maarten Van Loo on 30/09/2022.
//
using namespace MRay;
//https://iquilezles.org/articles/intersectors/
//https://www.shadertoy.com/view/ld23DV
//https://iquilezles.org/articles/boxfunctions/
bool MRay::Box::hitPoint(Ray &ray,Intersection &intersection) {
    //bounding box test
    if (!this->bb.hit(ray)) return false;

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

    float hit1 = tN.max3(); //std::max(std::max(tN[0], tN[1] ), tN[2]);
    float hit2 = tF.min3(); //std::min(std::min(tF[0], tF[1] ), tF[2]);

    if( hit1>hit2 || hit2<0.0) return false;
    intersection.hit[0].t = hit1;
    intersection.hit[0].obj = this;
    intersection.hit[0].point = ray.at(hit1);
    intersection.hit[1].t = hit2;
    intersection.hit[1].obj = this;
    intersection.hit[1].point = ray.at(hit2);
    return true;
*/
    double tHit, numer, denom;
    double tIn = DBL_MIN, tOut = DBL_MAX;
    int inSurf, outSurf;
    for (int i= 0; i < 6; i++) {
        switch (i) {
            case 0:
                numer = 1.0 - tr.pos().get<_Y>();
                denom = tr.dir().get<_Y>();
                break;
            case 1:
                numer = 1.0 + tr.pos().get<_Y>();
                denom = -tr.dir().get<_Y>();
                break;
            case 2:
                numer = 1.0 - tr.pos().get<_X>();
                denom = tr.dir().get<_X>();
                break;
            case 3:
                numer = 1.0 + tr.pos().get<_X>();
                denom = -tr.dir().get<_X>();
                break;
            case 4:
                numer = 1.0 - tr.pos().get<_Z>();
                denom = tr.dir().get<_Z>();
                break;
            case 5:
                numer = 1.0 + tr.pos().get<_Z>();
                denom = -tr.dir().get<_Z>();
                break;
            default:
                return false;
        }

        if (std::fabs(denom) < 0.00001) { //ray is parallel
            if (numer < 0) return false; // ray is out;
            else;                        // ray inside, no change to tIn, tOut
        }
        else { //ray is not parallel
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
        intersection.hit.emplace_back();
        intersection.hit[0].t = tIn;
        intersection.hit[0].obj = this;
        intersection.hit[0].point = ray.at(float(tIn));
        intersection.hit[0].normal = this->getTransform() *  boxNormal(inSurf);
        intersection.hit[0].entering = true;
        num++;
    }
    if (tOut > 0.0001){  //hit in front of eye
        intersection.hit.emplace_back();
        intersection.hit[num].t = tOut;
        intersection.hit[num].obj = this;
        intersection.hit[num].point = ray.at(float(tOut));
        intersection.hit[num].normal = this->getTransform() * boxNormal(outSurf);
        intersection.hit[num].entering = false;
        num++;
    }
    return (num > 0);
}

Vec4 MRay::Box::boxNormal(int surf) {
    Vec4 v;
    int m = surf/2, n = (surf%2)?-1:1;
    if (m == 0) v = Vec4(0, float(n),0,0);
    else if (m == 1) v = Vec4(float(n),0,0,0);
    else v = Vec4(0,0,float(n),0);
    return v;
}

std::ostream &MRay::operator<<(std::ostream &os, const Box &box) {
    os << "Box: {}";
    return os;
}

MRay::Box::Box(const Vec4 &pos, const Vec4 &size) {
    this->scale(size.get<0>(), size.get<1>(),size.get<2>());
    this->translate(pos.get<0>(),pos.get<1>(),pos.get<2>());
}

void Box::computeBoundingBox() {
    this->bb = BoundingBox(Vec3(-1.1,-1.1,-1.1),Vec3(1.1,1.1,1.1)); //additional margin to avoid precision errors
    this->bb.transform(this->transform);
}


