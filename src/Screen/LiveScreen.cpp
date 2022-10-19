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
    this->options.renderName = "";

    this->currentRes = Resolution(Screensize::_720p);
    this->currentRes.width/=8;
    this->currentRes.height/=8;
    this->renderFast();

    gui_running = true;
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
    cv::Mat rImage = resizeKeepAspectRatio(((LiveScreen*)(param))->image->getImageBuffer(), renderArea.size(),cv::Scalar(0,0,0));
    std::string word;
    switch (((LiveScreen*)(param))->mode){
        case Mode::strafe:
            word = "Mode: strafe";
            break;
        case Mode::roll:
            word = "Mode: roll";
    }
    cv::putText(rImage, word, cv::Point(20, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 0, 0), 1);
    cv::imshow("Rendered Image", rImage );
    ((LiveScreen*)(param))->lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    cv::waitKey(1);
    //std::cout << "Mouse event " << flags << std::endl;
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
    cv::Mat rImage = resizeKeepAspectRatio(image, renderArea.size(),cv::Scalar(0,0,0));
    std::string word;
    switch (this->mode){
        case Mode::strafe:
            word = "Mode: strafe";
            break;
        case Mode::roll:
            word = "Mode: roll";
            break;
    }
    cv::putText(rImage, word, cv::Point(20, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 0, 0), 1);
    cv::imshow(winname, rImage );
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
    Vec4 dir;
    int key;
    bool pendingRender = true;
    int pendingFrames = 0;
    int maxPendingFrames = 5 ;

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
        key = cv::waitKey(100);
        switch (key) {
            case -1:
                if (pendingRender){
                    long long now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
                    if (pendingFrames == 0 && (now - this->lastUpdate) > 1000){ //no pending renders & last render was > 1sec ago, increase resolution
                        this->renderFast();
                        this->lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
                        if (this->currentRes.width > getWidth(Screensize::_1440p)) pendingRender = false;
                    }
                    else if (pendingFrames != 0){
                        //reset resolution
                        this->currentRes = Resolution(Screensize::_720p);
                        this->currentRes.width/=8;
                        this->currentRes.height/=8;
                        this->renderFast();
                        this->lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
                        pendingFrames = 0;
                    }

                }
                break; //No key pressed
            case keycodes::esc:
                cv::setWindowProperty("Rendered Image", cv::WND_PROP_FULLSCREEN, cv::WINDOW_NORMAL);
                break;
            case keycodes::f:
                cv::setWindowProperty("Rendered Image", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
                break;
            case keycodes::z: case keycodes::s: case keycodes::d:
            case keycodes::q: case keycodes::e: case keycodes::a:
                move(key);
                std::cout << *this->camera << std::endl;
                pendingRender = true;
                pendingFrames++;
                break;
            case keycodes::_plus:
                this->camera->setFocalLength(this->camera->getFocalLength()*1.1); //zoom in
                std::cout << *this->camera << std::endl;
                pendingRender = true;
                pendingFrames++;
                break;
            case keycodes::_minus:
                this->camera->setFocalLength(this->camera->getFocalLength()/1.1); //zoom out
                std::cout << *this->camera << std::endl;
                pendingRender = true;
                pendingFrames++;
                break;
            case keycodes::m:
                //change mode:
                this->mode=this->mode == Mode::strafe?Mode::roll:Mode::strafe;
                showImage("Rendered Image", this->image->getImageBuffer());
                break;
            case keycodes::space:
                this->renderSlow();
                showImage("Rendered Image", this->image->getImageBuffer());
                pendingFrames = 0;
                pendingRender = false;
                break;
            default:
                std::cout << "key pressed:" << key << std::endl;
        }
        if (pendingRender && pendingFrames >= maxPendingFrames){ //force update after x numbers of updates (for smoother movement)
            this->currentRes = Resolution(Screensize::_720p);
            this->currentRes.width/=8;
            this->currentRes.height/=8;
            this->renderFast();
            pendingFrames = 0;
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
    delete this->scene;
    delete this->image;

}

void LiveScreen::renderFast() {
    if (this->currentRes.width > getWidth(Screensize::_1440p)) return;
    Resolution res= Resolution(this->currentRes.width, this->currentRes.height);
    this->camera->setResolution(res);
    RenderEngine engine = RenderEngine(this->scene,this->camera,this->options);
    engine.render();
    delete this->image;
    this->image = new Image(*engine.getImage());
    this->showImage("Rendered Image", this->image->getImageBuffer());
    this->currentRes.width*=2;
    this->currentRes.height*=2;
}


void LiveScreen::renderSlow() {
    this->currentRes = Resolution(Screensize::_4K);
    this->camera->setResolution(this->currentRes);
    RenderEngine engine = RenderEngine(scene,camera,options);
    engine.render();

    delete this->image;
    this->image = new Image(*engine.getImage());

}

void LiveScreen::move(int key) {
    Vec4 lcs_X = this->camera->getTransform() * Vec4(1,0,0,0);
    Vec4 lcs_Y = this->camera->getTransform() * Vec4(0,1,0,0);
    Vec4 lcs_Z = this->camera->getTransform() * Vec4(0,0,1,0);
    if (this->mode == LiveScreen::Mode::strafe){
        switch(key){
            case z: //forward
                lcs_X *= 0.1;
                this->camera->translate(lcs_X.get<_X>(),lcs_X.get<_Y>(),lcs_X.get<_Z>());
                break;
            case s: //backwards
                lcs_X = -lcs_X*0.1;
                this->camera->translate(lcs_X.get<_X>(),lcs_X.get<_Y>(),lcs_X.get<_Z>());
                break;
            case q: // left
                lcs_Y *= 0.1;
                this->camera->translate(lcs_Y.get<_X>(),lcs_Y.get<_Y>(),lcs_Y.get<_Z>());
                break;
            case d: //right
                lcs_Y = -lcs_Y * 0.1;
                this->camera->translate(lcs_Y.get<_X>(),lcs_Y.get<_Y>(),lcs_Y.get<_Z>());
                break;
            case e: //up
                lcs_Z *= 0.1;
                this->camera->translate(lcs_Z.get<_X>(),lcs_Z.get<_Y>(),lcs_Z.get<_Z>());
                break;
            case a: //down
                lcs_Z = -lcs_Z * 0.1;
                this->camera->translate(lcs_Z.get<_X>(),lcs_Z.get<_Y>(),lcs_Z.get<_Z>());
                break;
            default:
                break;
       }
    }
    else if(this->mode == LiveScreen::Mode::roll){
        Vec4 pos = this->camera->getTransform().get<3>(); //last col = translation = position
        this->camera->translate(-pos.get<_X>(),-pos.get<_Y>(),-pos.get<_Z>());//reset position to origin before rotation
        switch(key){
            case z: //pitch forward
                this->camera->rotatef(CV_PI/90, lcs_Y); // -2° rotation
                break;
            case s: //pitch backward
                this->camera->rotatef(-CV_PI/90, lcs_Y); // -2° rotation
                break;
            case q: // yaw left
                this->camera->rotatef(CV_PI/90, lcs_Z); // -2° rotation
                break;
            case d: // yaw right
                this->camera->rotatef(-CV_PI/90, lcs_Z); // -2° rotation
                break;
            case e: // roll ccw
                this->camera->rotatef(CV_PI/90, lcs_X); // -2° rotation
                break;
            case a: // roll cw
                this->camera->rotatef(-CV_PI/90, lcs_X); // -2° rotation
                break;
            default:
                break;
        }
        this->camera->translate(pos.get<_X>(),pos.get<_Y>(),pos.get<_Z>());//reset position to original position before rotation
    }


}

