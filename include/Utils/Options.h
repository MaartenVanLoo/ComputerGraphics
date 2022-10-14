//
// Created by maart on 4/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_OPTIONS_H
#define I_COMPUTERGRAPHICS_OPTIONS_H
#include <string>
namespace MRay {
    enum ShaderTypes{
        Phong,
        CookTorrance
    };

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
    };


}
#endif //I_COMPUTERGRAPHICS_OPTIONS_H
