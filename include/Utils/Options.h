//
// Created by maart on 4/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_OPTIONS_H
#define I_COMPUTERGRAPHICS_OPTIONS_H
#include <string>
namespace MRay {

    struct Options {
        bool enableGui = false;
        bool multicore = false;
        std::string renderName = "render";
    };
}
#endif //I_COMPUTERGRAPHICS_OPTIONS_H
