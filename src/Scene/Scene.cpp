//
// Created by maart on 30/09/2022.
//

#include <Materials/MaterialsLibrary.h>
#include <Scene/Scene.h>
#include <Objects/Plane.h>
#include <Render/PhongShader.h>
#include <Objects/Sphere.h>
#include <Objects/Box.h>
#include <Textures/Checkerboard.h>
#include <Objects/TaperedCylinder.h>
#include <math.h>
#include <Objects/BooleanUnion.h>
#include <Objects/BooleanIntersection.h>
#include <Objects/BooleanDifference.h>



using namespace MRay;
MRay::Scene::Scene() {

}
MRay::Scene::~Scene() {
    for (auto obj : this->objects){
        delete obj;
    }
    for (auto light: this->lights){
        delete light;
    }
}

std::ostream &MRay::operator<<(std::ostream &os, const Scene &scene) {
    os << "Scene: {" <<"objects: " << scene.objects.size() << "}";
    return os;
}

void MRay::Scene::addObject(Object *obj) {
    this->objects.push_back(obj);
}
void MRay::Scene::addLight(Light* light) {
    this->lights.push_back(light);
}

/* TODO: discard later
Color3 MRay::Scene::shade(int x, int y) {
    const int N = 1; //super sampling ratio //not smart! => dynamic super sampling?
    Intersection intersect; //object to store intersections, can be reused!
    Color3 color;
    Color3 sample;
    color.openTransaction();
    //super sample:


    for (int i =0; i < N; i++){
        sample.clear();
        Ray primary =  this->camera.getPrimaryRay(x,y,float(rand())/RAND_MAX,float(rand())/RAND_MAX);

        Hit first = Hit();

        if (y == 538 && x >= 928 && x <= 930 ) {
            getFirstHit(primary, first, intersect);
        }
        if (!getFirstHit(primary, first, intersect)){
            //no hit, set background color:
            color.add(Color3(0x87, 0xCE, 0xFA));
            continue;
            //return color;
        }

        Vec4 v = - primary.dir(); //always normalized
        Object* obj = first.obj;

        sample.add(obj->getMaterial().emissive);
        sample.add(Color3(obj->getMaterial().ambient));

        Vec4 normal = obj->getTransform() * first.normal;
        normal.normalize();

        // diff & spec
        for (const Light* light: this->lights){
            if (isInShadow(first.point,obj, light, intersect)) continue;
            //diffuse
            Vec4 s = light->getVec(first.point);
            s.normalize();
            float mDotS = s.dot(normal); // lambert term;
            if (mDotS > 0.0){
                Color3 diffuse = mDotS * obj->getMaterial().diffuse * light->color;
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
                float phong = std::pow(mDotH, obj->getMaterial().specularExponent);
                Color3 specColor = phong* obj->getMaterial().specular * light->color;
                sample.add(specColor);
            }

        }
        color.add(sample);
        //only emissive model:
        //if (first.t>=0){
        //    color = first.obj->getMaterial().emissive;
        //    //rgb = Color3(x, y, 0);
        //}

    }

    color.closeTransaction();
    return color;
}
*/

/*
 * TODO: discard later

bool MRay::Scene::getFirstHit(Ray &ray, Hit &best, Intersection& intersect,  const Object* ignore) const {
    bool flag = false;
    for (auto obj: this->objects){
        if (obj == ignore) continue;
        intersect.clear();
        if (obj->hitPoint(ray, intersect)){
            Hit hit = intersect.hit[0];
            if (best.t > hit.t && hit.t >= 0){
                best = hit;
                flag = true;
            }
        }
    }
    return flag;
}*/

/*
 * TODO: discard later

bool MRay::Scene::isInShadow(const Vec4 &point, const Object* ignore, const Light* light, Intersection& intersect) const {
    //ray to light source
    Ray ray = light->getRay(point);

    //get distance between point and light:
    float dist = light->getDist(point); //square of the distance!

    //look for intersections:
    Hit best;
    intersect.clear();
    for (auto obj: this->objects){
        if (obj->hitPoint(ray, intersect)){
            for (const auto& h: intersect.hit){
                if (h.obj == ignore){
                    Vec4 p = h.point - point;
                    if (p.dot(p) < 1e-6) continue; //this is the original point
                }
                if (dist > h.t * h.t)
                    return true; //object between point and light
            }
        }
    }
    //no object found between point and light => not in shadow
    return false;



}
*/

void MRay::Scene::clearLights() {
    for (auto l: this->lights){
        delete l;
    }
    this->lights.clear();
}

const std::vector<Object *> &MRay::Scene::getObjects() const {
    return objects;
}

const std::vector<Light *> &MRay::Scene::getLights() const {
    return lights;
}

void Scene::load(std::string &file) {


    Object* obj = nullptr;
    Object* obj1 = nullptr;
    Object* obj2 = nullptr;
    Texture* texture = nullptr;

    obj = new Plane(Vec4(0,0,0,0),Vec4(0,0,1,0));
    //obj->setTexture(new Checkboard(5,5,5));
    obj->setMaterial(MaterialsLibrary::gray_rubber());
    this->addObject(obj);

    obj = new TaperedCylinder(0.5);
    Material mat = MaterialsLibrary::red_plastic();
    //mat.ambient = Vec3(255,255,255);
    obj->setMaterial(mat);
    obj->scale(1,1,2);
    obj->rotate(CV_PI/2,0,-1);
    obj->translate(0,-4.5,5);
    this->addObject(obj);

    obj = new Sphere(Vec4(0,-2,2,1),1);
    obj->setMaterial(MaterialsLibrary::red_plastic());
    this->addObject(obj);

    obj = new Sphere(Vec4(0,2,2,1),1);
    obj->setMaterial(MaterialsLibrary::bronze());
    this->addObject(obj);

    //BooleanIntersection
    obj1 = new Sphere(Vec4(3,-1.8,8,1),1);
    obj1->setMaterial(MaterialsLibrary::red_plastic());
    //this->addObject(obj);

    obj2 = new Sphere(Vec4(3,-2.2,8,1),1);
    obj2->setMaterial(MaterialsLibrary::bronze());

    obj = new BooleanIntersection(obj1, obj2);
    this->addObject(obj);

    //BooleanUnion
    obj1 = new Box(Vec4(4,3,5,1), Vec4(1,1,1,1));
    obj1->setMaterial(MaterialsLibrary::jade());
    obj2 = new Sphere(Vec4(2.75,3,5,1),0.5);
    obj2->setMaterial(MaterialsLibrary::chrome());
    obj = new BooleanUnion(obj1,obj2);
    this->addObject(obj);

    //Boolean Difference
    obj1 = new Box(Vec4(4,3,7,1), Vec4(1,1,1,1));
    obj1->setMaterial(MaterialsLibrary::green_plastic());
    obj2 = new Sphere(Vec4(2.9,3,7,1),1.2);
    obj2->setMaterial(MaterialsLibrary::red_plastic());
    obj = new BooleanDifference(obj1,obj2);
    this->addObject(obj);
/*
    // creates problems
    obj = new  Sphere(Vec4(0,0,0,1),1);
    obj->scale(.1,1,1);
    obj->setMaterial(MaterialsLibrary::red_plastic());
    this->addObject(obj);
*/

    obj = new Box(Vec4(0,-0.5f,2.5f,1),Vec4(1,1,1,0));
    obj->setMaterial(MaterialsLibrary::green_plastic());
    this->addObject(obj);

    obj = new Box(Vec4(2,0,2,1),Vec4(1,1,1,0));
    obj->setMaterial(MaterialsLibrary::yellow_plastic());
    obj->rotate(0.0,0.0,0.5);
    this->addObject(obj);

    Light* light = new PointLight(Vec4(-10,0,30,1));
    this->addLight(light);
    light = new PointLight(Vec4(-5,15,20,1));
    this->addLight(light);
    //light = new PointLight(Vec4(-10,0,5,1));
    //this->addLight(light);
}







