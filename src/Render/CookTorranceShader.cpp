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
    if (primaryRay.getDepth() > maxBounces) maxBounces = primaryRay.getDepth();
    const float dw = 0.0001f;
    const double ka = 1;
    const double kd = 0.80;
    const double ks = 1.0-kd;
    assert (ks >= 0);
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
    //sample.add(obj->getMaterial().emissive);
    Color3 ambient = ka * obj->getMaterial().getAmbient<CookTorrance>();
    if (obj->getTexture() != nullptr) {
        ambient *= first.obj->getTexture()->compute(first.point.get<0>(), first.point.get<1>(), first.point.get<2>());
    }
    sample.add(ambient);

    Vec4 normal = first.normal;
    normal.normalize();

    //reverse normal when exiting the object
    //when exiting && current ray object = nullptr => camera ray must be inside an object
    if (!first.entering) {
        normal = -normal;
        if (primaryRay.getObject() == nullptr) primaryRay.pushObject(first.obj);
    }
    // diff & spec
    for (const Light* light: scene->getLights()){
        double shadowFactor = this->shadowFactor<CookTorrance>(first.point, obj, light, intersection);
        if (shadowFactor == 0.0) continue;
        //diffuse
        Vec4 s = light->getVec(first.point);
        s.normalize();
        float mDotS = s.dot(normal); // lambert term;
        if (mDotS > 0.0){
            Color3 diffuse = (shadowFactor * mDotS * kd * fresnell(obj->getMaterial().getFresnell<CookTorrance>())) * light->color; //note: precompute fresnell values ??
            if (obj->getTexture() != nullptr) {
                diffuse *= first.obj->getTexture()->compute(first.point.get<0>(), first.point.get<1>(), first.point.get<2>());
            }
            assert(mDotS * kd * fresnell(obj->getMaterial().getFresnell<CookTorrance>()).get<0>() >= 0); //underflow
            assert(mDotS * kd * fresnell(obj->getMaterial().getFresnell<CookTorrance>()).get<1>() >= 0); //underflow
            assert(mDotS * kd * fresnell(obj->getMaterial().getFresnell<CookTorrance>()).get<2>() >= 0); //underflow
            sample.add(diffuse);
        }
        //specular
        Vec4 h  = v + s;
        h.normalize();
        float mDotH = h.dot(normal);
        if (mDotH > 0 && mDotS > 0){
            //numerical precision error, limit detla!
            double delta = std::max(std::min(normal.dot(h),1.0f),-1.0f);
            delta = std::acos(delta);
            double beck = this->beckmannDistribution(delta , obj->getMaterial().getRoughness<CookTorrance>());

            float hDotS = h.dot(s);
            double mDotV = normal.dot(v);
            double g = std::fmin(1.0f,2.0f*std::fmin(mDotH*mDotS/hDotS,mDotH*mDotV/mDotS));

            Vec4 spec = fresnell(obj->getMaterial().getFresnell<CookTorrance>(), mDotS) * float(beck * g / mDotV);
            Color3 specColor = light->color * (ks  * spec*shadowFactor);

            assert(ks  * spec.get<0>() >= 0);
            //assert(ks  * spec.get<0>() <= 255);
            assert(ks  * spec.get<1>() >= 0);
            //assert(ks  * spec.get<1>() <= 255);
            assert(ks  * spec.get<2>() >= 0);
            //assert(ks  * spec.get<2>() <= 255);
            sample.add(specColor);
        }

    }

    if (primaryRay.getDepth() == options.maxRayBounce)
        return sample;


    //refraction
    bool internalReflection = false;
    if (obj->getMaterial().getTransparancy<CookTorrance>() > options.transparencyThreshold){
        double cosa = normal.angle(-primaryRay.dir());
        double cosa2 = cosa*cosa;
        double sina2 = 1-cosa2;

        double n1, n2;

        Ray transmitted(primaryRay);
        if (first.entering){
            transmitted.pushObject(first.obj);
        }
        else{
            transmitted.eraseObject(first.obj);
        }
        Object* primaryObject = primaryRay.getObject();
        Object* refractedObject = transmitted.getObject();

        if (primaryObject == nullptr){
            n1 = 1;
            n2 = refractedObject->getMaterial().getRelativeSpeed<CookTorrance>();
        }else if (refractedObject == nullptr) {
            n1 = primaryObject->getMaterial().getRelativeSpeed<CookTorrance>();
            n2 = 1;
        }else{
            n1 = primaryObject->getMaterial().getRelativeSpeed<CookTorrance>();
            n2 = refractedObject->getMaterial().getRelativeSpeed<CookTorrance>();
        }



        double cr = n1/n2;
        double snell2 = 1-cr*cr*sina2; //snell2 = cos(theta2)^2

        //check for total internal reflection:
        //total internal reflection when sin(theta_2) < 0 => snell < 0

        double critAngle = std::acos(n2/n1);
        double angle = std::acos(cosa);
        if (angle > critAngle && n2/n1 < 1 || snell2 < 0){
            internalReflection = true;
        }else if(first.thinMaterial) {
            transmitted.setPos(first.point - this->options.eps * normal);
            transmitted.setDir(primaryRay.dir());
            transmitted.setDepth(primaryRay.getDepth() + 1);
            sample.add(obj->getMaterial().getTransparancy<CookTorrance>() * shade(transmitted));
        }
        else {
            assert(snell2 >= 0);
            double snell = sqrt(snell2);
            transmitted.setPos(first.point - this->options.eps * normal);
            transmitted.setDir(float(cr) * primaryRay.dir() + float(cr * cosa - snell) * normal);
            transmitted.setDepth(primaryRay.getDepth() + 1);
            sample.add(obj->getMaterial().getTransparancy<CookTorrance>() * shade(transmitted));
        }

    }

    //reflections
    if (obj->getMaterial().getShininess<CookTorrance>() > options.shininessThreshold || internalReflection){
        //get reflected ray,
        Ray reflected;
        reflected.setPos(first.point + this->options.eps * normal);
        Vec4 d = primaryRay.dir() - 2 *(normal.dot(primaryRay.dir()))*normal;
        reflected.setDir(d);
        reflected.setDepth(primaryRay.getDepth() + 1);

        //recursive call to shade
        if (internalReflection)
            sample.add(obj->getMaterial().getTransparancy<CookTorrance>() * shade(reflected));
        else
            sample.add(obj->getMaterial().getShininess<CookTorrance>() * shade(reflected));
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

Vec4 CookTorranceShader::fresnell(const Vec4 &refraction, Vec4 &m, Vec4 &s) {
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
Vec4 CookTorranceShader::fresnell(const Vec4 &refraction, float mDotS) {
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
Vec4 CookTorranceShader::fresnell(const Vec4 &refraction) {
    Vec4 nmin = (refraction - 1);
    Vec4 nplus = (refraction + 1);
    return nmin*nmin/(nplus*nplus);
}
double CookTorranceShader::beckmannDistribution(double angle, double m) {
    double exponent= std::tan(angle)/m;
    double cosa = std::cos(angle);
    double num = std::exp(-exponent*exponent);
    double denom = 4 * m * m * cosa*cosa*cosa*cosa;
    return num/denom;
}






