//
// Created by maart on 30/09/2022.
//


#include <Scene/Scene.h>
#include <Objects/Plane.h>


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
        ThreadPool<void, RenderTask> pool;
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
    this->camera.rotate(0,0,0);
    this->camera.setPosition(Vec4(-7.5,0,3,1));
    this->camera.setSensor(Sensor(360,240));
    this->camera.setResolution(Resolution(Screensize::_4K));
    this->camera.setFocalLength(100);
}

Color3 Scene::shade(int x, int y) {
    Intersection intersect; //object to store intersections, can be reused!
    Color3 color;
    Ray primary =  this->camera.getPrimaryRay(x,y);

    Hit first = Hit();
    if (!getFirstHit(primary, first, intersect)){
        //no hit, set background color:
        color = Color3(0x87, 0xCE, 0xFA);
        return color;
    }

    Vec4 v = - primary.dir(); //always normalized
    Object* obj = first.obj;

    color = obj->getMaterial().emissive;
    Vec4 normal = obj->getTransform() * first.normal;
    normal.normalize();

    for (const Light* light: this->lights){
        if (isInShadow(first.point,obj, light, intersect)) continue;
        //diffuse
        Vec4 s = light->getVec(first.point);
        s.normalize();
        float mDotS = s.dot(normal); // lambert term;
        if (mDotS > 0.0){
            Color3 diffuse = mDotS * obj->getMaterial().diffuse * light->color;
            color.add(diffuse);
        }
        //specular
        Vec4 h  = v + s;
        h.normalize();
        float mDotH = h.dot(normal);
        float phong = std::pow(mDotH, obj->getMaterial().specularExponent);
        Color3 specColor = phong* obj->getMaterial().specular * light->color;
        color.add(specColor);
    }

    //only emissive model:
    /*if (first.t>=0){
        color = first.obj->getMaterial().emissive;
        //rgb = Color3(x, y, 0);
    }*/
    return color;
}

bool Scene::getFirstHit(Ray &ray, Hit &best, Intersection& intersect,  const Object* ignore) const {
    bool flag = false;
    for (auto obj: this->objects){
        if (obj == ignore) continue;
        intersect.clear();
        if (obj->hitPoint(ray, intersect)){
            Hit hit = intersect.hit[0];
            if (best.t > hit.t && hit.t >= 0){
                best = hit;
                flag = true;
            }
        }
    }
    return flag;
}

bool Scene::isInShadow(const Vec4 &point, const Object* obj, const Light* light, Intersection& intersect) const {
    //ray to light source
    Ray ray = light->getRay(point);

    //look for intersections:
    Hit best;
    intersect.clear();
    if (!getFirstHit(ray, best, intersect,obj)) return false; //no hit= not in shadow

    //get distance between point and light:
    float dist = light->getDist(point); //square of the distance!
    if (dist >= best.t * best.t) return true;
    return true;
}

#pragma region MultiThreading tools
//https://www.geeksforgeeks.org/print-given-matrix-counter-clock-wise-spiral-form/
std::vector<int> spiralMap(int row, int col){
    std::vector<int> output;
    output.reserve(row*col);
    int i, k = 0, l = 0;

    //  k - starting row index
    //    row - ending row index
    //    l - starting column index
    //    col - ending column index
    //    i - iterator

    // initialize the count
    int cnt = 0;

    // total number of
    // elements in matrix
    int total = row * col;
    int inCol = col;

    while (k < row && l < col)
    {
        if (cnt == total)
            break;

        // Print the first column
        // from the remaining columns
        for (i = k; i < row; ++i)
        {
            //cout << arr[i][l] << " ";
            //i = row; l = col;
            output.push_back(inCol*i+l);
            cnt++;
        }
        l++;

        if (cnt == total)
            break;

        // Print the last row from
        // the remaining rows
        for (i = l; i < col; ++i)
        {
            //cout << arr[row - 1][i] << " ";
            output.push_back(inCol*(row - 1)+i);
            cnt++;
        }
        row--;

        if (cnt == total)
            break;

        // Print the last column
        // from the remaining columns
        if (k < row)
        {
            for (i = row - 1; i >= k; --i)
            {
                //cout << arr[i][col - 1] << " ";
                output.push_back(inCol*i+(col - 1));
                cnt++;
            }
            col--;
        }

        if (cnt == total)
            break;

        // Print the first row
        // from the remaining rows
        if (l < col)
        {
            for (i = col - 1; i >= l; --i)
            {
                //cout << arr[k][i] << " ";
                //k = row; i = col;
                output.push_back(inCol*k+i);
                cnt++;
            }
            k++;
        }
    }

    return output;
}
void reorder(std::vector<RenderTask*>& vA, std::vector<int>& vOrder)
{
    //assert(vA.size() == vOrder.size());

    //copy tasks:
    std::vector<RenderTask*> copy(vA.size());
    std::copy(vA.begin(), vA.end(), copy.begin());

    // for all elements to put in place
    for( int i = 0; i < vA.size(); ++i )
    {
       //std::cout << vOrder[i] << "\n";
       if (vOrder[i] > vA.size()) continue;
       vA[i] = copy[vOrder[i]];
    }
}
void Scene::createTasks(std::vector<RenderTask*> &tasks) {
    //find suitable size, minimum 16x16, always square, power of 2
    int size = 16;
    const Resolution resolution = this->camera.getResolution();
    int row = int(std::ceil(double(resolution.height) / size));
    int col = int(std::ceil(double(resolution.width) / size));
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

    for (int y=0; y < resolution.height; y+=size){
        for (int x= 0; x < resolution.width; x+=size){;
            tasks.push_back(new RenderTask(this,this->image,x,x+size,y,y+size));
        }
    }

    //remap:
    std::vector<int> spiral = spiralMap(row, col);
    std::reverse(spiral.begin(),spiral.end());
    reorder(tasks,spiral);
}
#pragma endregion

void Image::save(std::string filename) {
    cv::imwrite(filename, this->imageBuffer);
}



