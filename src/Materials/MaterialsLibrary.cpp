//
// Created by Maarten Van Loo on 12/10/2022.
//

#include <Materials/MaterialsLibrary.h>
using namespace MRay;

Material MaterialsLibrary::emerald(){
        return Material(0.0215*255, 0.1745*255, 0.0215*255, 0.07568, 0.61424, 0.07568, 0.633, 0.727811, 0.633, 0.6*128,
                        1.586,1.586,1.586);
}

Material MaterialsLibrary::jade(){
        return Material(0.135*255, 0.2225*255, 0.1575*255, 0.54, 0.89, 0.63, 0.316228, 0.316228, 0.316228, 0.1*128,
                        1.6,1.6,1.6);
}

Material MaterialsLibrary::obsidian(){
        return Material(0.05375*255, 0.05*255, 0.06625*255, 0.18275, 0.17, 0.22525, 0.332741, 0.328634, 0.346435, 0.3*128,
                        1.5,1.5,1.5);
}

Material MaterialsLibrary::pearl(){
        return Material(0.25*255, 0.20725*255, 0.20725*255, 1, 0.829, 0.829, 0.296648, 0.296648, 0.296648, 0.088*128,
                        1.53,1.53,1.523);
}

Material MaterialsLibrary::ruby(){
        return Material(0.1745*255, 0.01175*255, 0.01175*255, 0.61424, 0.04136, 0.04136, 0.727811, 0.626959, 0.626959, 0.6*128,
                        1.76,1.76,1.76);
}

/**
 * No Fresnel coefficient known?
 * @return
 */
Material MaterialsLibrary::turquoise(){
        return Material(0.1*255, 0.18725*255, 0.1745*255, 0.396, 0.74151, 0.69102, 0.297254, 0.30829, 0.306678, 0.1*128,
                        1, 1, 1);
}

Material MaterialsLibrary::brass(){
        return Material(0.329412*255, 0.223529*255, 0.027451*255, 0.780392, 0.568627, 0.113725, 0.992157, 0.941176, 0.807843, 0.21794872*128,
                        1.44400 , 1.52700,1.0940);
}

Material MaterialsLibrary::bronze(){
        return Material(0.2125*255, 0.1275*255, 0.054*255, 0.714, 0.4284, 0.18144, 0.393548, 0.271906, 0.166721, 0.2*128,
                        1.44400 , 1.52700,1.0940);
}

Material MaterialsLibrary::chrome(){
        return Material(0.25*255, 0.25*255, 0.25*255, 0.4, 0.4, 0.4, 0.774597, 0.774597, 0.774597, 0.6*128,
                        3.1071,3.1812,2.3230);
}


Material MaterialsLibrary::copper(){
        return Material(0.19125*255, 0.0735*255, 0.0225*255, 0.7038, 0.27048, 0.0828, 0.256777, 0.137622, 0.086014, 0.1*128,
                        1.27105,1.67693,1.3164);
}

Material MaterialsLibrary::gold(){
        return Material(0.24725*255, 0.1995*255, 0.0745*255, 0.75164, 0.60648, 0.22648, 0.628281, 0.555802, 0.366065, 0.4*128,
                        1.18299 ,1.42108,1.3734);
}

Material MaterialsLibrary::silver(){
        return Material(0.19225*255, 0.19225*255, 0.19225*255, 0.50754, 0.50754, 0.50754, 0.508273, 0.508273, 0.508273, 0.4*128,
                        1.15943,1.14512, 1.13547);
}

/// Based on PVP, polyvinylpyrrolidone
/// \return
Material MaterialsLibrary::black_plastic(){
        return Material(0.0*255, 0.0*255, 0.0*255, 0.01, 0.01, 0.01, 0.50, 0.50, 0.50, .25*128,
                        1.5245,1.5299,1.5413);
}
/// Based on PVP, polyvinylpyrrolidone
/// \return
Material MaterialsLibrary::cyan_plastic(){
        return Material(0.0*255, 0.1*255, 0.06*255, 0.0, 0.50980392, 0.50980392, 0.50196078, 0.50196078, 0.50196078, .25*128,
                        1.5245,1.5299,1.5413);
}
/// Based on PVP, polyvinylpyrrolidone
/// \return
Material MaterialsLibrary::green_plastic(){
        //return Material(0.0, 0.0, 0.0, 0.1, 0.05, 0.1, 0.05, 0.05, 0.45, .9*128,
        //                1.5245,1.5299,1.5413);
        return Material(0.01*255, 0.1*255, 0.01*255, 0.1, 0.35, 0.1, 0.45, 0.55, 0.45, .25*128,
                        1.5245,1.5299,1.5413);
}
/// Based on PVP, polyvinylpyrrolidone
/// \return
Material MaterialsLibrary::red_plastic(){
        return Material(.5*255, 0.2*255, 0.2*255, 0.5, 0.0, 0.0, 0.7, 0.6, 0.6, .25*128,
                        1.5245*10,1.5299*10,1.5413*10);
}
/// Based on PVP, polyvinylpyrrolidone
/// \return
Material MaterialsLibrary::white_plastic(){
        return Material(0.0*255, 0.0*255, 0.0*255, 0.55, 0.55, 0.55, 0.70, 0.70, 0.70, .25*128,
                        1.5245,1.5299,1.5413);
}
/// Based on PVP, polyvinylpyrrolidone
/// \return
Material MaterialsLibrary::yellow_plastic(){
        return Material(0.2*255, 0.2*255, 0.05*255, 0.5, 0.5, 0.0, 0.60, 0.60, 0.50, .25*128,
                        1.5245,1.5299,1.5413);
}
/// Based on PVP, polyvinylpyrrolidone
/// \return
Material MaterialsLibrary::gray_plastic() {
    return Material(0.1*255, 0.1*255, 0.1*255, 0.3, 0.3, 0.3, 0.50, 0.50, 0.50, .25*128,
                    1.5245,1.5299,1.5413);
}

///rubber is similar to plastic for refractive indeces
Material MaterialsLibrary::black_rubber(){
        return Material(0.02*255, 0.02*255, 0.02*255, 0.01, 0.01, 0.01, 0.4, 0.4, 0.4, .078125*128,
                1.5245,1.5299,1.5413);
}

///rubber is similar to plastic for refractive indeces
Material MaterialsLibrary::cyan_rubber(){
        return Material(0.0*255, 0.05*255, 0.05*255, 0.4, 0.5, 0.5, 0.04, 0.7, 0.7, .078125*128,
                        1.5245,1.5299,1.5413);
}

///rubber is similar to plastic for refractive indeces
Material MaterialsLibrary::green_rubber(){
        return Material(0.0*255, 0.05*255, 0.0*255, 0.4, 0.5, 0.4, 0.04, 0.7, 0.04, .078125*128,
                        1.5245,1.5299,1.5413);
}

///rubber is similar to plastic for refractive indeces
Material MaterialsLibrary::red_rubber(){
        return Material(0.05*255, 0.0*255, 0.0*255, 0.5, 0.4, 0.4, 0.7, 0.04, 0.04, .078125*128,
                        1.5245,1.5299,1.5413);
}

///rubber is similar to plastic for refractive indeces
Material MaterialsLibrary::white_rubber(){
        return Material(0.05*255, 0.05*255, 0.05*255, 0.5, 0.5, 0.5, 0.7, 0.7, 0.7, .078125*128,
                        1.5245,1.5299,1.5413);
}

///rubber is similar to plastic for refractive indeces
Material MaterialsLibrary::yellow_rubber(){
        return Material(0.05*255, 0.05*255, 0.0*255, 0.5, 0.5, 0.4, 0.7, 0.7, 0.04, .078125*128,
                        1.5245,1.5299,1.5413);
}

///rubber is similar to plastic for refractive indeces
Material MaterialsLibrary::gray_rubber() {
        return Material(0.12*255, 0.12*255, 0.12*255, 0.3, 0.3, 0.3, 0.4, 0.4, 0.4, .078125*128,
                        1.5245,1.5299,1.5413);
}
const std::unordered_map<std::string,Material> MaterialsLibrary::materials = std::unordered_map<std::string, Material>({
    {"emerald",MaterialsLibrary::emerald()},
    {"jade",MaterialsLibrary::jade()},
    {"obsidian",MaterialsLibrary::obsidian()},
    {"pearl",MaterialsLibrary::pearl()},
    {"ruby",MaterialsLibrary::ruby()},
    {"turquoise",MaterialsLibrary::turquoise()},
    {"brass",MaterialsLibrary::brass()},
    {"bronze",MaterialsLibrary::bronze()},
    {"chrome",MaterialsLibrary::chrome()},
    {"copper",MaterialsLibrary::copper()},
    {"gold",MaterialsLibrary::gold()},
    {"silver",MaterialsLibrary::silver()},
    {"black_plastic",MaterialsLibrary::black_plastic()},
    {"cyan_plastic",MaterialsLibrary::cyan_plastic()},
    {"green_plastic",MaterialsLibrary::green_plastic()},
    {"red_plastic",MaterialsLibrary::red_plastic()},
    {"white_plastic",MaterialsLibrary::white_plastic()},
    {"yellow_plastic",MaterialsLibrary::yellow_plastic()},
    {"gray_plastic",MaterialsLibrary::gray_plastic()},
    {"black_rubber",MaterialsLibrary::black_rubber()},
    {"cyan_rubber",MaterialsLibrary::cyan_rubber()},
    {"green_rubber",MaterialsLibrary::green_rubber()},
    {"red_rubber",MaterialsLibrary::red_rubber()},
    {"white_rubber",MaterialsLibrary::white_rubber()},
    {"yellow_rubber",MaterialsLibrary::yellow_rubber()},
    {"gray_rubber",MaterialsLibrary::gray_rubber()},
    });
