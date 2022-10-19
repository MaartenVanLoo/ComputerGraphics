//
// Created by maart on 19/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_SDLPARSER_H
#define I_COMPUTERGRAPHICS_SDLPARSER_H
#include <Materials/Material.h>
#include <Materials/MaterialsLibrary.h>
#include <Objects/ObjectCore.h>
#include <Light/LightCore.h>
#include <unordered_map>
#include <string>

#include "Scene.h"
#include <json/json.h>

namespace MRay {
    class SDLParser {
    public:
        SDLParser(){};

        void parse(const std::string& sdlFile);
        std::vector<Object*> getObjects();
        std::vector<Light*> getLights();
    protected:
        std::unordered_map <std::string, Material> customMaterials;
        std::unordered_map<std::string, Object *> loadedObjects;
        std::unordered_map<std::string, Light *> loadedLights;

        void objectParser(Json::Value objects);
        void lightParser(Json::Value lights);
        void materialParser(Json::Value material);

        Object* objectCreator(std::string& type, Json::Value config);
        Light* lightCreator(std::string& type, Json::Value config);

        Material getMaterial(const std::string& materials);
        Texture* getTexture(const std::string& texture, Json::Value config);
        Object* transformObject(Object* object, Json::Value transform);


    };
}


#endif //I_COMPUTERGRAPHICS_SDLPARSER_H
