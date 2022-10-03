//
// Created by Maarten Van Loo on 1/10/2022.
//

#include "Screen/Screen.h"



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

Image::Image() {
    Resolution resolution = Resolution();
    this->imageBuffer = cv::Mat::zeros(cv::Size(resolution.width,resolution.height),CV_8UC3);
}
Image::Image(Resolution resolution) {
    this->imageBuffer = cv::Mat::zeros(cv::Size(resolution.width,resolution.height),CV_8UC3);
}

void Image::setPixel(int x, int y, RGB rgb) {
    cv::Vec3b & color = this->imageBuffer.at<cv::Vec3b>(y,x);
    color[0] = static_cast<unsigned char>(rgb.blue);
    color[1] = static_cast<unsigned char>(rgb.green);
    color[2] = static_cast<unsigned char>(rgb.red);

    this->lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

RGB Image::getPixel(int x, int y){
    cv::Vec3b & color = this->imageBuffer.at<cv::Vec3b>(y,x);
    return RGB(color[2], color[1], color[0]);
}

long long Image::getLastUpdate() {
    return this->lastUpdate;
}

void Image::update() {
    //forces last update time to make a draw call in the screen
    this->lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

const cv::Mat &Image::getImageBuffer() const {
    return this->imageBuffer;
}

Screen::Screen(Image &image) {
    this->image = &image;
}


void Screen::show() {
    gui_running = true,
    this->gui = new std::thread(&Screen::loop, this);
}

void Screen::hide(){
    gui_running = false;
    this->gui->join();
    free(this->gui);
    this->gui = nullptr;
}

void Screen::waitClose(){
    if (this->gui == nullptr) return;
    while (cv::getWindowProperty("Rendered Image",cv::WND_PROP_VISIBLE) == 1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


void Screen::onMouse(int event,int x,int y,int flags,void *param){
    if (((Screen*)(param))->lastUpdate + 100 > std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()){
        return; //only once every 100 ms;
    }
    cv::Rect renderArea =  cv::getWindowImageRect("Rendered Image");
    cv::imshow("Rendered Image", resizeKeepAspectRatio(((Screen*)(param))->image->getImageBuffer(), renderArea.size(),cv::Scalar(0,0,0)));
    ((Screen*)(param))->lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    cv::waitKey(1);
    //std::cout << "Mouse event " << flags << std::endl;
}

void Screen::onMouseCrop(int event,int x,int y,int flags,void *param){
    auto test = cvGetWindowHandle("Crop Image");
    if (cvGetWindowHandle("Crop Image") == 0) return; //window closed
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
    cv::Rect renderArea =  cv::getWindowImageRect(winname);
    cv::imshow(winname, resizeKeepAspectRatio(image, renderArea.size(),cv::Scalar(0,0,0)));
}
void Screen::loop() {
    cv::Rect2d rect;

    int key;
    cv::namedWindow("Rendered Image", cv::WINDOW_NORMAL);
    cv::setWindowProperty("Rendered Image", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

    cv::Rect renderArea =  cv::getWindowImageRect("Rendered Image");
    cv::imshow("Rendered Image", resizeKeepAspectRatio(this->image->getImageBuffer(), renderArea.size(),cv::Scalar(0,0,0)));
    cv::setMouseCallback("Rendered Image",&Screen::onMouse,this);


    while (gui_running && cv::getWindowProperty("Rendered Image",cv::WND_PROP_VISIBLE) == 1)
    {
        if (this->lastUpdate <= this->image->getLastUpdate()+100){ //only update if pixels have changed (allow a difference of 100 ms to not miss a draw call;
            showImage("Rendered Image",this->image->getImageBuffer());
            //cv::Rect renderArea =  cv::getWindowImageRect("Rendered Image");
            //cv::imshow("Rendered Image", resizeKeepAspectRatio(this->image->getImageBuffer(), renderArea.size(),cv::Scalar(0,0,0)));
            this->lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        }
        key = cv::waitKey(50); //20 fps
        //std::cout << key << std::endl;
        switch (key){
            case -1: break; //No key pressed
            case keycodes::esc:
                cv::setWindowProperty("Rendered Image", cv::WND_PROP_FULLSCREEN, cv::WINDOW_NORMAL);
                break;
            case keycodes::f:
                cv::setWindowProperty("Rendered Image", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
                break;
            case keycodes::s:
                rect = cv::selectROI("Rendered Image",this->image->getImageBuffer(),true);
                if (rect.empty()) break;
                this->detailImage = this->image->getImageBuffer()(rect);
                cv::namedWindow("Crop Image", cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
                cv::setMouseCallback("Crop Image",&Screen::onMouseCrop,this);
                cv::resizeWindow("Crop Image",1280 ,720);
                showImage("Crop Image",this->detailImage);
                break;
            default:
                std::cout << "key pressed:" << key << std::endl;

        }
    }
    cv::destroyAllWindows();
}


Screen::~Screen() {
    gui_running = false;
    if (this->gui != nullptr){
        this->gui->join();
        free(this->gui);
    }
}


