//
// Created by Maarten Van Loo on 1/10/2022.
//

#include "Screen/Screen.h"


using namespace MRay;
cv::Mat resizeKeepAspectRatio(const cv::Mat &input, const cv::Size &dstSize, const cv::Scalar &bgcolor)
{
    cv::Mat output;

    // initially no borders
    int top = 0;
    int down = 0;
    int left = 0;
    int right = 0;
    double h1 = dstSize.width * (input.rows/(double)input.cols);
    double w2 = dstSize.height * (input.cols/(double)input.rows);
    if( h1 <= dstSize.height)
    {
        // only vertical borders
        top = int((dstSize.height - h1) / 2);
        down = top;
        cv::resize( input, output, cv::Size(dstSize.width, int(h1)),0,0);
    }
    else
    {
        // only horizontal borders
        left = int((dstSize.width - w2) / 2);
        right = left;
        cv::resize( input, output, cv::Size(int(w2), dstSize.height),0,0);
    }
    cv::copyMakeBorder(output, output, top, down, left, right, cv::BORDER_CONSTANT, bgcolor );
    return output;
}

MRay::Image::Image() {
    Resolution resolution = Resolution();
    this->imageBuffer = cv::Mat::zeros(cv::Size(resolution.width,resolution.height),CV_8UC3);
}
MRay::Image::Image(Resolution resolution) {
    this->imageBuffer = cv::Mat::zeros(cv::Size(resolution.width,resolution.height),CV_8UC3);
}

void MRay::Image::setPixel(int x, int y, Color3 rgb) {
    cv::Vec3b & color = this->imageBuffer.at<cv::Vec3b>(y,x);
    color[0] = static_cast<unsigned char>(rgb.blue);
    color[1] = static_cast<unsigned char>(rgb.green);
    color[2] = static_cast<unsigned char>(rgb.red);

    this->lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

Color3 MRay::Image::getPixel(int x, int y){
    cv::Vec3b & color = this->imageBuffer.at<cv::Vec3b>(y,x);
    return Color3(color[2], color[1], color[0]);
}

long long MRay::Image::getLastUpdate() {
    return this->lastUpdate;
}

void MRay::Image::update() {
    //forces last update time to make a draw call in the screen
    this->lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

const cv::Mat &MRay::Image::getImageBuffer() const {
    return this->imageBuffer;
}
void Image::setImageBuffer(const cv::Mat &mat) {
    this->imageBuffer = mat;
}
void MRay::Image::save(const std::string &filename) {
    cv::imwrite(filename, this->imageBuffer);
}

Image::Image(Image &im) {
    this->imageBuffer = im.imageBuffer;
    this->lastUpdate = 0;
}




MRay::Screen::Screen(Image &image) {
    this->image = &image;
}


void MRay::Screen::show() {
    gui_running = true,
    this->gui = new std::thread(&MRay::Screen::loop, this);
}

void MRay::Screen::hide(){
    gui_running = false;
    this->gui->join();
    free(this->gui);
    this->gui = nullptr;
}

void MRay::Screen::waitClose(){
    if (this->gui == nullptr) return;
    while (cv::getWindowProperty("Rendered Image",cv::WND_PROP_VISIBLE) == 1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


void MRay::Screen::onMouse(int event,int x,int y,int flags,void *param){
    if (((Screen*)(param))->lastUpdate + 100 > std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()){
        return; //only once every 100 ms;
    }
    cv::Rect renderArea =  cv::getWindowImageRect("Rendered Image");
    cv::imshow("Rendered Image", resizeKeepAspectRatio(((Screen*)(param))->image->getImageBuffer(), renderArea.size(),cv::Scalar(0,0,0)));
    ((Screen*)(param))->lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    cv::waitKey(1);
    //std::cout << "Mouse event " << flags << std::endl;
}

void MRay::Screen::onMouseCrop(int event,int x,int y,int flags,void *param){
    try{
        if(cvGetWindowHandle("Crop Image") == nullptr) return; //window closed
    }catch(const std::exception&){
        return; //window doesn't exist?
    }
    if (((Screen*)(param))->lastUpdate + 100 > std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()){
        return; //only once every 100 ms;
    }
    cv::Rect renderArea =  cv::getWindowImageRect("Crop Image");
    cv::imshow("Crop Image", resizeKeepAspectRatio(((Screen*)(param))->detailImage, renderArea.size(),cv::Scalar(0,0,0)));
    ((Screen*)(param))->lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    cv::waitKey(1);
    //std::cout << "Mouse event " << flags << std::endl;
}


void showImage(const std::string& winname, const cv::Mat &image){
    if (cv::getWindowProperty("Rendered Image",cv::WND_PROP_VISIBLE) ==0) return; //image not visible
    cv::Rect renderArea =  cv::getWindowImageRect(winname);
    cv::imshow(winname, resizeKeepAspectRatio(image, renderArea.size(),cv::Scalar(0,0,0)));
}
bool guiExists(const std::string &winname){
    try{
        return cv::getWindowProperty("Rendered Image",cv::WND_PROP_ASPECT_RATIO) > 0; //aspect_ratio = -1 when minimized
    }
    catch(const std::exception&){
        return false;
    }
}
void MRay::Screen::loop() {
    cv::Rect2d rect;
    cv::Rect renderArea;
    cv::Mat tmp;
    int key;

    cv::namedWindow("Rendered Image", cv::WINDOW_NORMAL);
    cv::setWindowProperty("Rendered Image", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

    showImage("Rendered Image", this->image->getImageBuffer());
    cv::setMouseCallback("Rendered Image",&MRay::Screen::onMouse,this);


    while (gui_running &&
           guiExists("Rendered Image"))//cv::getWindowProperty("Rendered Image",cv::WND_PROP_VISIBLE) >= 1)
    {
        if (this->image == nullptr){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        //std::cout << cv::getWindowProperty("Rendered Image",cv::WND_PROP_VISIBLE) << std::endl;
        //std::cout << cv::getWindowProperty("Rendered Image",cv::WND_PROP_ASPECT_RATIO)  << std::endl;
        if (this->lastUpdate <= this->image->getLastUpdate() +
                                100) { //only update if pixels have changed (allow a difference of 100 ms to not miss a draw call;
            showImage("Rendered Image", this->image->getImageBuffer());
            //cv::Rect renderArea =  cv::getWindowImageRect("Rendered Image");
            //cv::imshow("Rendered Image", resizeKeepAspectRatio(this->image->getImageBuffer(), renderArea.size(),cv::Scalar(0,0,0)));
            this->lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now().time_since_epoch()).count();
        }
        key = cv::waitKey(50); //20 fps
        //std::cout << key << std::endl;
        switch (key) {
            case -1:
                break; //No key pressed
            case keycodes::esc:
                cv::setWindowProperty("Rendered Image", cv::WND_PROP_FULLSCREEN, cv::WINDOW_NORMAL);
                break;
            case keycodes::f:
                cv::setWindowProperty("Rendered Image", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
                break;
            case keycodes::c:
                renderArea =  cv::getWindowImageRect("Rendered Image");
                tmp = resizeKeepAspectRatio(this->image->getImageBuffer(), renderArea.size(),cv::Scalar(0,0,0));
                rect = cv::selectROI("Rendered Image", tmp, true);
                if (rect.empty()) break;
                this->detailImage = tmp(rect);
                cv::namedWindow("Crop Image", cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
                cv::resizeWindow("Crop Image", 1280, 720);
                showImage("Crop Image", this->detailImage);
                cv::setMouseCallback("Rendered Image",&MRay::Screen::onMouse,this);
                cv::setMouseCallback("Crop Image",&MRay::Screen::onMouseCrop,this);
                break;
            default:
                std::cout << "key pressed:" << key << std::endl;

        }
    }
    cv::destroyAllWindows();
}


MRay::Screen::~Screen() {
    gui_running = false;
    if (this->gui != nullptr){
        this->gui->join();
        free(this->gui);
    }
}


