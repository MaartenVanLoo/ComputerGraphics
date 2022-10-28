//
// Created by Maarten Van Loo on 12/10/2022.
//

#include <Objects/TaperedCylinder.h>

MRay::TaperedCylinder::TaperedCylinder(float s) :s(s){

}

bool MRay::TaperedCylinder::hitPoint(MRay::Ray &ray, MRay::Intersection &intersection, const Options &options) {
    //bounding box test
    if (!this->bb.hit(ray)) return false;

    Ray tr = ray.transform(this->invtransform);
    int num = 0;

    //intersections with cylinder wall
    double d = (this->s - 1)*tr.dir().get<_Z>();
    double f = 1 + (s-1)*tr.pos().get<_Z>();
    double a = tr.dir().get<_X>() * tr.dir().get<_X>() + tr.dir().get<_Y>() * tr.dir().get<_Y>() - d * d;
    double b = tr.pos().get<_X>() * tr.dir().get<_X>() + tr.pos().get<_Y>() * tr.dir().get<_Y>() - f * d;
    double c = tr.pos().get<_X>() * tr.pos().get<_X>() + tr.pos().get<_Y>() * tr.pos().get<_Y>() - f * f;
    double discr = b*b-a*c;

    if (discr >= 0.0001) {

        double discRoot = std::sqrt(discr);
        auto hit1 = float((-b - discRoot) / a);
        auto hit2 = float((-b + discRoot) / a);


        if (hit1 > 0.0001) {
            Vec4 p = tr.at(hit1);
            if (p.get<_Z>() > 0 && p.get<_Z>() < 1) {
                intersection.hit.emplace_back();
                intersection.hit[0].t = hit1;
                intersection.hit[0].obj = this;
                intersection.hit[0].point = ray.at(hit1);
                intersection.hit[0].normal = this->normal(p);
                //intersection.hit[0].normal = this->getTransform() * this->normal(p);
                intersection.hit[0].entering = true;
                intersection.hit[0].surface = 0;
                num++;
            }
        }
        if (hit2 > 0.0001) {
            Vec4 p = tr.at(hit2);
            if (p.get<_Z>() > 0 && p.get<_Z>() < 1) {
                intersection.hit.emplace_back();
                intersection.hit[num].t = hit2;
                intersection.hit[num].obj = this;
                intersection.hit[num].point = ray.at(hit2);
                //intersection.hit[num].normal = this->getTransform() * this->normal(p);
                intersection.hit[num].normal = this->normal(p);
                intersection.hit[num].entering = false;
                intersection.hit[num].surface = 0;
                num++;
            }
        }
    }
    //hits with base planes
    if (std::abs(tr.dir().get<_Z>()) >= 0.00001) { // avoid parallel with base! => no intersect!
        //hit with z = 0:
        double hit = -tr.pos().get<_Z>() / tr.dir().get<_Z>();
        if (hit >= 0.0001) {
            Vec4 p = tr.at(float(hit));
            if (p.dot(p) < 1) {//note p = {_X,_Y,0,1}, p.dot doesn't use last value!
                intersection.hit.emplace_back();
                intersection.hit[num].t = hit;
                intersection.hit[num].obj = this;
                intersection.hit[num].point = ray.at(float(hit));
                intersection.hit[num].normal = this->transformNormal(Vec4(0, 0, -1, 0));
                //intersection.hit[num].normal = this->getTransform() * Vec4(0, 0, -1, 0);
                intersection.hit[num].entering = tr.dir().dot(intersection.hit[num].normal) > 0; //if normal & dir in same direction, dot product is positive and ray is leaving
                intersection.hit[num].surface = 1;
                num++;
            }
        }
        //hit with z = 1:
        hit = (1-tr.pos().get<_Z>()) / tr.dir().get<_Z>();
        if (hit >= 0.0001) {
            Vec4 p = tr.at(float(hit));
            if (p.dot(p) - 1< this->s * this->s ) {//note p = {_X,_Y,1,1}, p.dot doesn't use last value!, result = X² + Y² + 1 < s², correct for '1' term
                intersection.hit.emplace_back();
                intersection.hit[num].t = hit;
                intersection.hit[num].obj = this;
                intersection.hit[num].point = ray.at(float(hit));
                //intersection.hit[num].normal = this->getTransform() * Vec4(0, 0, 1, 0);
                intersection.hit[num].normal = this->transformNormal(Vec4(0, 0, 1, 0));
                intersection.hit[num].entering = tr.dir().dot(intersection.hit[num].normal) > 0; //if normal & dir in same direction, dot product is positive and ray is leaving
                intersection.hit[num].surface = 2;
                num++;
            }
        }
    }

    //sort hits:
    if (num >= 2){
        if (intersection.hit[0].t > intersection.hit[1].t){
            std::swap(intersection.hit[0], intersection.hit[1]);
        }
        intersection.hit[0].entering = true;
        intersection.hit[1].entering = false;
    }
    if (num == 1){
        intersection.hit[0].entering = false; //only way to have a single intersection is a ray that starts inside the object
    }
    if (num == 2){
        if( std::abs( intersection.hit[0].t- intersection.hit[1].t) < options.eps){
            intersection.hit[0].thinMaterial = true;
            intersection.hit[1].thinMaterial = true;
        }
    }
    return (num > 0);
}

MRay::Vec4 MRay::TaperedCylinder::normal(Vec4 &point) const  {
    if (point.get<_Z>() == 0) return Vec4(0, 0, -1, 0); //base plane
    if (point.get<_Z>() == 1) return Vec4(0, 0, 1, 0);  //top plane
    Vec4 norm= Vec4(point.get<_X>(), point.get<_Y>(), -(this->s - 1) * (1 + (this->s - 1) * point.get<_Z>()), 0);                       //wall
    norm = transformNormal(norm);
    return norm;
}

void MRay::TaperedCylinder::computeBoundingBox() {
    float m = float(std::max(s,1.0f)* 1.1);
    this->bb = BoundingBox(Vec3(-m,-m,-0.1f),Vec3(m,m,1.1f)); //additional margin to avoid precision errors
    this->bb.transform(this->transform);
}
