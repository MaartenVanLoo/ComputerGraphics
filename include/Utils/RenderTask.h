//
// Created by maart on 6/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_RENDERTASK_H
#define I_COMPUTERGRAPHICS_RENDERTASK_H
#include <Utils/ThreadPool.h>
#include <Scene/Scene.h>

class RenderTask : public Task<void>{
public:
    RenderTask(Scene *scene, Image* image, int x_min, int x_max, int y_min, int y_max) : scene(scene), image(image), x_min(x_min),
                                                                                         x_max(x_max), y_min(y_min), y_max(y_max) {}

    void run() override {
        for (int x = x_min; x < x_max; x++){
            for (int y = y_min; y < y_max; y++){
                RGB rgb = this->scene->computePixelColor(x,y);
                this->image->setPixel(x,y,rgb);
            }
        }
    }

private:
    Scene* scene;
    Image* image;
    int x_min, x_max, y_min, y_max;
};
#endif //I_COMPUTERGRAPHICS_RENDERTASK_H
