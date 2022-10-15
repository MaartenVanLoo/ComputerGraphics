//
// Created by Maarten Van Loo on 15/10/2022.
//

#include <Screen/LiveScreen.h>


using namespace MRay;
cv::Mat MRay::LiveScreen::resizeKeepAspectRatio(const cv::Mat &input, const cv::Size &dstSize, const cv::Scalar &bgcolor)
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


MRay::LiveScreen::LiveScreen(Scene *scene, Camera *camera) {
    this->scene = scene;
    this->camera = camera;
}


void MRay::LiveScreen::show() {
    this->options.enableGui = false;
    this->options.multicore = true;

    this->renderFast();

    gui_running = true,
            this->gui = new std::thread(&MRay::LiveScreen::loop, this);
}

void MRay::LiveScreen::hide(){
    gui_running = false;
    this->gui->join();
    free(this->gui);
    this->gui = nullptr;
}

void MRay::LiveScreen::waitClose(){
    if (this->gui == nullptr) return;

    while (cv::getWindowProperty("Rendered Image",cv::WND_PROP_VISIBLE) == 1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


void MRay::LiveScreen::onMouse(int event,int x,int y,int flags,void *param){
    if (((LiveScreen*)(param))->lastUpdate + 100 > std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()){
        return; //only once every 100 ms;
    }
    cv::Rect renderArea =  cv::getWindowImageRect("Rendered Image");
    cv::imshow("Rendered Image", resizeKeepAspectRatio(((LiveScreen*)(param))->image->getImageBuffer(), renderArea.size(),cv::Scalar(0,0,0)));
    ((LiveScreen*)(param))->lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    cv::waitKey(1);
    std::cout << "Mouse event " << flags << std::endl;
}

void MRay::LiveScreen::onMouseCrop(int event,int x,int y,int flags,void *param){
    try{
        if(cvGetWindowHandle("Crop Image") == nullptr) return; //window closed
    }catch(const std::exception&){
        return; //window doesn't exist?
    }
    if (((LiveScreen*)(param))->lastUpdate + 100 > std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()){
        return; //only once every 100 ms;
    }
    cv::Rect renderArea =  cv::getWindowImageRect("Crop Image");
    cv::imshow("Crop Image", resizeKeepAspectRatio(((LiveScreen*)(param))->detailImage, renderArea.size(),cv::Scalar(0,0,0)));
    ((LiveScreen*)(param))->lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    cv::waitKey(1);
    //std::cout << "Mouse event " << flags << std::endl;
}


void MRay::LiveScreen::showImage(const std::string& winname, const cv::Mat &image){
    if (cv::getWindowProperty("Rendered Image",cv::WND_PROP_VISIBLE) ==0) return; //image not visible
    cv::Rect renderArea =  cv::getWindowImageRect(winname);
    cv::imshow(winname, resizeKeepAspectRatio(image, renderArea.size(),cv::Scalar(0,0,0)));
}
bool MRay::LiveScreen::guiExists(const std::string &winname){
    try{
        return cv::getWindowProperty("Rendered Image",cv::WND_PROP_ASPECT_RATIO) > 0; //aspect_ratio = -1 when minimized
    }
    catch(const std::exception&){
        return false;
    }
}
void MRay::LiveScreen::loop() {
    cv::Rect2d rect;
    cv::Rect renderArea;
    cv::Mat tmp;
    int key;

    cv::namedWindow("Rendered Image", cv::WINDOW_NORMAL);
    cv::setWindowProperty("Rendered Image", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

    showImage("Rendered Image", this->image->getImageBuffer());
    cv::setMouseCallback("Rendered Image",&MRay::LiveScreen::onMouse,this);


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
            case keycodes::z:
                this->camera->setFocalLength(this->camera->getFocalLength()*1.1); //TODO: move forwards
                std::cout << *this->camera << std::endl;
                this->renderFast();
                showImage("Rendered Image", this->image->getImageBuffer());
                cv::waitKey(1); //force screen update
                break;
            case keycodes::s:
                this->camera->setFocalLength(this->camera->getFocalLength()/1.1); //TODO: move backwards
                std::cout << *this->camera << std::endl;
                this->renderFast();
                showImage("Rendered Image", this->image->getImageBuffer());
                cv::waitKey(1); //force screen update
                break;
            case keycodes::_plus:
                this->camera->setFocalLength(this->camera->getFocalLength()*1.1); //zoom in
                std::cout << *this->camera << std::endl;
                this->renderFast();
                showImage("Rendered Image", this->image->getImageBuffer());
                cv::waitKey(1); //force screen update
                break;
            case keycodes::_minus:
                this->camera->setFocalLength(this->camera->getFocalLength()/1.1); //zoom out
                std::cout << *this->camera << std::endl;
                this->renderFast();
                showImage("Rendered Image", this->image->getImageBuffer());
                cv::waitKey(1);//force screen update
                break;
            case keycodes::d:
                this->camera->rotate(0,0,0.0872665); //rotate cw 5 degrees
                std::cout << *this->camera << std::endl;
                this->renderFast();
                showImage("Rendered Image", this->image->getImageBuffer());
                cv::waitKey(1);//force screen update
                break;
            case keycodes::q:
                this->camera->rotate(0,0,-0.0872665); //rotate ccw 5 degrees
                std::cout << *this->camera << std::endl;
                this->renderFast();
                showImage("Rendered Image", this->image->getImageBuffer());
                cv::waitKey(1);//force screen update
                break;
            case keycodes::e:
                this->camera->translate(0,0,0.5); //move up
                std::cout << *this->camera << std::endl;
                this->renderFast();
                showImage("Rendered Image", this->image->getImageBuffer());
                cv::waitKey(1); //force screen update
                break;
            case keycodes::a:
                this->camera->translate(0,0,-0.5); //move down
                std::cout << *this->camera << std::endl;
                this->renderFast();
                showImage("Rendered Image", this->image->getImageBuffer());
                cv::waitKey(1); //force screen update
                break;
            case keycodes::space:
                this->renderSlow();
                showImage("Rendered Image", this->image->getImageBuffer());
                cv::waitKey(1); //force screen update
                break;
            default:
                std::cout << "key pressed:" << key << std::endl;

        }
    }
    cv::destroyAllWindows();
}


MRay::LiveScreen::~LiveScreen() {
    gui_running = false;
    if (this->gui != nullptr){
        this->gui->join();
        delete this->gui;
    }
    if (this->scene != nullptr){
        delete this->scene;
    }
    if (this->image != nullptr){
        delete this->image;
    }
}

void LiveScreen::renderFast() {
    this->camera->setResolution(Resolution(Screensize::_1080p));
    RenderEngine engine = RenderEngine(scene,camera,options);
    engine.render();

    delete this->image;
    this->image = new Image(*engine.getImage());

}


void LiveScreen::renderSlow() {
    this->camera->setResolution(Resolution(Screensize::_4K));
    RenderEngine engine = RenderEngine(scene,camera,options);
    engine.render();

    delete this->image;
    this->image = new Image(*engine.getImage());

}
