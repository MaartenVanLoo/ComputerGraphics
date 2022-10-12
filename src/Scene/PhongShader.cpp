//
// Created by maart on 11/10/2022.
//

#include <Scene/PhongShader.h>
#include <Objects/ObjectCore.h>
#include <Camera/Camera.h>

using namespace MRay;
MRay::PhongShader::PhongShader(Scene *scene) : Shader(scene) {}
Color3 MRay::PhongShader::shade(int x, int y) {
    Ray primaryRay = scene->getCamera().getPrimaryRay(x,y);
    return this->shade(primaryRay);
}

Color3 MRay::PhongShader::shade(Ray &primaryRay) {
    Intersection intersect; //object to store intersections, can be reused!
    Color3 color;
    color.openTransaction();


    Hit first = Hit();
    if (!this->getFirstHit(primaryRay, first, intersect)){
        //no hit, set background color:
        color.add(Color3(0x87, 0xCE, 0xFA));
        return color;
    }

    Vec4 v = - primaryRay.dir(); //always normalized
    Object* obj = first.obj;

    color.add(obj->getMaterial().emissive);
    Vec4 normal = obj->getTransform() * first.normal;
    normal.normalize();


    for (const Light* light: scene->getLights()){
        if (this->isInShadow(first.point,obj, light, intersect)) continue;
        //diffuse
        Vec4 s = light->getVec(first.point);
        s.normalize();
        float mDotS = s.dot(normal); // lambert term;
        if (mDotS > 0.0){
            Color3 diffuse = mDotS * obj->getMaterial().diffuse * light->color;
            color.add(diffuse);
        }
        //specular
        Vec4 h  = v + s;
        h.normalize();
        float mDotH = h.dot(normal);
        float phong = std::pow(mDotH, obj->getMaterial().specularExponent);
        Color3 specColor = phong* obj->getMaterial().specular * light->color;
        color.add(specColor);
        



    }

    color.closeTransaction();
    return color;
    return Color3();
}



