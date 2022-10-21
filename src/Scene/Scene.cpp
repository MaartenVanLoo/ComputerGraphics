//
// Created by Maarten Van Loo on 30/09/2022.
//

#include <Materials/MaterialsLibrary.h>
#include <Scene/Scene.h>
#include <Objects/Plane.h>
#include <fstream>
#include <json/value.h>
#include <Scene/SDLParser.h>


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
    obj->computeBoundingBox();
    this->objects.push_back(obj);
}
void MRay::Scene::addLight(Light* light) {
    this->lights.push_back(light);
}

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

void Scene::load(const std::string& file) {
    Stopwatch stopwatch = Stopwatch();
    stopwatch.start();
    SDLParser parser = SDLParser();
    parser.parse(file);

    this->objects = parser.getObjects();
    this->lights = parser.getLights();
    stopwatch.stop();
    std::cout<< stopwatch << std::endl;

}

void Scene::hardReset(){
    this->clearLights();
    this->clearObjects();
}
void Scene::clearObjects() {
    for (auto&obj: this->objects){
        delete obj;
    }
    this->objects.clear();
}






