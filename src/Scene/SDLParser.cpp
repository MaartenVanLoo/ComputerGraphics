//
// Created by maart on 19/10/2022.
//

#include <Scene/SDLParser.h>
#include <Textures/Checkerboard.h>
#include "Textures/WaterTexture.h"
#include "Utils/Logger.h"

using namespace MRay;

#pragma region helpers
std::string getType(const Json::Value& obj){
    std::string type = obj.get("type","").asString();
    //type to lower case
    //type to lower:
    for(auto &c : type)
        c = std::tolower(c);
    return type;
}
void splitIdentifier(const std::string& identifier, std::string& file, std::string& key){
    file = "";
    key = identifier;
    auto loc_dot = identifier.find('.');
    auto loc_colon  = identifier.find("::");
    auto loc = std::min(loc_dot, loc_colon);
    if (loc != std::string::npos){
        int length = loc == loc_colon?2:1;
        file = key.substr(0,loc_dot);
        key = key.erase(0,loc_dot+length);
    }
}
#pragma endregion


#pragma region contains functions
template<class M>
bool contains(M const&){return true;}
template<class M, class K, class...Ks>
bool contains(M const&m, K const&k, Ks const&...ks){
    auto it=m.find(k);
    if (it==m.end()) return false;
    return contains(it->second, ks...);
}

bool SDLParser::containsImport(const std::string &file) const{
    if (file.empty()) return false;
    if (contains(this->importedFiles, file)) return true;
    for (auto& pair:this->importedFiles){
        auto& imported = pair.second;
        if (imported.containsObject(file)) return true;
    }
    return false;
}
bool SDLParser::containsObject(const std::string &id) const {
    std::string file;
    std::string key;
    splitIdentifier(id, file, key);
    if (file.empty()){
        return contains(this->loadedObjects,key);
    }else{
        for (auto& pair:this->importedFiles){
            auto& imported = pair.second;
            if (imported.containsObject(key)) return true;
        }
    }
    return false;
}
bool SDLParser::containsLight(const std::string &id) const {
    std::string file;
    std::string key;
    splitIdentifier(id, file, key);
    if (file.empty()){
        return contains(this->loadedLights,key);
    }else{
        for (auto& pair:this->importedFiles){
            auto& imported = pair.second;
            if (imported.containsLight(key)) return true;
        }
    }
    return false;
}
bool SDLParser::containsMaterial(const std::string &id) const{
    std::string file;
    std::string key;
    splitIdentifier(id, file, key);
    if (file.empty()){
        return contains(this->loadedMaterials,key);
    }else{
        for (auto& pair:this->importedFiles){
            auto& imported = pair.second;
            if (imported.containsMaterial(key)) return true;
        }
    }
    return false;
}
#pragma endregion



std::vector<Object *> MRay::SDLParser::getObjects() {
    return sceneObjects;
}
std::vector<Light*> MRay::SDLParser::getLights() {
    return sceneLights;
}

void MRay::SDLParser::parse(const std::string& sdlFile){
    this->parse(sdlFile,true);
}
void MRay::SDLParser::parse(const std::string& sdlFile, bool topLevel) {
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

    if (topLevel){
        std::cout << "Loading file " << sdlFile << std::endl;
    }
    this->statistics.reset();

    if (!root["import"].isNull()){
        std::cout << "Importing files";
        importFiles(root["import"]);
        //TODO: import other files
    }
    if (!root["materials"].isNull()){
        loadMaterials(root["materials"]);
    }
    if (!root["objects"].isNull()){
        loadObjects(root["objects"]);
    }
    if (!root["lights"].isNull()){
        loadLights(root["lights"]);
    }
    this->validateMaterials();
    this->validateObjects();
    this->validateLights();

    if (!root["scene"].isNull()){
        this->hasScene = true;
        this->sceneConstructor(root["scene"]);
    }

    printStatistics();
}


#pragma region loading
void SDLParser::importFiles(const Json::Value& import) {
    if (!import.isArray()) return;
    for (Json::Value::ArrayIndex i = 0; i != import.size(); i++){
        std::string file = import.get(i,"").asString();
        if (file.empty()) continue;
        if (containsImport(file)) continue; //file already loaded;

        //import file
        this->importedFiles[file] = SDLParser(); //first add file to imported files to avoid self importing of file! (would be infinite loop!)
        this->importedFiles[file].parse(file);
    }
}

void SDLParser::loadMaterials(Json::Value& materials) {
    auto objIds = materials.getMemberNames();
    int count = 0;
    size_t total = objIds.size();
    for (auto objId = objIds.begin(); objId != objIds.end(); objId++){
        count++;
        std::cout << "\rLoading materials..." << count <<"/"<<total;
        Json::Value obj = materials[*objId];
        if (contains(this->loadedMaterials, *objId)){
            Logger::warning("Overriding existing material " + *objId);
        }
        this->loadedMaterials[*objId] = obj;

    }
    if (total> 0) std::cout << "\rLoading materials...Done" << std::endl;
    this->statistics.loadedMaterials = count;
}
void SDLParser::loadObjects(Json::Value &objects) {
    auto objIds = objects.getMemberNames();
    int count = 0;
    size_t total = objIds.size();
    for (auto objId = objIds.begin(); objId != objIds.end(); objId++){
        count++;
        std::cout << "\rLoading objects..." << count <<"/"<<total;

        Json::Value obj = objects[*objId];
        if (contains(this->loadedObjects, *objId)){
            Logger::warning("Overriding existing object " + *objId);
        }
        this->loadedObjects[*objId] = obj;
    }
    if (total> 0) std::cout << "\rLoading objects...Done" << std::endl;
    this->statistics.loadedObjects = count;
}
void SDLParser::loadLights(Json::Value &lights) {
    auto objIds = lights.getMemberNames();
    int count = 0;
    size_t total = objIds.size();
    for (auto objId = objIds.begin(); objId != objIds.end(); objId++){
        count++;
        std::cout << "\rLoading lights..." << count <<"/"<<total;

        Json::Value obj = lights[*objId];
        if (contains(this->loadedLights, *objId)){
            Logger::warning("Overriding existing light " + *objId);
        }
        this->loadedLights[*objId] = obj;

    }
    if (total > 0) std::cout << "\rLoading lights...Done" << std::endl;
    this->statistics.loadedLights = count;
}
#pragma endregion

#pragma region validation
bool validateTransformation(const Json::Value& transform) noexcept{
    try{
        // required fields

        //optional fields
        const Json::Value& translate = transform["translate"];
        const Json::Value& scale = transform["scale"];
        const Json::Value& rotate = transform["rotate"];

        if (!translate.isNull() && !translate.isArray()) return false; //translate must be an array if it exists!
        if (!scale.isNull() && !scale.isArray()) return false; //scale must be an array if it exists!
        if (!rotate.isNull() && !rotate.isArray()) return false; //rotate must be an array if it exists!

        //length of array doens't mater, non specified field will become a default value

        //all oké
        return true;
    }catch(...){}
    return false;
}
bool validateTextures(const std::string& texture){
    //todo: check if imported files contain custom textures??
    for (const auto& t: Texture::textureLibrary){
        if (t == texture) return true;
    }
    return false;
}
bool validateTextures(const Json::Value& texture) noexcept{
    if (texture.isNull()) return true;
    if (texture.isString()) return validateTextures(texture.asString());

    //todo: texture options???
    return false;

}


void SDLParser::validateMaterials() {
    int count = 0;
    size_t total = this->loadedMaterials.size();
    for (auto it = this->loadedMaterials.cbegin(), next_it = it; it != this->loadedMaterials.cend(); it = next_it){
        count++;
        std::cout << "\rValidating materials..." << count << "/" << total;
        ++next_it;
        std::string_view key = (*it).first;
        const Json::Value& material = (*it).second;
        if (!SDLParser::validateMaterial(material)){
            std::cout << "\n";
            Logger::warning("Material " + std::string(key) + " is not valid");
            this->loadedMaterials.erase(it);
        }

    }
    if (total > 0) std::cout << "\rValidating materials...Done\t\t\t\t\t\t" << std::endl;
    this->statistics.validMaterials = count;
}
bool SDLParser::validateMaterial(const Json::Value &material) noexcept{
    //TODO: implement custom materials
    Logger::warning("Custom materials are not implemented");
    return false;
}

void SDLParser::validateObjects() {
    int count = 0;
    size_t total = this->loadedObjects.size();
    for (auto it = this->loadedObjects.cbegin(), next_it = it; it != this->loadedObjects.cend(); it = next_it){
        count++;
        std::cout << "\rValidating objects..." << count << "/" << total;
        ++next_it;
        std::string_view key = (*it).first;
        const Json::Value& object = (*it).second;
        if (!SDLParser::validateObject(object)){
            std::cout << "\n";
            Logger::warning("Object " + std::string(key) + " is not valid");
            this->loadedObjects.erase(it);
        }

    }
    if (total > 0) std::cout << "\rValidating objects...Done\t\t\t\t\t\t" << std::endl;
    this->statistics.validObjects = count;
}
bool SDLParser::validateObject(const Json::Value &object) noexcept {
    //note: by getting the "optional fields" I ensure no exceptions will be thrown later in the code
    try {
        std::string type = getType(object);
        if (type.empty()) return false; //no valid type

        if (type == "sphere") {
            // required fields

            //optional fields
            std::string material = object.get("material", "").asString();
            if (!material.empty()){
                //check if material is loaded or default library
                if (!this->containsMaterial(material) && !contains(MaterialsLibrary::materials,material)) return false;
            }
            const Json::Value& transformation = object["transformation"];
            if (!validateTransformation(transformation)) return false;

            const Json::Value& texture = object["texture"];
            if (!validateTextures(texture)) return false;
            //all oké
            return true;

        }
        else if (type == "box" || type == "cube") {
            // required fields

            // optional fields
            std::string material = object.get("material", "").asString();
            if (!material.empty()){
                //check if material is loaded
                if (!this->containsMaterial(material) && !contains(MaterialsLibrary::materials,material)) return false;
            }
            const Json::Value& transformation = object["transformation"];
            if (!validateTransformation(transformation)) return false;
            const Json::Value& texture = object["texture"];
            if (!validateTextures(texture)) return false;

            //all oké
            return true;

        }
        else if (type == "plane") {
            // required fields

            //optional fields
            std::string material = object.get("material", "").asString();
            if (!material.empty()){
                //check if material is loaded
                if (!this->containsMaterial(material) && !contains(MaterialsLibrary::materials,material)) return false;
            }
            const Json::Value& transformation = object["transformation"];
            if (!validateTransformation(transformation)) return false;
            const Json::Value& texture = object["texture"];
            if (!validateTextures(texture)) return false;

            //all oké
            return true;

        }
        else if (type == "taperedcylinder") {
            // required fields

            //optional fields
            double s = object.get("s",1.0).asDouble();
            std::string material = object.get("material", "").asString();
            if (!material.empty()){
                //check if material is loaded
                if (!this->containsMaterial(material) && !contains(MaterialsLibrary::materials,material)) return false;
            }
            const Json::Value& transformation = object["transformation"];
            if (!validateTransformation(transformation)) return false;
            const Json::Value& texture = object["texture"];
            if (!validateTextures(texture)) return false;

            //all oké
            return true;

        }
        else if (type == "booleandifference") {
            // required fields
            std::string left = object.get("left","").asString();
            std::string right = object.get("right","").asString();
            if (left.empty()) return false;
            if (right.empty()) return false;
            if (!this->containsObject(left)) return false;
            if (!this->containsObject(right)) return false;

            //optional fields
            std::string material = object.get("material", "").asString();
            if (!material.empty()){
                //check if material is loaded
                if (!this->containsMaterial(material) && !contains(MaterialsLibrary::materials,material)) return false;
            }
            const Json::Value& transformation = object["transformation"];
            if (!validateTransformation(transformation)) return false;

            //all oké
            return true;

        }
        else if (type == "booleanintersection") {
            // required fields
            std::string left = object.get("left","").asString();
            std::string right = object.get("right","").asString();
            if (left.empty()) return false;
            if (right.empty()) return false;
            if (!this->containsObject(left)) return false;
            if (!this->containsObject(right)) return false;

            //optional fields
            std::string material = object.get("material", "").asString();
            if (!material.empty()){
                //check if material is loaded
                if (!this->containsMaterial(material) && !contains(MaterialsLibrary::materials,material)) return false;
            }
            const Json::Value& transformation = object["transformation"];
            if (!validateTransformation(transformation)) return false;

            //all oké
            return true;

        }
        else if (type == "booleanunion") {
            // required fields
            std::string left = object.get("left","").asString();
            std::string right = object.get("right","").asString();
            if (left.empty()) return false;
            if (right.empty()) return false;
            if (!this->containsObject(left)) return false;
            if (!this->containsObject(right)) return false;

            //optional fields
            std::string material = object.get("material", "").asString();
            if (!material.empty()){
                //check if material is loaded
                if (!this->containsMaterial(material) && !contains(MaterialsLibrary::materials,material)) return false;
            }
            const Json::Value& transformation = object["transformation"];
            if (!validateTransformation(transformation)) return false;

            //all oké
            return true;
        }
    }
    catch(...){}
    return false;
}

void SDLParser::validateLights() {
    int count = 0;
    size_t total = this->loadedLights.size();
    for (auto it = this->loadedLights.cbegin(), next_it = it; it != this->loadedLights.cend(); it = next_it){
        count++;
        std::cout << "\rValidating lights..." << count << "/" << total;
        ++next_it;
        std::string_view key = (*it).first;
        const Json::Value& light = (*it).second;
        if (!SDLParser::validateLight(light)){
            std::cout << "\n";
            Logger::warning("Lights " + std::string(key) + " is not valid");
            this->loadedLights.erase(it);
        }
    }
    if (total > 0) std::cout << "\rValidating lights...Done\t\t\t\t\t\t" << std::endl;
    this->statistics.validLights = count;
}
bool SDLParser::validateLight(const Json::Value &light) noexcept{
    try{
        std::string type = getType(light);
        if (type.empty()) return false; //no valid type
        if (type == "pointlight"){
            //required

            //optional
            const Json::Value& position = light["position"];
            if (!position.isNull() && !position.isArray()) return false; //position must be an array if it exists!

            //all oké
            return true;
        }
    }catch(...){};
    return false;
}

#pragma endregion



#pragma region scene constructor
void applyTransformation(Object* object, const Json::Value& transform){
    if (transform.isNull()) return; //don't transform object when not needed;
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
}
Vec4 getPosition(const Json::Value& position){
    Vec4 pos;
    if (position.isNull()) return pos; //return default position;

    if (!position.isNull() && position.isArray()){
        double px = position.get(Json::ArrayIndex(0),1.0).asDouble();
        double py = position.get(Json::ArrayIndex(1),1.0).asDouble();
        double pz = position.get(Json::ArrayIndex(2),1.0).asDouble();
        pos = Vec4(px, py, pz, 1);
    }
    return pos;
}

void SDLParser::sceneConstructor(const Json::Value& sceneDescription) {
    //2 possibilities to define a scene, all objects are already defined!
    //todo: finish other types of scene descriptions!!!!
    if (sceneDescription.isArray()){
        //just defined the object identifier
        for (auto& member: sceneDescription){
            //just defined the object identifier
            if (member.isString()){
                construct(member.asString());
            }
        }
    }
    else{
        auto keys = sceneDescription.getMemberNames();
        for (auto key = keys.begin(); key != keys.end(); key++) {

        }
    }

    //collect the scene objects from imported files (they might or might not exist
    for (auto& pair:this->importedFiles){
        auto& imported = pair.second;
        if (imported.hasScene){
            for(auto obj: imported.getObjects()){
                this->sceneObjects.push_back(obj);
            }
            for (auto obj: imported.getLights()){
                this->sceneLights.push_back(obj);
            }
        }

    }

    //compute bounding boxes
    for (auto& obj: this->sceneObjects){
        obj->computeBoundingBox();
    }
}
void SDLParser::construct(const std::string &identifier) {
    Logger::info("Not specifying the object type might cause naming collisions between materials, lights and objects.");
    if (this->containsObject(identifier)){
        this->sceneObjects.push_back(this->constructObject(identifier));
    }
    else if (this->containsLight(identifier)){
        this->sceneLights.push_back(this->constructLight(identifier));
    }
}

Object* SDLParser::constructObject(const std::string& identifier){
    std::string file;
    std::string key;
    splitIdentifier(identifier, file, key);
    if (file.empty()){
        //this sdl file contains the object description => build it!
        if (!contains(loadedObjects, key)) throw std::invalid_argument(key + " is not found in loaded objects");
        return this->buildObject(loadedObjects[key]); //finally, after all the validation and checking we can create the actual object!
    }else{
        for (auto& pair:this->importedFiles){
            auto& imported = pair.second;
            if (imported.containsObject(identifier)) return imported.constructObject(identifier);
        }
    }
    //dammit, getting here means this identifier wasn't loaded but this should be caught in validation????
    throw std::invalid_argument(key + " is not found in loaded lights");
}
Light* SDLParser::constructLight(const std::string& identifier){
    std::string file;
    std::string key;
    splitIdentifier(identifier, file, key);
    if (file.empty()){
        //this sdl file contains the object description => build it!
        if (!contains(loadedLights, key)) throw std::invalid_argument(key + " is not found in loaded lights");
        return this->buildLight(loadedLights[key]); //finally, after all the validation and checking we can create the actual light!
    }else{
        for (auto& pair:this->importedFiles){
            auto& imported = pair.second;
            if (imported.containsObject(identifier)) return imported.buildLight(identifier);
        }
    }
    //dammit, getting here means this identifier wasn't loaded but this should be caught in validation????
    throw std::invalid_argument(key + " is not found in loaded lights");
}
Material SDLParser::constructMaterial(const std::string& material){
    //first look in loaded objects, they might override default library
    if (material.empty()) return Material(); //default value!
    if (contains(this->loadedMaterials,material)){
        return buildMaterial(this->loadedMaterials[material]);
    }
    for (auto& pair:this->importedFiles){
        auto& imported = pair.second;
        if (imported.containsMaterial(material)) return imported.constructMaterial(material);
    }
    //look in default library:
    if (contains(MaterialsLibrary::materials,material)){
        return MaterialsLibrary::materials.at(material);
    }
    //dammit, getting here means this material wasn't loaded but this should be caught in validation????
    throw std::invalid_argument(material + " is not found in loaded lights");
}


Object* SDLParser::buildObject(const Json::Value& config){
    //std::cout << "building object\n";
    //std::cout << config << std::endl;

    std::string type = getType(config);
    if (type.empty()) throw std::invalid_argument(type + " is an unknown object specifier"); // no valid type, should never happen due to all the previous checks
    if (type == "sphere"){
        Object* object = new Sphere();

        const std::string material = config.get("material","").asString();
        object->setMaterial(constructMaterial(material));

        const Json::Value& transform = config["transformation"];
        applyTransformation(object, transform);

        const std::string texture = config.get("texture","").asString();
        object->setTexture(constructTexture(texture));
        return object;
    }
    else if (type == "box" || type == "cube"){
        Object* object = new Box();

        const std::string material = config.get("material","").asString();
        object->setMaterial(constructMaterial(material));

        const Json::Value& transform = config["transformation"];
        applyTransformation(object, transform);

        const std::string texture = config.get("texture","").asString();
        object->setTexture(constructTexture(texture));
        return object;
    }
    else if (type == "plane"){
        Object* object = new Plane();

        const std::string material = config.get("material","").asString();
        object->setMaterial(constructMaterial(material));

        const Json::Value& transform = config["transformation"];
        applyTransformation(object, transform);

        const std::string texture = config.get("texture","").asString();
        object->setTexture(constructTexture(texture));
        return object;
    }
    else if (type == "taperedcylinder"){
        double s = config.get("s",1.0).asDouble();
        Object* object = new TaperedCylinder(s);

        const std::string material = config.get("material","").asString();
        object->setMaterial(constructMaterial(material));

        const Json::Value& transform = config["transformation"];
        applyTransformation(object, transform);

        const std::string texture = config.get("texture","").asString();
        object->setTexture(constructTexture(texture));
        return object;
    }
    else if (type == "booleandifference"){
        Object* left = this->constructObject(config.get("left","").asString());
        Object* right = this->constructObject(config.get("right","").asString());
        Object* object = new BooleanDifference(left, right);

        //can override material
        const std::string material = config.get("material","").asString();
        object->setMaterial(constructMaterial(material));

        //can apply additional transform
        const Json::Value& transform = config["transformation"];
        applyTransformation(object, transform);

        return object;
    }
    else if (type == "booleanintersection"){
        Object* left = this->constructObject(config.get("left","").asString());
        Object* right = this->constructObject(config.get("right","").asString());
        Object* object = new BooleanIntersection(left, right);

        //can override material
        const std::string material = config.get("material","").asString();
        object->setMaterial(constructMaterial(material));

        //can apply additional transform
        return object;
    }
    else if (type == "booleanunion"){
        Object* left = this->constructObject(config.get("left","").asString());
        Object* right = this->constructObject(config.get("right","").asString());
        Object* object = new BooleanUnion(left, right);

        //can override material
        const std::string material = config.get("material","").asString();
        object->setMaterial(constructMaterial(material));

        //can apply additional transform
        return object;
    }
    return nullptr;
}
Light* SDLParser::buildLight(const Json::Value& config){
    //std::cout << "building light\n";
    //std::cout << config << std::endl;
    std::string type = getType(config);
    if (type.empty()) throw std::invalid_argument(type + " is an unknown light specifier"); // no valid type, should never happen due to all the previous checks
    if (type == "pointlight") {
        Light* light = new PointLight();

        Vec4 pos = getPosition(config["position"]);
        light->setPosition(pos);
        return light;
    }
    return nullptr;
}


Material SDLParser::buildMaterial(const Json::Value& config){
    //todo: implement custom material
    return Material();
}


Texture* SDLParser::constructTexture(const std::string& texture){
    //note=> texture must already be loaded!

    //for now no custom textures allowed
    return buildTexture(texture);

    //todo:check if imported files contain custom textures???



}
Texture* SDLParser::buildTexture(const Json::Value& texture){
    //todo: custom texture?
    return nullptr;
}
Texture* SDLParser::buildTexture(const Json::String& texture){
    //todo: custom texture?

    if (texture == "checkboard"){
        return new Checkboard(5,5,5);
    }else if (texture =="water" || texture =="waterTexture"){
        return new WaterTexture(0.1,0.1);
    }
    return nullptr;
}

#pragma endregion


/*
void MRay::SDLParser::objectParser(Json::Value objects) {
    auto objIds = objects.getMemberNames();
    std::cout << "Parsing " << objIds.size() << " objects\n";

    for (auto objId = objIds.begin(); objId != objIds.end(); objId++){
        std::cout << "Parsing:" << *objId << " " << objId-objIds.begin() << "/" << objIds.size() << "...";

        Json::Value obj = objects[*objId];
        if (obj["type"].isNull()){
            std::cout << "\nObject at index " << objId-objIds.begin() << "has no type specified\n";
        }
        std::string type = obj["type"].asString();
        Object* object = objectCreator(type, obj);
        if (object != nullptr) this->loadedObjects[*objId] = object;

        if (object != nullptr) std::cout << "done\n";
        else                   std::cout << "failed\n";
    }
}

void MRay::SDLParser::lightParser(Json::Value lights) {
    auto lightIds = lights.getMemberNames();
    for (auto lightId = lightIds.begin(); lightId != lightIds.end(); lightId++){
        Json::Value l = lights[*lightId];
        if (l["type"].isNull()){
            std::cout << "\nLight at index " << lightId-lightIds.begin() << "has no type specified\n";
        }
        std::string type = l["type"].asString();
        Light* light = lightCreator(type, l);
        if (light != nullptr) this->loadedLights[*lightId] = light;
    }
}

void MRay::SDLParser::materialParser(Json::Value materials) {

}
*/
/*
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
*/
void SDLParser::Statistics::reset() {
    this->loadedMaterials = 0;
    this->loadedObjects = 0;
    this->loadedLights = 0;

    this->validMaterials = 0;
    this->validObjects = 0;
    this->validLights = 0;

    this->sceneObjects = 0;
    this->sceneLights = 0;
    this->importedFiles = 0;
}

void SDLParser::Statistics::add(Statistics& stats) {
    this->loadedMaterials +=stats.loadedMaterials;
    this->loadedObjects +=stats.loadedObjects;
    this->loadedLights +=stats.loadedLights;
    this->validMaterials +=stats.validMaterials;
    this->validObjects +=stats.validObjects;
    this->validLights +=stats.validLights;
    this->sceneObjects +=stats.sceneObjects;
    this->sceneLights +=stats.sceneLights;
    this->importedFiles +=stats.importedFiles;
}

void SDLParser::printStatistics() {
    Statistics combinedStats = Statistics();
    for (auto& pair:this->importedFiles){
        auto& imported = pair.second;
         combinedStats.add(imported.statistics);
    }
    combinedStats.add(this->statistics);

    std::cout << "Load statistics:\n";
    std::cout << "Loaded elements:\n";
    std::cout << "\tMaterials:\t" << combinedStats.validMaterials << "\n";
    std::cout << "\tObjects  :\t" << combinedStats.validObjects << "\n";
    std::cout << "\tLights   :\t" << combinedStats.validLights << "\n";
    std::cout << "Rejected elements:\n";
    std::cout << "\tMaterials:\t" << (combinedStats.loadedMaterials - combinedStats.validMaterials) << "\n";
    std::cout << "\tObjects  :\t" << (combinedStats.loadedObjects - combinedStats.validObjects) << "\n";
    std::cout << "\tLights   :\t" << (combinedStats.loadedLights - combinedStats.validLights) << "\n";

    std::cout << "Total unique scene elements:\n";
    std::cout << "\tObjects  :\t" << this->sceneObjects.size() << "\n";
    std::cout << "\tLights   :\t" << this->sceneLights.size() << "\n";
    std::cout.flush();
}


