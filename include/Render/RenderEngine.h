//
// Created by Maarten Van Loo on 14/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_RENDERENGINE_H
#define I_COMPUTERGRAPHICS_RENDERENGINE_H

#include <Scene/Scene.h>
#include <Render/Shader.h>
#include <Render/PhongShader.h>
namespace MRay {
    class RenderEngine {
    public:
        RenderEngine(Scene *scene, Camera *camera, Options &options);

#pragma region Getters & Setters
        Scene *getScene() const;
        void setScene(Scene *scene);
        Camera *getCamera() const;
        void setCamera(Camera *camera);
        const Options &getOptions() const;
        void setOptions(const Options &options);
        Shader *getShader() const;
        void setShader(Shader *shader);
        Image* getImage();
#pragma endregion

        void render();

        void createTasks(std::vector<RenderTask *> &tasks);
    protected:
        Options options;

        Scene *scene = nullptr;
        Camera *camera = nullptr;

        Shader* shader = nullptr;

        //GUI
        Image *image = nullptr;
        Screen *screen = nullptr;

        friend RenderTask;
    };


    class RenderTask : public Task<void> {
    public:
        RenderTask(RenderEngine *engine, Image *image, int x_min, int x_max, int y_min, int y_max) : engine(engine), image(image),
                                                                                             x_min(x_min),
                                                                                             x_max(x_max), y_min(y_min),
                                                                                             y_max(y_max) {}

        void run() override {
            const Resolution resolution = this->engine->camera->getResolution();
            //Color3 taskColor = Color3(rand() % 255, rand() % 255, rand() % 255);
            x_max = std::min(x_max, resolution.width);
            y_max = std::min(y_max, resolution.height);
            for (int y = y_min; y < y_max; y++) {
                for (int x = x_min; x < x_max; x++) {
                    Color3 rgb = this->engine->shader->shade(x, y);
                    this->image->setPixel(x, y, rgb);
                }
#if artificaldelay
                using namespace std::chrono_literals;
                    std::this_thread::sleep_for(5ms);
#endif
            }
            finished = true;
        }

        bool done() const {
            return finished;
        }

    private:
        volatile bool finished = false;
        RenderEngine *engine;
        Image *image;
        int x_min, x_max, y_min, y_max;
    };
}
#endif //I_COMPUTERGRAPHICS_RENDERENGINE_H
