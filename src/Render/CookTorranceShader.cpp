//
// Created by Maarten Van Loo on 14/10/2022.
//

#include <Objects/Intersection.h>
#include <Light/Color3.h>
#include <Ray.h>
#include <Render/CookTorranceShader.h>

using namespace MRay;
CookTorranceShader::CookTorranceShader(Scene *scene, Camera *camera, Options &options) : Shader(scene, camera,
                                                                                                      options) {

}
Color3 CookTorranceShader::shade(int x, int y) {
    Ray primaryRay = this->camera->getPrimaryRay(x,y);
    Color3 test = this->shade(primaryRay);
    //std::cout << test << "\n";
    return test;
}
Color3 CookTorranceShader::shade(int x, int y, Intersection &intersection) {
    Ray primaryRay = this->camera->getPrimaryRay(x,y);
    return this->shade(primaryRay, intersection);
}
Color3 CookTorranceShader::shade(Ray &primaryRay) {
    Intersection intersection;
    return this->shade(primaryRay, intersection);
}

Color3 CookTorranceShader::shade(Ray &primaryRay, Intersection &intersection) {
    const float dw = 0.0001f;
    const float kd = 0.9f;
    const float ks = 1.0f-kd;
    Color3 sample =  Color3();

    Hit first = Hit();

    if (!getFirstHit(primaryRay, first, intersection)){
        //no hit, set background color:
        sample.add(options.background);
        //sample.add(Color3(0x87, 0xCE, 0xFA));
        return sample;
    }

    Vec4 v = - primaryRay.dir(); //always normalized
    Object* obj = first.obj;

    //TODO: check these
    sample.add(obj->getMaterial().emissive);
    sample.add(Color3(obj->getMaterial().ambient));

    Vec4 normal = obj->getTransform() * first.normal;
    normal.set<3>(0);
    normal.normalize();

    // diff & spec
    for (const Light* light: scene->getLights()){
        if (isInShadow(first.point,obj, light, intersection)) continue;
        //diffuse
        Vec4 s = light->getVec(first.point);
        s.normalize();
        float mDotS = s.dot(normal); // lambert term;
        if (mDotS > 0.0){
            Vec4 tmp = mDotS * kd * fresnell(obj->getMaterial().fresnell);
            Color3 diffuse = mDotS * kd * fresnell(obj->getMaterial().fresnell) * light->color; //note: precompute fresnell values ??
            if (obj->getTexture() != nullptr){
                diffuse *= first.obj->getTexture()->compute(first.point.get<0>(),first.point.get<1>(),first.point.get<2>(),10);
            }
            sample.add(diffuse);
        }
        //specular
        Vec4 h  = v + s;
        h.normalize();
        float mDotH = h.dot(normal);
        if (mDotH > 0){
            float delta = std::acos(normal.dot(h));
            float d = this->beckmannDistribution(delta , 0.2f);

            float hDotS = h.dot(s);
            float mDotV = normal.dot(v);
            float g = float(std::fmin(1.0f,2.0f*std::fmin(mDotH*mDotS/hDotS,mDotH*mDotV/mDotS)));

            Vec4 spec = fresnell(obj->getMaterial().fresnell, mDotS) * d * g / mDotV;
            Color3 specColor = light->color * ks  * spec;
            sample.add(specColor);
        }

    }

    if (primaryRay.getDepth() == options.maxRayBounce)
        return sample;
    //reflections
    if (obj->getMaterial().shininess > options.shininessThreshold){
        //get reflected ray,
        Ray reflected;
        reflected.setPos(first.point + options.eps * normal);
        Vec4 d = primaryRay.dir() - 2 *(normal.dot(primaryRay.dir()))*normal;
        reflected.setDir(d);
        reflected.setDepth(primaryRay.getDepth() + 1);

        //recursive call to shade
        sample.add(obj->getMaterial().shininess * shade(reflected));
    }
    return sample;
}

float CookTorranceShader::fresnell(float refraction, Vec4 &m, Vec4 &s) {
    float c = m.dot(s);
    float g = std::sqrt(refraction + c * c - 1);

    float gminc = g-c;
    float gplusc = g+c;
    float fac1 = 0.5f*gminc*gminc/(gplusc*gplusc);

    float num = c * gplusc - 1;
    float denom = c * gminc + 1;
    float fac2 =1+(num*num/(denom*denom));

    return fac1 * fac2;
}

Vec4 CookTorranceShader::fresnell(Vec4 &refraction, Vec4 &m, Vec4 &s) {
    float c = m.dot(s);
    Vec4 g = refraction + c * c - 1;
    Vec4::sqrt(g);

    Vec4 gminc = g-c;
    Vec4 gplusc = g+c;
    Vec4 fac1 = 0.5f*gminc*gminc/(gplusc*gplusc);

    Vec4 num = c * gplusc - 1;
    Vec4 denom = c * gminc + 1;
    Vec4 fac2 = 1 + (num*num/(denom*denom));

    return fac1 * fac2;
}
Vec4 CookTorranceShader::fresnell(Vec4 &refraction, float mDotS) {
    float c = mDotS;
    Vec4 g = refraction + c * c - 1;
    Vec4::sqrt(g);

    Vec4 gminc = g-c;
    Vec4 gplusc = g+c;
    Vec4 fac1 = 0.5f*gminc*gminc/(gplusc*gplusc);

    Vec4 num = c * gplusc - 1;
    Vec4 denom = c * gminc + 1;
    Vec4 fac2 = 1 + (num*num/(denom*denom));

    return fac1 * fac2;
}
float CookTorranceShader::fresnell(float refraction) {
    float nmin = (refraction - 1);
    float nplus = (refraction + 1);
    return nmin*nmin/(nplus*nplus);
}
Vec4 CookTorranceShader::fresnell(Vec4 &refraction) {
    Vec4 nmin = (refraction - 1);
    Vec4 nplus = (refraction + 1);
    return nmin*nmin/(nplus*nplus);
}
float CookTorranceShader::beckmannDistribution(float angle, float m) {
    float exponent= std::tan(angle)/m;
    float cosa = std::cos(angle);
    float num = std::exp(-exponent*exponent);
    float denom = 4 * m * m * cosa*cosa*cosa*cosa;
    return num/denom;
}






