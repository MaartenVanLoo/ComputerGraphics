//
// Created by Maarten Van Loo on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_SCENE_H
#define I_COMPUTERGRAPHICS_SCENE_H


#include <vector>
#include <ostream>
#include <Camera/Camera.h>
#include <Light/LightCore.h>
#include <Screen/Screen.h>
#include <Utils/Options.h>
#include "../Objects/Object.h"

#include <Utils/ThreadPool.h>
#include <Utils/Stopwatch.h>
#include <vector>
#include <Textures/Texture.h>
#include <fstream>
#include <iostream>
#include <json/json.h>

#define workerjobs 12 //minimum number of jobs for a worker
#define artificaldelay false

namespace MRay {

    class RenderTask;

    class Scene {
    public:
        Scene();

        virtual ~Scene();

        void addObject(Object *obj);
        void clearObjects();

        void addLight(Light *light);

        void clearLights();

        void hardReset();

        [[nodiscard]] const std::vector<Object *> &getObjects() const;

        [[nodiscard]] const std::vector<Light *> &getLights() const;

        friend std::ostream &operator<<(std::ostream &os, const Scene &scene);

        void load(const std::string& file);
    private:
        std::vector<Light *> lights;
        std::vector<Object *> objects;

        std::unordered_map<std::string, Material> parseMaterials(Json::Value& objects);
        std::unordered_map<std::string, Object*> parseObjects(Json::Value& objects,std::unordered_map<std::string, Material> &materials);
        std::unordered_map<std::string, Light*> parseLights(Json::Value& objects);

        friend RenderTask;
    };



}
#endif //I_COMPUTERGRAPHICS_SCENE_H
