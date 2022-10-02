//
// Created by maart on 30/09/2022.
//

#include "../../include/Scene/Scene.h"

Scene::~Scene() {
    for (auto obj : this->objects){
        free(obj);
    }
    if (this->screen != nullptr){
        this->screen->waitClose();
        free(this->screen);
    }
    if (this->image == nullptr){
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

void Scene::Render() {
    if (this->image == nullptr) free(this->image);
    this->image = new Image(camera.getResolution());

    //create new gui
    this->screen = new Screen(*this->image);
    this->screen->show();

    //main render loop
    for (int y = 0; y < this->camera.getResolution().height; y++){
        for (int x = 0; x < this->camera.getResolution().width; x++){
            Ray primary =  this->camera.getPrimaryRay(x,y);
            //std::cout <<primary << std::endl;
            for (auto obj: this->objects){
                float t1,t2;
                if (obj->hitPoint(primary, t1, t2)){
                    this->image->setPixel(x, y, RGB(x, y, 0));
                }
            }
            //image.setPixel(x, y, RGB(x, y, 0));
        }
    }
    this->image->update();
    this->image->save("render.png");
    this->image->save("render.bmp");
    this->screen->waitClose();

    //cleanup screen
    free(this->screen);
    this->screen = nullptr;

}

Scene::Scene() {
    this->camera.setPosition(Vec4(-5,0,0,1));
    this->camera.setDirection(Vec4(1,0,0, 0));
    this->camera.setSensor(Sensor(360,240));
    this->camera.setResolution(Resolution(Screensize::_4K));
    this->camera.setFocalLength(100);
}

void Image::save(std::string filename) {
    cv::imwrite(filename, this->imageBuffer);
}



