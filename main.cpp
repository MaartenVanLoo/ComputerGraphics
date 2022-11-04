#include <iostream>
#include <Utils/Stopwatch.h>


#include "Textures/Perlin.h"

#include <cmath>
#include <sstream>
#include <Materials/Material.h>
#include <Scene/Scene.h>
#include <iomanip>
#include <Textures/Checkerboard.h>
#include <Render/RenderEngine.h>
#include <Screen/LiveScreen.h>
int main() {

    //try to make wood
    //MRay::WoodTexture wood = MRay::WoodTexture();
    //wood.preview(-1,1,-1,1);

    MRay::PerlinPlot plotter(1500,1000);
    MRay::Perlin2D perlin2D = MRay::Perlin2D();
    perlin2D.setScale(MRay::Vec3(0.005f,0.005f,0.005f));
    perlin2D.setOctaves(2);
    plotter.plot(perlin2D, -255*4, 255*4, -255*4, 255*4);


    //MRay::Perlin3D perlin3D_1 = MRay::Perlin3D();
    //perlin3D_1.setRoughness(0.5);
    //perlin3D_1.setScale(MRay::Vec3(0.01,0.01,0.01));
    //perlin3D_1.setOctaves(0);
    //plotter.plot(perlin3D_1, -1000, 1000, -1000, 1000, 0);
    //perlin3D_1.setOctaves(1);
    //plotter.plot(perlin3D_1, -1000, 1000, -1000, 1000, 0);
    //perlin3D_1.setOctaves(2);
    //plotter.plot(perlin3D_1, -1000, 1000, -1000, 1000, 0);
    //perlin3D_1.setOctaves(3);
    //plotter.plot(perlin3D_1, -1000, 1000, -1000, 1000, 0);
    //perlin3D_1.setOctaves(4);
    //plotter.plot(perlin3D_1, -1000, 1000, -1000, 1000, 0);
    //perlin3D_1.setOctaves(5);
    //plotter.plot(perlin3D_1, -1000, 1000, -1000, 1000, 0);
    //perlin3D_1.setOctaves(6);
    //plotter.plot(perlin3D_1, -1000, 1000, -1000, 1000, 0);
    //perlin3D_1.setOctaves(7);
    //plotter.plot(perlin3D_1, -1000, 1000, -1000, 1000, 0);
    //perlin3D_1.setOctaves(8);
    //plotter.plot(perlin3D_1, -1000, 1000, -1000, 1000, 0);
    //perlin3D_1.setOctaves(9);
    //plotter.plot(perlin3D_1, -1000, 1000, -1000, 1000, 0);

    //MRay::Perlin3D perlin3D_2 = MRay::Perlin3D();
    //perlin3D_2.setRoughness(.66);
    //perlin3D_2.setScale(MRay::Vec3(1,1,1));
    //plotter.plot(perlin3D_2, 0.01, 0.01, 0.01, 0);

    //plotter.plot(perlin3D_1,perlin3D_2,0.01,0.01,0.01,0);
    //return 0;

    Stopwatch stopwatch = Stopwatch();
    stopwatch.start();

    MRay::Scene scene = MRay::Scene();
    scene.hardReset();
    //scene.load("../../SDL/spacecraft.json");
    //scene.load("../../SDL/sdl.json");
    //scene.load("../../SDL/sdl_all.json");
    //scene.load("../../SDL/materialTest.json");
    scene.load("../../SDL/RefractionTest.json");

    MRay::Options options;
    options.enableGui = true;
    options.multicore = true;
    options.quitOnFinish = false;
    //options.shaderType = MRay::ShaderTypes::Phong;
    options.shaderType = MRay::ShaderTypes::CookTorrance;
    options.renderName = "render";

    MRay::Camera camera = MRay::Camera();
    //camera.setPosition(MRay::Vec4(-9,0,2,1));
    //camera.rotate(0.0f,float(CV_PI/4.0),0.0f);
    camera.translate(-10,5,1);
    camera.setSensor(MRay::Sensor(360,240));
    camera.setResolution(MRay::Resolution(MRay::Screensize::_1080p));
    camera.setFocalLength(200);


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
