//
// Created by Maarten Van Loo on 15/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_LIVESCREEN_H
#define I_COMPUTERGRAPHICS_LIVESCREEN_H



#include <opencv2/opencv.hpp>
#include <Light/Color3.h>
#include <Camera/CameraUtils.h>
#include "LinearAlgebra/Vector.h"
#include <thread>
#include <chrono>
#include <atomic>
#include <opencv2/highgui/highgui_c.h>
#include <Render/RenderEngine.h>
#include <Utils/Options.h>
namespace MRay {

    class LiveScreen {
        enum Mode{
            strafe,
            roll
        };
    public:
        LiveScreen() = default;

        LiveScreen(Scene *scene, Camera *camera);

        void show();

        void hide();

        void waitClose();

        virtual ~LiveScreen();


        void showImage(const std::string& winname, const cv::Mat &image);
        bool guiExists(const std::string &winname);
        void move(int key);
        static cv::Mat resizeKeepAspectRatio(const cv::Mat &input, const cv::Size &dstSize, const cv::Scalar &bgcolor);

    private:
        //resources to redraw screen
        Scene *scene = nullptr;
        Camera *camera = nullptr;
        Options options = Options();

        Mode mode = Mode::strafe;
        Resolution currentRes = Resolution(Screensize::_720p);

        Image *image = nullptr;
        std::thread *gui = nullptr;
        std::atomic<bool> gui_running = false;
        long long lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now().time_since_epoch()).count();

        void loop();
        void renderFast();
        void renderSlow();

        cv::Mat detailImage;

        static void onMouse(int event, int x, int y, int flags, void *param);

        static void onMouseCrop(int event, int x, int y, int flags, void *param);
    };

}


#endif //I_COMPUTERGRAPHICS_LIVESCREEN_H
