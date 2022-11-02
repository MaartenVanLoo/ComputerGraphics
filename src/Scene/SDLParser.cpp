//
// Created by maart on 19/10/2022.
//

#include <Scene/SDLParser.h>
#include <Textures/Checkerboard.h>
#include "Textures/WaterTexture.h"

template<class M>
bool contains(M const&){return true;}
template<class M, class K, class...Ks>
bool contains(M const&m, K const&k, Ks const&...ks){
    auto it=m.find(k);
    if (it==m.end()) return false;
    return contains(it->second, ks...);
}
using namespace MRay;

std::vector<Object *> MRay::SDLParser::getObjects() {
    std::vector<Object*> objects;
    objects.reserve(this->loadedObjects.size());
    for (auto& o:this->loadedObjects){
        objects.push_back(o.second);
    }
    return objects;
}
std::vector<Light*> MRay::SDLParser::getLights() {
    std::vector<Light*> lights;
    lights.reserve(this->loadedLights.size());
    for (auto& l:this->loadedLights){
        lights.push_back(l.second);
    }
    return lights;
}


void MRay::SDLParser::parse(const std::string& sdlFile) {
    Json::Value root;
    std::ifstream file;
    try{
        file.open(sdlFile);
        file >> root;
        if (file.fail()){
            throw std::ios::failure("Something went wrong when reading the SDL file: " + sdlFile);
        }
        file.close();
    }
    catch(std::exception& e){
        file.close();
        throw e; //continue throwing
    }

    if (!root["materials"].isNull()){
        materialParser(root["materials"]);
    }
    if (!root["objects"].isNull()){
        objectParser(root["objects"]);
    }
    if (!root["lights"].isNull()){
        lightParser(root["lights"]);
    }
    //compute bounding boxes
    for (auto& obj: this->loadedObjects){
        obj.second->computeBoundingBox();
    }
}

void MRay::SDLParser::objectParser(Json::Value objects) {
    auto objIds = objects.getMemberNames();
    std::cout << "Parsing " << objIds.size() << " objects\n";

    for (auto objId = objIds.begin(); objId != objIds.end(); objId++){
        std::cout << "Parsing:" << *objId << " " << objId-objIds.begin() << "/" << objIds.size() << "\n";
        Json::Value obj = objects[*objId];
        if (obj["type"].isNull()){
            std::cout << "Object at index " << objId-objIds.begin() << "has no type specified\n";
        }
        std::string type = obj["type"].asString();
        Object* object = objectCreator(type, obj);
        if (object != nullptr) this->loadedObjects[*objId] = object;
        if (object != nullptr) std::cout << *objId << " accepted\n";
    }
}

void MRay::SDLParser::lightParser(Json::Value lights) {
    auto lightIds = lights.getMemberNames();
    for (auto lightId = lightIds.begin(); lightId != lightIds.end(); lightId++){
        Json::Value l = lights[*lightId];
        if (l["type"].isNull()){
            std::cout << "Object at index " << lightId-lightIds.begin() << "has no type specified\n";
        }
        std::string type = l["type"].asString();
        Light* light = lightCreator(type, l);
        if (light != nullptr) this->loadedLights[*lightId] = light;
    }
}

void MRay::SDLParser::materialParser(Json::Value materials) {

}

Object* MRay::SDLParser::objectCreator(std::string &type, Json::Value config) {
    //type to lower:
    for(auto &c : type)
        c = std::tolower(c);

    Object* object = nullptr;
    if (type == "sphere"){
        object = new Sphere();

        Material material = getMaterial(config.get("material","").asString());
        object->setMaterial(material);

        object = transformObject(object, config["transformation"]);
    }
    else if (type == "box" || type == "cube"){
        object = new Box();

        Material material = getMaterial(config.get("material","").asString());
        object->setMaterial(material);

        object = transformObject(object, config["transformation"]);
    }
    else if (type == "plane"){
        Material material = getMaterial(config.get("material","").asString());
        Texture* texture = getTexture(config.get("texture","").asString(), config["texture"]);

        object = new Plane(); //TODO: check problem with LCS and GCS, now no scaling is used inside plane
        object->setMaterial(material);
        object->setTexture(texture);
        object = transformObject(object, config["transformation"]);
    }
    else if (type == "taperedcylinder"){
        Material material = getMaterial(config.get("material","").asString());
        float s = config.get("s",1).asFloat();
        object = new TaperedCylinder(s);

        object->setMaterial(material);
        object = transformObject(object, config["transformation"]);
    }
    else if (type == "booleandifference"){
        if (config["left"].isNull() && config["left"].isString()){
            std::cout << "Boolean difference doesn't contain a left member\n";
            return nullptr;
        }
        if (config["right"].isNull() && config["right"].isString()){
            std::cout << "Boolean difference doesn't contain a right member\n";
            return nullptr;
        }

        std::string left = config["left"].asString();
        std::string right = config["right"].asString();

        if (!contains(loadedObjects,left)) {
            std::cout << "Object " << left << " is not (yet) defined\n";
            return nullptr;
        }
        if (!contains(loadedObjects,right)){
            std::cout << "Object "<< right << " is not (yet) defined\n";
            return nullptr;
        }

        object = new BooleanDifference(loadedObjects[left],loadedObjects[right]);
        object = transformObject(object, config["transformation"]);
        loadedObjects.erase(left);
        loadedObjects.erase(right);

    }
    else if (type == "booleanintersection"){
        if (config["left"].isNull() && config["left"].isString()){
            std::cout << "Boolean intersection doesn't contain a left member\n";
            return nullptr;
        }
        if (config["right"].isNull() && config["right"].isString()){
            std::cout << "Boolean intersection doesn't contain a right member\n";
            return nullptr;
        }

        std::string left = config["left"].asString();
        std::string right = config["right"].asString();

        if (!contains(loadedObjects,left)) {
            std::cout << "Object " << left << " is not (yet) defined\n";
            return nullptr;
        }
        if (!contains(loadedObjects,right)){
            std::cout << "Object "<< right << " is not (yet) defined\n";
            return nullptr;
        }

        object = new BooleanIntersection(loadedObjects[left],loadedObjects[right]);
        object = transformObject(object, config["transformation"]);
        loadedObjects.erase(left);
        loadedObjects.erase(right);
    }
    else if (type == "booleanunion"){
        if (config["left"].isNull() && config["left"].isString()){
            std::cout << "Boolean union doesn't contain a left member\n";
            return nullptr;
        }
        if (config["right"].isNull() && config["right"].isString()){
            std::cout << "Boolean union doesn't contain a right member\n";
            return nullptr;
        }

        std::string left = config["left"].asString();
        std::string right = config["right"].asString();

        if (!contains(loadedObjects,left)) {
            std::cout << "Object " << left << " is not (yet) defined\n";
            return nullptr;
        }
        if (!contains(loadedObjects,right)){
            std::cout << "Object "<< right << " is not (yet) defined\n";
            return nullptr;
        }

        object = new BooleanUnion(loadedObjects[left],loadedObjects[right]);
        object = transformObject(object, config["transformation"]);
        loadedObjects.erase(left);
        loadedObjects.erase(right);
    }

    return object;
}

Light* MRay::SDLParser::lightCreator(std::string &type, Json::Value config) {
    //type to lower:
    for(auto& c : type)
        c = tolower(c);
    Light* light= nullptr;
    if (type == "pointlight"){
        Json::Value point = config["position"];
        float px = 0,py= 0,pz=0;
        if (!point.isNull()){
            px = point.get(Json::ArrayIndex(0),0).asFloat();
            py = point.get(Json::ArrayIndex(1),0).asFloat();
            pz = point.get(Json::ArrayIndex(2),0).asFloat();
        }
        light = new PointLight(px,py,pz);

    }
    else{
        std::cout << "Unknown light type found: " << type << "\n";
    }
    return light;
}

MRay::Material MRay::SDLParser::getMaterial(const std::string &material) {
    if (material.empty()){
        std:: cout << "No material specified" << "\n";
        return Material();
    }
    if (contains(customMaterials,material)){
        return customMaterials[material];
    }
    //look in default library:
    if (contains(MaterialsLibrary::materials,material)){
        return MaterialsLibrary::materials.at(material);
    }
    else{
        std::cout << "WARNING: Material " << material << " not found in defined materials. Using empty material" << "\n";
        return Material();
    }
}

MRay::Texture *MRay::SDLParser::getTexture(const std::string &texture, Json::Value config) {
    if (texture == "checkboard"){
        return new Checkboard(5,5,5);
    }else if (texture =="water"){
        return new WaterTexture(0.1,0.1);
    }
    return nullptr;
}

MRay::Object *MRay::SDLParser::transformObject(Object* object, Json::Value transform) {
    Json::Value translate;
    Json::Value rotate;
    Json::Value scale;
    translate = transform["translate"];
    rotate = transform["rotate"];
    scale = transform["scale"];

    if (!scale.isNull() && scale.isArray()){
        float sx = scale.get(Json::ArrayIndex(0),1).asFloat();
        float sy = scale.get(Json::ArrayIndex(1),1).asFloat();
        float sz = scale.get(Json::ArrayIndex(2),1).asFloat();
        object->scale(sx,sy,sz);
    }
    if (!rotate.isNull() && rotate.isArray()){
        float rx = rotate.get(Json::ArrayIndex(0),0).asFloat();
        float ry = rotate.get(Json::ArrayIndex(1),0).asFloat();
        float rz = rotate.get(Json::ArrayIndex(2),0).asFloat();
        object->rotate(rx,ry,rz);
    }
    if (!translate.isNull() && translate.isArray()){
        float tx = translate.get(Json::ArrayIndex(0),1).asFloat();
        float ty = translate.get(Json::ArrayIndex(1),1).asFloat();
        float tz = translate.get(Json::ArrayIndex(2),1).asFloat();
        object->translate(tx,ty,tz);
    }
    return object;
}



