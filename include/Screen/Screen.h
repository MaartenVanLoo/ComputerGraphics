//
// Created by Maarten Van Loo on 1/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_SCREEN_H
#define I_COMPUTERGRAPHICS_SCREEN_H

#include <opencv2/opencv.hpp>
#include <Utils/Color3.h>
#include <Camera/CameraUtils.h>
#include "LinearAlgebra/Vector.h"
#include <thread>
#include <chrono>
#include <atomic>
#include <opencv2/highgui/highgui_c.h>
enum keycodes{
    esc = 27,
    f = 102,
    s = 115
};

class Image{
public:
    Image();
    Image(Resolution resolution);

    const cv::Mat &getImageBuffer() const;

    void setPixel(int x, int y, Color3 rgb);
    Color3 getPixel(int x, int y);

    long long getLastUpdate();

    void update();
    void save(std::string filename);
private:
    cv::Mat imageBuffer;
    std::atomic<long long> lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
};

class Screen {
public:
    Screen()= default;;
    Screen(Image &image);

    void show();
    void hide();
    void waitClose();
    virtual ~Screen();

private:
    Image* image = nullptr;
    std::thread* gui = nullptr;
    std::atomic<bool> gui_running= false;
    long long lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

    void loop();

    cv::Mat detailImage;

    static void onMouse(int event,int x,int y,int flags,void *param);
    static void onMouseCrop(int event,int x,int y,int flags,void *param);
};




#endif //I_COMPUTERGRAPHICS_SCREEN_H
