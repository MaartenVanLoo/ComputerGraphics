//
// Created by maart on 30/09/2022.
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

#define workerjobs 12 //minimum number of jobs for a worker
#define artificaldelay false

namespace MRay {

    class RenderTask;

    class Scene {
    public:
        Scene();

        virtual ~Scene();

        void addObject(Object *obj);

        void addLight(Light *light);

        void setCamera(Camera &camera);

        void clearLights();

        [[nodiscard]] const std::vector<Object *> &getObjects() const;

        [[nodiscard]] const std::vector<Light *> &getLights() const;

        [[nodiscard]] Camera &getCamera();

        friend std::ostream &operator<<(std::ostream &os, const Scene &scene);

        void Render(const Options &options);

        Color3 shade(int x, int y);

        void load(std::string &file);
    private:
        bool getFirstHit(Ray &ray, Hit &best, Intersection &intersect, const Object *ignore = nullptr) const;

        bool isInShadow(const Vec4 &point, const Object *ignore, const Light *light, Intersection &intersect) const;

        void createTasks(std::vector<RenderTask *> &tasks);

        Camera camera;
        std::vector<Light *> lights;
        std::vector<Object *> objects;

        //Shader* shader;

        //GUI
        Image *image = nullptr;
        Screen *screen = nullptr;

        std::ofstream outfile;


        friend RenderTask;
    };


    class RenderTask : public Task<void> {
    public:
        RenderTask(Scene *scene, Image *image, int x_min, int x_max, int y_min, int y_max) : scene(scene), image(image),
                                                                                             x_min(x_min),
                                                                                             x_max(x_max), y_min(y_min),
                                                                                             y_max(y_max) {}

        void run() override {
            const Resolution resolution = scene->camera.getResolution();
            Color3 taskColor = Color3(rand() % 255, rand() % 255, rand() % 255);
            x_max = std::min(x_max, resolution.width);
            y_max = std::min(y_max, resolution.height);
            for (int y = y_min; y < y_max; y++) {
                for (int x = x_min; x < x_max; x++) {
                    Color3 rgb = this->scene->shade(x, y);
                    this->image->setPixel(x, y, rgb);
                }
#if artificaldelay
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(5ms);
#endif
            }
            finished = true;
        }

        bool done() {
            return finished;
        }

    private:
        volatile bool finished = false;
        Scene *scene;
        Image *image;
        int x_min, x_max, y_min, y_max;
    };
}
#endif //I_COMPUTERGRAPHICS_SCENE_H
