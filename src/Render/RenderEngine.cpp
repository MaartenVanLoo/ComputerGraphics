//
// Created by Maarten Van Loo on 14/10/2022.
//

#include <Render/RenderEngine.h>
#include <Render/CookTorranceShader.h>

using namespace MRay;


RenderEngine::RenderEngine(Scene *scene, Camera *camera,Options &options) :scene(scene), camera(camera), options(options){
    switch (options.shaderType){
        case ShaderTypes::Phong:
            this->shader = new  PhongShader(this->scene, this->camera, this->options);
            break;
        case ShaderTypes::CookTorrance:
            this->shader = new CookTorranceShader(this->scene, this->camera, this->options);
            break;
        default:
            break;
    }
}

#pragma region Getters & Setters
Scene *RenderEngine::getScene() const {
    return scene;
}

void RenderEngine::setScene(Scene *scene) {
    RenderEngine::scene = scene;
}

Camera *RenderEngine::getCamera() const {
    return camera;
}

void RenderEngine::setCamera(Camera *camera) {
    RenderEngine::camera = camera;
}

const Options &RenderEngine::getOptions() const {
    return options;
}

void RenderEngine::setOptions(const Options &options) {
    RenderEngine::options = options;
}

Shader *RenderEngine::getShader() const {
    return shader;
}

void RenderEngine::setShader(Shader *shader) {
    RenderEngine::shader = shader;
}

#pragma endregion

void RenderEngine::render() {
    //track progress in cli:
    int progress = 0; //0 = start, 100= finish

    //Set render image
    if (this->image != nullptr) free(this->image);
    this->image = new Image(camera->getResolution());

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
        stopwatch.stop();
        std::cout << "Threads created and started:" << stopwatch;
        std::cout.flush();
        stopwatch.start();
        for (auto task = renderTasks.begin(); task < renderTasks.end(); task ++){
            while (!(*task)->done()){
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(50ms);
            }
            int i = task - renderTasks.begin();
            if (progress < i*100/renderTasks.size()){
                progress = i*100/renderTasks.size();
                RenderEngine::updateCli(progress);
            }
        }
        pool.terminate();
    }
    else {
        for (int y = 0; y < this->camera->getResolution().height; y++) {
            for (int x = 0; x < this->camera->getResolution().width; x++) {
                Color3 rgb = this->shader->shade(x,y);
                this->image->setPixel(x, y, rgb);
            }
            if (progress < y*100/this->camera->getResolution().height){
                progress = y*100/this->camera->getResolution().height;
                RenderEngine::updateCli(progress);
            }
#if artificaldelay
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(5ms);
#endif
        }
    }
    RenderEngine::updateCli(100);
    std::cout << std::endl;
    stopwatch.stop();
    // print render info
    std::cout << "Render finished in : " << stopwatch.elapsedms() << " ms\n";
    std::cout << "Pixel count: " << this->camera->getResolution().getPixels() << "\n";
    std::cout << "Pixels / second : " << this->camera->getResolution().getPixels() * 1000/stopwatch.elapsedms() << "\n";
    stopwatch.reset();
    stopwatch.start();
    this->image->update();
    this->image->save(options.renderName + ".png");
    //this->image->save(options.renderName+ ".bmp");
    stopwatch.stop();
    std::cout << "File saved in :" << stopwatch.elapsedms() << " ms\n";

    //close gui
    if (options.enableGui) {
        if (this->options.quitOnFinish) this->screen->hide();
        else                            this->screen->waitClose();
        //cleanup screen
        delete this->screen;
        this->screen = nullptr;
    }
    std::cout << "\n\n" << std::endl;
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
void RenderEngine::createTasks(std::vector<RenderTask*> &tasks) {
    //find suitable size, minimum 16x16, always square, power of 2
    int size = 4;
    const Resolution resolution = this->camera->getResolution();
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

Image *RenderEngine::getImage() {
    return this->image;
}

void RenderEngine::updateCli(int progress) {
    std::cout << "\r" << "Progress: " << std::setw(3) << progress << " %";
    std::cout.flush();
}


#pragma endregion