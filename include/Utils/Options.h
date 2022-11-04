//
// Created by Maarten Van Loo on 4/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_OPTIONS_H
#define I_COMPUTERGRAPHICS_OPTIONS_H
#include <string>
namespace MRay {
    enum ShaderTypes{
        Phong,
        CookTorrance
    };
    template<ShaderTypes T>
    std::string toString(){
        switch(T){
            case ShaderTypes::Phong:
                return "Phong";
            case ShaderTypes::CookTorrance:
                return "CookTorrance";
            default:
                return "";
        }
    }

    struct Options {
        bool enableGui = false;
        bool quitOnFinish = false;
        bool multicore = false;
        std::string renderName = "render";

        //render settings
        Color3 background = Color3(0x87, 0xCE, 0xFA);

        ShaderTypes shaderType = Phong;
        bool enableAliasing = false;
        int oversamplingRate = 1;

        double shininessThreshold = 0.0001;
        double transparencyThreshold = 0.0001;
        int maxRayBounce = 6;
        double eps = 0.001;
    };


}
#endif //I_COMPUTERGRAPHICS_OPTIONS_H
