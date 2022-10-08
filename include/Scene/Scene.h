//
// Created by maart on 30/09/2022.
//

#ifndef I_COMPUTERGRAPHICS_SCENE_H
#define I_COMPUTERGRAPHICS_SCENE_H


#include <vector>
#include <ostream>
#include <Camera/Camera.h>
#include <Light/Light.h>
#include <Screen/Screen.h>
#include <Utils/Options.h>
#include "../Objects/Object.h"
#include <Utils/ThreadPool.h>
#include <Utils/Stopwatch.h>

#define workerjobs 12 //minimum number of jobs for a worker
#define artificaldelay false

class RenderTask;

class Scene {
public:
    Scene();

    virtual ~Scene();

    void addObject(Object* obj);
    void addLight(Light* light);
    friend std::ostream &operator<<(std::ostream &os, const Scene &scene);

    void Render(const Options &options);

    Color3 shade(int x, int y);
private:
    void getFirstHit(Ray& ray, Hit& hit);
    void createTasks(std::vector<RenderTask*>& tasks);
    Camera camera;
    std::vector<Light*> lights;
    std::vector<Object*> objects;

    //GUI
    Image* image = nullptr;
    Screen* screen = nullptr;

    friend RenderTask;
};


class RenderTask : public Task<void>{
public:
    RenderTask(Scene *scene, Image* image, int x_min, int x_max, int y_min, int y_max) : scene(scene), image(image), x_min(x_min),
                                                                                         x_max(x_max), y_min(y_min), y_max(y_max) {}

    void run() override {
        const Resolution resolution = scene->camera.getResolution();
        Color3 taskColor = Color3(rand()%255,rand()%255,rand()%255);
        x_max = std::min(x_max,resolution.width);
        y_max = std::min(y_max, resolution.height);
        for (int y = y_min; y < y_max; y++){
            for (int x = x_min; x < x_max; x++){
                Color3 rgb = this->scene->shade(x, y);
                this->image->setPixel(x,y,rgb);
            }
#if artificaldelay
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(5ms);
#endif
        }
        finished = true;
    }
    bool done(){
        return finished;
    }
private:
    volatile bool finished = false;
    Scene* scene;
    Image* image;
    int x_min, x_max, y_min, y_max;
};
#endif //I_COMPUTERGRAPHICS_SCENE_H
