//
// Created by Maarten Van Loo on 1/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_SCREEN_H
#define I_COMPUTERGRAPHICS_SCREEN_H

#include <opencv2/opencv.hpp>
#include "../Camera/CameraUtils.h"
#include "../Vector.h"
#include <thread>
#include <chrono>
enum keycodes{
    esc = 27,
    f = 102
};

class Image{
public:
    Image(Resolution resolution);
    cv::Mat getImageBuffer();
    void setPixel(int x, int y, RGB rgb);
    RGB getPixel(int x, int y);

    long long getLastUpdate();
private:
    cv::Mat imageBuffer;
    long long lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
};

class Screen {
public:
    Screen(Image &image);

    void show();
    void hide();
    void waitClose();
    virtual ~Screen();

private:
    Image* image = nullptr;
    std::thread gui;
    std::atomic<bool> gui_running = false;
    long long lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    void loop();
    static void onMouse(int event,int x,int y,int flags,void *param);
};




#endif //I_COMPUTERGRAPHICS_SCREEN_H
