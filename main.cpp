#include <iostream>
#include <Utils/Stopwatch.h>

#include "include/RenderEngineCore.h"
#include <cmath>
#include <sstream>
#include <Materials/Material.h>
#include <Scene/Scene.h>
#include <iomanip>
#include <Textures/Checkerboard.h>
#include <Render/RenderEngine.h>
#include <Screen/LiveScreen.h>
int main() {
    Stopwatch stopwatch = Stopwatch();
    stopwatch.start();

    MRay::Scene scene = MRay::Scene();
    scene.hardReset();
    //scene.load("../../SDL/spacecraft.json");
    //scene.load("../../SDL/sdl.json");
    //scene.load("../../SDL/sdl_all.json");
    scene.load("../../SDL/materialTest.json");

    MRay::Options options;
    options.enableGui = true;
    options.multicore = false;
    options.quitOnFinish = false;
    //options.shaderType = MRay::ShaderTypes::Phong;
    options.shaderType = MRay::ShaderTypes::CookTorrance;
    options.renderName = "render";

    MRay::Camera camera = MRay::Camera();
    //camera.setPosition(MRay::Vec4(-9,0,2,1));
    camera.rotate(0.0f,float(CV_PI/4.0),0.0f);
    camera.translate(-18,0,20);
    camera.setSensor(MRay::Sensor(360,240));
    camera.setResolution(MRay::Resolution(MRay::Screensize::_1080p));
    camera.setFocalLength(100);


    MRay::RenderEngine engine(&scene, &camera, options);
    engine.render();
    //MRay::LiveScreen liveScreen = MRay::LiveScreen(&scene, &camera, options);
    //liveScreen.show();

    /*sequence render:
    for(int i =0; i < 720; i+=5){
        std::ostringstream oss;
        oss << "Render_"<<std::setw(3) << i;
        options.renderName = oss.str();
        std::cout << "Current render:" << options.renderName << std::endl;

        //scene.clearLights();
        camera.rotate(0,0,2.5*CV_PI/180);
        //rotate light
        //MRay::Light* light = new MRay::PointLight(MRay::Vec4(float(10.0*cos(i*CV_PI/180)),float(10.0 *sin((i*CV_PI/180))),10));
        //scene.addLight(light);
        //light = new MRay::PointLight(MRay::Vec4(float(10.0*cos((i+90)*CV_PI/180)),float(10.0 *sin(((i+90)*CV_PI/180))),10));
        //move light
        //MRay::Light* light = new MRay::PointLight(MRay::Vec4(i/3.6,0,10));
        //scene.addLight(light);
        engine.setOptions(options);
        engine.render();
    }
*/
    system("pause");
    return 0;
}
