//
// Created by Maarten Van Loo on 11/10/2022.
//

#include <Render/PhongShader.h>
#include <Objects/ObjectCore.h>
#include <Camera/Camera.h>

using namespace MRay;
MRay::PhongShader::PhongShader(Scene *scene, Camera* camera, Options& options) : Shader(scene, camera, options){}

Color3 MRay::PhongShader::shade(int x, int y) {
    Ray primaryRay = this->camera->getPrimaryRay(x,y);
    return this->shade(primaryRay);
}

Color3 PhongShader::shade(int x, int y, Intersection &intersection) {
    Ray primaryRay = this->camera->getPrimaryRay(x,y);
    return this->shade(primaryRay, intersection);
}
Color3 MRay::PhongShader::shade(Ray &primaryRay){
    Intersection intersection;
    return this->shade(primaryRay, intersection);
}


Color3 MRay::PhongShader::shade(Ray &primaryRay, Intersection& intersection) {
    Color3 sample =  Color3();

    Hit first = Hit();

    if (!getFirstHit(primaryRay, first, intersection)){
        //no hit, set background color:
        //sample.add(Color3(0x87, 0xCE, 0xFA));
        sample.add(options.background);
        //sample.add(Color3(0, 0,0));
        return sample;
        //return color;
    }

    Vec4 v = - primaryRay.dir(); //always normalized
    Object* obj = first.obj;

    //TODO: check these
    //sample.add(obj->getMaterial().emissive);
    sample.add(Color3(obj->getMaterial().getAmbient<Phong>()));

    Vec4 normal = first.normal;
    normal.normalize();
    //reverse normal when exiting the object
    if (!first.entering)
        normal = -normal;

    // diff & spec
    for (const Light* light: scene->getLights()){
        double shadowFactor = this->shadowFactor<Phong>(first.point,obj, light, intersection);
        if (shadowFactor == 0.0) continue;
        //diffuse
        Vec4 s = light->getVec(first.point);
        s.normalize();
        float mDotS = s.dot(normal); // lambert term;
        if (mDotS > 0.0){
            Color3 diffuse = mDotS * obj->getMaterial().getDiffuse<Phong>() * light->color;
            if (obj->getTexture() != nullptr){
                diffuse *= first.obj->getTexture()->compute(first.point.get<0>(),first.point.get<1>(),first.point.get<2>());
            }
            sample.add(diffuse);
        }
        //specular
        Vec4 h  = v + s;
        h.normalize();
        float mDotH = h.dot(normal);
        if (mDotH > 0){
            double phong = std::pow(mDotH, obj->getMaterial().getSpecularExponent<Phong>());
            Color3 specColor = phong* obj->getMaterial().getSpecular<Phong>() * light->color;
            sample.add(specColor);
        }
    }

    if (primaryRay.getDepth() == options.maxRayBounce) return sample;
    //reflections
    if (obj->getMaterial().getShininess<Phong>() > options.shininessThreshold){
        //get reflected ray,
        Ray reflected;
        reflected.setPos(first.point);// + options.eps * normal);
        Vec4 d = primaryRay.dir() - 2 *(normal.dot(primaryRay.dir()))*normal;
        reflected.setDir(d);
        reflected.setDepth(primaryRay.getDepth() + 1);

        //recursive call to shade
        sample.add(obj->getMaterial().getShininess<Phong>() * shade(reflected));
    }
    return sample;
}





