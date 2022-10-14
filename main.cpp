#include <iostream>
#include <Utils/Stopwatch.h>

#include "include/RenderEngineCore.h"
#include <cmath>
#include <sstream>
#include <Materials/Material.h>
#include <Scene/Scene.h>
#include <iomanip>
#include <Textures/Checkerboard.h>

int main() {
    Stopwatch stopwatch = Stopwatch();
    stopwatch.start();

    MRay::Scene scene = MRay::Scene();
    scene.load((std::string &) "");
    MRay::Options options;
    options.enableGui = true;
    options.multicore = false;
    scene.Render(options);
    /*
    //sequence render:
    for(int i =0; i < 720; i+=5){
        std::ostringstream oss;
        oss << "Render_"<<std::setw(3) << i;
        options.renderName = oss.str();
        std::cout << "Current render:" << options.renderName << std::endl;

        //scene.clearLights();
        scene.getCamera().rotate(0,2.5*CV_PI/180,0);
        //rotate light
        //MRay::Light* light = new MRay::PointLight(MRay::Vec4(float(10.0*cos(i*CV_PI/180)),float(10.0 *sin((i*CV_PI/180))),10));
        //scene.addLight(light);
        //light = new MRay::PointLight(MRay::Vec4(float(10.0*cos((i+90)*CV_PI/180)),float(10.0 *sin(((i+90)*CV_PI/180))),10));
        //move light
        //MRay::Light* light = new MRay::PointLight(MRay::Vec4(i/3.6,0,10));
        //scene.addLight(light);

        scene.Render(options);
    }
*/
    system("pause");
    return 0;
}
