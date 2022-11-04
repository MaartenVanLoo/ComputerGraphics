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
        struct Statistics{
            void reset();
            void add(Statistics& stats);
            int loadedMaterials = 0;
            int loadedObjects = 0;
            int loadedLights = 0;
            int loadedTextures = 0;

            int validMaterials = 0;
            int validObjects = 0;
            int validLights = 0;
            int validTextures = 0;

            int sceneObjects = 0;
            int sceneLights = 0;
            int importedFiles = 0;
        };
    public:
        SDLParser(){};

        void parse(const std::string& sdlFile);
        std::vector<Object*> getObjects();
        std::vector<Light*> getLights();
    protected:
        void parse(const std::string& sdlFile, bool topLevel);
        void importFiles(const Json::Value& import);

        std::unordered_map<std::string, SDLParser> importedFiles;
        std::unordered_map<std::string, Json::Value> loadedMaterials;
        std::unordered_map<std::string, Json::Value> loadedObjects;
        std::unordered_map<std::string, Json::Value> loadedLights;
        std::unordered_map<std::string, Json::Value> loadedTextures;

        std::vector<Object*> sceneObjects;
        std::vector<Light*> sceneLights;
        bool hasScene = false;


        void loadMaterials(Json::Value& materials);
        void loadTextures(Json::Value& materials);
        void loadObjects(Json::Value& objects);
        void loadLights(Json::Value& lights);

        void validateMaterials();
        bool validateMaterial(const Json::Value& material) noexcept ;
        void validateObjects();
        bool validateObject(const Json::Value& material) noexcept;
        void validateLights();
        bool validateLight(const Json::Value& material) noexcept;
        void validateTextures();
        bool validateTexture(const Json::Value& material) noexcept;

        void sceneConstructor(const Json::Value& sceneDescription);
        void construct(const std::string& identifier);
        Object* constructObject(const std::string& identifier);
        Light* constructLight(const std::string& identifier);
        Material constructMaterial(const std::string& material);
        Texture* constructTexture(const std::string& texture);

        Object* buildObject(const Json::Value& config);
        Light* buildLight(const Json::Value& config);
        Material buildMaterial(const Json::Value& config);
        Texture* buildTexture(const Json::Value& texture);
        Texture* buildDefaultTexture(const std::string& texture);

        //functions to check if it contains a certain key in this file or its imports
        bool containsImport(const std::string &key) const;
        bool containsObject(const std::string &key) const;
        bool containsLight(const std::string &key) const;
        bool containsMaterial(const std::string & key) const;
        bool containsTexture(const std::string & key) const;

        Statistics statistics;
        void printStatistics();
        //std::unordered_map <std::string, Material> customMaterials;
        //std::unordered_map<std::string, Object *> loadedObjects;
        //std::unordered_map<std::string, Light *> loadedLights;
/*
        void objectParser(Json::Value objects);
        void lightParser(Json::Value lights);
        void materialParser(Json::Value material);

        Object* objectCreator(std::string& type, Json::Value config);
        Light* lightCreator(std::string& type, Json::Value config);

        Material getMaterial(const std::string& materials);
        Texture* getTexture(const std::string& texture, Json::Value config);
        Object* transformObject(Object* object, Json::Value transform);
*/

    };
}


#endif //I_COMPUTERGRAPHICS_SDLPARSER_H
