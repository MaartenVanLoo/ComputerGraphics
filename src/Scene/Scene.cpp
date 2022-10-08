//
// Created by maart on 30/09/2022.
//

#include <Utils/Stopwatch.h>
#include <Utils/Options.h>
#include <Scene/Scene.h>


Scene::~Scene() {
    for (auto obj : this->objects){
        free(obj);
    }
    for (auto light: this->lights){
        free(light);
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
void Scene::addLight(Light* light) {
    this->lights.push_back(light);
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
    if (options.multicore){
        std::vector<RenderTask*> renderTasks;
        createTasks(renderTasks);
        ThreadPool pool = ThreadPool<void, RenderTask>();
        for (auto task: renderTasks){
            pool.pushTaskQueue(task);
        }
        for (auto task:renderTasks){
            while (!task->done()){
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(100ms);
            }
        }
        pool.terminate();
    }
    else {
        for (int y = 0; y < this->camera.getResolution().height; y++) {
            for (int x = 0; x < this->camera.getResolution().width; x++) {
                Color3 rgb = this->shade(x, y);
                this->image->setPixel(x, y, rgb);
            }
#if artificaldelay
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(5ms);
#endif
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

Color3 Scene::shade(int x, int y) {
    Color3 rgb;
    Ray primary =  this->camera.getPrimaryRay(x,y);
    //std::cout <<primary << std::endl;
    Hit first = Hit();

    getFirstHit(primary, first);
    if (first.t == FLT_MAX || first.t < 0){
        //no hit = background
        rgb = Color3(0x87, 0xCE, 0xFA);

    }
    else if (first.t>=0){
        rgb = first.obj->getMaterial().emissive;
        //rgb = Color3(x, y, 0);
    }
    return rgb;
}

void Scene::getFirstHit(Ray &ray, Hit &hit) {
    hit = Hit();
    Hit hit1,hit2;
    for (auto obj: this->objects){
        if (obj->hitPoint(ray, hit1, hit2)){
            if (hit.t > hit1.t && hit1.t >= 0){
                hit = hit1;
            }
            if (hit.t > hit2.t && hit2.t >= 0){
                hit = hit2;
            }
        }
    }

}

void Scene::createTasks(std::vector<RenderTask*> &tasks) {
    //find suitable size, minimum 16x16, always square, power of 2
    int size = 16;
    const Resolution resolution = this->camera.getResolution();
    int row = std::ceil(double(resolution.height) / size);
    int col = std::ceil(double(resolution.width) / size);
    int taskCount = row*col;
    const int processor_count = (int)std::thread::hardware_concurrency();
    while (taskCount > (4*workerjobs*processor_count)){
        size *=2;
        row = int(std::ceil(double(resolution.height) / size));
        col = int(std::ceil(double(resolution.width) / size));
        taskCount = row*col;
    }
    //task size is defined, start creating tasks
    tasks.reserve(taskCount);
    for (int x=0; x < resolution.width; x+=size){
        for (int y= 0; y < resolution.height; y+=size){
            tasks.push_back(new RenderTask(this,this->image,x,x+size,y,y+size));
        }
    }
}


void Image::save(std::string filename) {
    cv::imwrite(filename, this->imageBuffer);
}



