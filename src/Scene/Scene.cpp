//
// Created by maart on 30/09/2022.
//

#include <Utils/Stopwatch.h>
#include <Utils/Options.h>
#include "../../include/Scene/Scene.h"

Scene::~Scene() {
    for (auto obj : this->objects){
        free(obj);
    }
    if (this->screen != nullptr){
        this->screen->waitClose();
        free(this->screen);
    }
    if (this->image != nullptr){
        free(this->image);
    }
}

std::ostream &operator<<(std::ostream &os, const Scene &scene) {
    os << "Scene: {" <<"objects: " << scene.objects.size() << "}";
    return os;
}

void Scene::addObject(Object *obj) {
    this->objects.push_back(obj);
}

void Scene::Render(const Options &options) {
    if (this->image != nullptr) free(this->image);
    this->image = new Image(camera.getResolution());

    //create new gui
    if (options.enableGui) {
        this->screen = new Screen(*this->image);
        this->screen->show();
    }
    Stopwatch stopwatch = Stopwatch();
    stopwatch.start();

    //main render loop
    for (int y = 0; y < this->camera.getResolution().height; y++){
        for (int x = 0; x < this->camera.getResolution().width; x++){
            RGB rgb = this->computePixelColor(x,y);
            this->image->setPixel(x, y,rgb);
        }
    }
    stopwatch.stop();
    std::cout << "Render finished in : " << stopwatch.elapsedms() << " ms" << std::endl;
    std::cout << "Pixel count: " << this->camera.getResolution().getPixels() << std::endl;
    std::cout << "Pixels / second : " << this->camera.getResolution().getPixels() * 1000/stopwatch.elapsedms() << std::endl;
    stopwatch.reset();
    stopwatch.start();
    this->image->update();
    this->image->save("render.png");
    this->image->save("render.bmp");
    stopwatch.stop();
    std::cout << "File saved in :" << stopwatch.elapsedms() << " ms" << std::endl;

    //close gui
    if (options.enableGui) {
        this->screen->waitClose();
        //cleanup screen
        free(this->screen);
        this->screen = nullptr;
    }

}

Scene::Scene() {
    this->camera.setPosition(Vec4(-5,0,0,1));
    this->camera.setDirection(Vec4(1,0,0, 0));
    this->camera.setSensor(Sensor(360,240));
    this->camera.setResolution(Resolution(Screensize::_4K));
    this->camera.setFocalLength(100);
}

RGB Scene::computePixelColor(int x, int y) {
    RGB rgb;
    Ray primary =  this->camera.getPrimaryRay(x,y);
    //std::cout <<primary << std::endl;
    for (auto obj: this->objects){
        float t1,t2;
        if (obj->hitPoint(primary, t1, t2)){
             rgb = RGB(x, y, 0);
        }
    }
    return rgb;
}

void Image::save(std::string filename) {
    cv::imwrite(filename, this->imageBuffer);
}



