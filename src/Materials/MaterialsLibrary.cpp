//
// Created by Maarten Van Loo on 12/10/2022.
//

#include <Materials/MaterialsLibrary.h>
using namespace MRay;

//http://www.cs.cornell.edu/courses/cs5625/2013sp/lectures/Lec2ShadingModelsWeb.pdf
Material MaterialsLibrary::emerald(){
    //phong
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.0215*255,0.1745*255,0.0215*255);
    phongMaterial.diffuse = Vec4(0.07568, 0.61424, 0.07568);
    phongMaterial.specular = Vec4(0.633, 0.727811, 0.633);
    phongMaterial.shininess = 0.6;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.0215*255,0.1745*255,0.0215*255);
    cookTorrenceMaterial.diffuse = Vec4(0.07568, 0.61424, 0.07568);
    cookTorrenceMaterial.fresnell = Vec4(1.586,1.586,1.586);
    cookTorrenceMaterial.shininess = 0.6;

    return Material(phongMaterial, cookTorrenceMaterial);
}

Material MaterialsLibrary::jade(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.135*255, 0.2225*255, 0.1575*255);
    phongMaterial.diffuse = Vec4(0.54, 0.89, 0.63);
    phongMaterial.specular = Vec4(0.316228, 0.316228, 0.316228);
    phongMaterial.shininess = 0.1;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.135*255, 0.2225*255, 0.1575*255);
    cookTorrenceMaterial.diffuse = Vec4(0.54, 0.89, 0.63);
    cookTorrenceMaterial.fresnell = Vec4(1.6,1.6,1.6);
    cookTorrenceMaterial.transparency = 0.3; //no source....
    cookTorrenceMaterial.shininess = 0.1;
    return Material(phongMaterial, cookTorrenceMaterial);
}

Material MaterialsLibrary::obsidian(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.05375*255, 0.05*255, 0.06625*255);
    phongMaterial.diffuse = Vec4( 0.18275, 0.17, 0.22525);
    phongMaterial.specular = Vec4(0.332741, 0.328634, 0.346435);
    phongMaterial.shininess = 0.3;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.05375*255, 0.05*255, 0.06625*255);
    cookTorrenceMaterial.diffuse = Vec4(0.18275, 0.17, 0.22525);
    cookTorrenceMaterial.fresnell = Vec4(1.5,1.5,1.5); //https://nationalgemlab.in/obsidian/
    cookTorrenceMaterial.transparency = 0.3; //no source....
    cookTorrenceMaterial.shininess = 0.3;
    return Material(phongMaterial, cookTorrenceMaterial);
}

Material MaterialsLibrary::pearl(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.25*255, 0.20725*255, 0.20725*255);
    phongMaterial.diffuse = Vec4( 1, 0.829, 0.829);
    phongMaterial.specular = Vec4(0.296648, 0.296648, 0.296648);
    phongMaterial.shininess = 0.088;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.25*255, 0.20725*255, 0.20725*255);
    cookTorrenceMaterial.diffuse = Vec4(1, 0.829, 0.829);
    cookTorrenceMaterial.fresnell = Vec4(1.53,1.53,1.523);
    cookTorrenceMaterial.transparency = 0.21; //[0.30,0.18,0.15]; //https://www.nature.com/articles/s41598-021-94737-w
    cookTorrenceMaterial.shininess = 0.088;
    return Material(phongMaterial, cookTorrenceMaterial);
}

Material MaterialsLibrary::ruby(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.1745*255, 0.01175*255, 0.01175*255);
    phongMaterial.diffuse = Vec4( 0.61424, 0.04136, 0.04136);
    phongMaterial.specular = Vec4(0.727811, 0.626959, 0.626959);
    phongMaterial.shininess = 0.6;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.1745*255, 0.01175*255, 0.01175*255);
    cookTorrenceMaterial.diffuse = Vec4(0.61424, 0.04136, 0.04136);
    cookTorrenceMaterial.fresnell = Vec4(1.77,1.77,1.77);
    cookTorrenceMaterial.shininess = 0.6;
    cookTorrenceMaterial.transparency =0.29;//[.42,.13,.33];  //https://www.lotusgemology.com/mobile/index.php/library/articles/310-presidium-synthetic-ruby-identifier
    cookTorrenceMaterial.roughness = 0.2;
    return Material(phongMaterial, cookTorrenceMaterial);
}

/**
 * No Fresnel coefficient known?
 * @return
 */
Material MaterialsLibrary::turquoise(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.1*255, 0.18725*255, 0.1745*255);
    phongMaterial.diffuse = Vec4( 0.396, 0.74151, 0.69102);
    phongMaterial.specular = Vec4(0.297254, 0.30829, 0.306678);
    phongMaterial.shininess = 0.1;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.1*255, 0.18725*255, 0.1745*255);
    cookTorrenceMaterial.diffuse = Vec4(0.396, 0.74151, 0.69102);
    cookTorrenceMaterial.fresnell = Vec4(1, 1, 1);
    cookTorrenceMaterial.shininess = 0.1;
    return Material(phongMaterial, cookTorrenceMaterial);
}

Material MaterialsLibrary::brass(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.329412*255, 0.223529*255, 0.027451*255);
    phongMaterial.diffuse = Vec4( 0.780392, 0.568627, 0.113725);
    phongMaterial.specular = Vec4(0.992157, 0.941176, 0.807843);
    phongMaterial.shininess = 0.21794872;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.329412*255, 0.223529*255, 0.027451*255);
    cookTorrenceMaterial.diffuse = Vec4(0.780392, 0.568627, 0.113725);
    cookTorrenceMaterial.fresnell = Vec4(1.44400 , 1.52700,1.0940);
    cookTorrenceMaterial.shininess = 0.21794872;
    return Material(phongMaterial, cookTorrenceMaterial);
}

Material MaterialsLibrary::bronze(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.2125*255, 0.1275*255, 0.054*255);
    phongMaterial.diffuse = Vec4( 0.714, 0.4284, 0.18144);
    phongMaterial.specular = Vec4(0.393548, 0.271906, 0.166721);
    phongMaterial.shininess = 0.2;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.2125*255, 0.1275*255, 0.054*255);
    cookTorrenceMaterial.diffuse = Vec4(0.714, 0.4284, 0.18144);
    cookTorrenceMaterial.fresnell = Vec4(1.44400 , 1.52700,1.0940);
    cookTorrenceMaterial.shininess = 0.2;
    return Material(phongMaterial, cookTorrenceMaterial);
}

Material MaterialsLibrary::chrome(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.15*255, 0.15*255, 0.15*255);
    phongMaterial.diffuse = Vec4(0.4, 0.4, 0.4);
    phongMaterial.specular = Vec4(0.774597, 0.774597, 0.774597);
    phongMaterial.shininess = 0.6;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.15*255, 0.15*255, 0.15*255);
    cookTorrenceMaterial.diffuse = Vec4(0.4, 0.4, 0.4);
    cookTorrenceMaterial.fresnell = Vec4(1.1071,1.1812,1.3230);
    cookTorrenceMaterial.shininess = 0.6;
    cookTorrenceMaterial.roughness = 0.2;
    return Material(phongMaterial, cookTorrenceMaterial);
}


Material MaterialsLibrary::copper(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.19125*255, 0.0735*255, 0.0225*255);
    phongMaterial.diffuse = Vec4(0.7038, 0.27048, 0.0828);
    phongMaterial.specular = Vec4(0.256777, 0.137622, 0.086014);
    phongMaterial.shininess = 0.1;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.19125*255, 0.0735*255, 0.0225*255);
    cookTorrenceMaterial.diffuse = Vec4(0.7038, 0.27048, 0.0828);
    cookTorrenceMaterial.fresnell = Vec4(1.27105,1.67693,1.3164);
    cookTorrenceMaterial.shininess = 0.1;
    return Material(phongMaterial, cookTorrenceMaterial);
}

Material MaterialsLibrary::gold(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.24725*255, 0.1995*255, 0.0745*255);
    phongMaterial.diffuse = Vec4(0.50754, 0.50754, 0.50754);
    phongMaterial.specular = Vec4(0.508273, 0.508273, 0.508273);
    phongMaterial.shininess = 0.4;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.24725*255, 0.1995*255, 0.0745*255);
    cookTorrenceMaterial.diffuse = Vec4(0.50754, 0.50754, 0.50754);
    cookTorrenceMaterial.fresnell = Vec4(1.15943,1.14512, 1.13547);
    cookTorrenceMaterial.shininess = 0.4;
    return Material(phongMaterial, cookTorrenceMaterial);
}

Material MaterialsLibrary::silver(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.19225*255, 0.19225*255, 0.19225*255);
    phongMaterial.diffuse = Vec4(0.50754, 0.50754, 0.50754);
    phongMaterial.specular = Vec4(0.508273, 0.508273, 0.508273);
    phongMaterial.shininess = 0.4;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.19225*255, 0.19225*255, 0.19225*255);
    cookTorrenceMaterial.diffuse = Vec4(0.50754, 0.50754, 0.50754);
    cookTorrenceMaterial.fresnell = Vec4(1.15943,1.14512, 1.13547);
    cookTorrenceMaterial.shininess = 0.4;
    return Material(phongMaterial, cookTorrenceMaterial);
}

/// Based on PVP, polyvinylpyrrolidone
/// \return
Material MaterialsLibrary::black_plastic(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.03*255, 0.03*255, 0.03*255);
    phongMaterial.diffuse = Vec4(0.01, 0.01, 0.01);
    phongMaterial.specular = Vec4(0.50, 0.50, 0.50);
    phongMaterial.shininess = 0.25;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.02*255, 0.02*255, 0.02*255);
    cookTorrenceMaterial.diffuse = Vec4(0.01, 0.01, 0.01);
    cookTorrenceMaterial.fresnell = Vec4(1.5245,1.5299,1.5413);
    cookTorrenceMaterial.shininess = 0.25;
    return Material(phongMaterial, cookTorrenceMaterial);
}
/// Based on PVP, polyvinylpyrrolidone
/// \return
Material MaterialsLibrary::cyan_plastic(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.0*255, 0.1*255, 0.1*255);
    phongMaterial.diffuse = Vec4(0.0, 0.50980392, 0.50980392);
    phongMaterial.specular = Vec4(0.50196078, 0.50196078, 0.50196078);
    phongMaterial.shininess = 0.25;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.0*255, 0.1*255, 0.1*255);
    cookTorrenceMaterial.diffuse = Vec4(0.0, 0.50980392, 0.50980392);
    cookTorrenceMaterial.fresnell = Vec4(1.5245,1.5299,1.5413);
    cookTorrenceMaterial.shininess = 0.25;
    return Material(phongMaterial, cookTorrenceMaterial);
}
/// Based on PVP, polyvinylpyrrolidone
/// \return
Material MaterialsLibrary::green_plastic(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.01*255, 0.1*255, 0.01*255);
    phongMaterial.diffuse = Vec4(0.1, 0.35, 0.1);
    phongMaterial.specular = Vec4(0.45, 0.55, 0.45);
    phongMaterial.shininess = 0.25;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.0*255, 0.1*255, 0.01*255);
    cookTorrenceMaterial.diffuse = Vec4(0.1, 0.35, 0.1);
    cookTorrenceMaterial.fresnell = Vec4(1.5245,1.5299,1.5413);
    cookTorrenceMaterial.shininess = 0.25;
    return Material(phongMaterial, cookTorrenceMaterial);
}
/// Based on PVP, polyvinylpyrrolidone
/// \return
Material MaterialsLibrary::red_plastic(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(.2*255, 0.0*255, 0.0*255);
    phongMaterial.diffuse = Vec4(0.5, 0.0, 0.0);
    phongMaterial.specular = Vec4(0.7, 0.6, 0.6);
    phongMaterial.shininess = 0.25;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(.2*255, 0.0*255, 0.0*255);
    cookTorrenceMaterial.diffuse = Vec4(0.5, 0.0, 0.0);
    cookTorrenceMaterial.fresnell = Vec4(1.5245,1.5299,1.5413);
    cookTorrenceMaterial.shininess = 0.25;
    cookTorrenceMaterial.roughness = .3;
    return Material(phongMaterial, cookTorrenceMaterial);
}
/// Based on PVP, polyvinylpyrrolidone
/// \return
Material MaterialsLibrary::white_plastic(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.2*255, 0.2*255, 0.2*255);
    phongMaterial.diffuse = Vec4(0.55, 0.55, 0.55);
    phongMaterial.specular = Vec4(0.70, 0.70, 0.70);
    phongMaterial.shininess = 0.25;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.2*255, 0.2*255, 0.2*255);
    cookTorrenceMaterial.diffuse = Vec4(0.55, 0.55, 0.55);
    cookTorrenceMaterial.fresnell = Vec4(1.5245,1.5299,1.5413);
    cookTorrenceMaterial.shininess = 0.25;
    return Material(phongMaterial, cookTorrenceMaterial);
}
/// Based on PVP, polyvinylpyrrolidone
/// \return
Material MaterialsLibrary::yellow_plastic(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.15*255, 0.15*255, 0.05*255);
    phongMaterial.diffuse = Vec4(0.5, 0.5, 0.1);
    phongMaterial.specular = Vec4(0.60, 0.60, 0.50);
    phongMaterial.shininess = 0.25;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.15*255, 0.15*255, 0.05*255);
    cookTorrenceMaterial.diffuse = Vec4(0.5, 0.5, 0.0);
    cookTorrenceMaterial.fresnell = Vec4(1.5245,1.5299,1.5413);
    cookTorrenceMaterial.shininess = 0.25;
    return Material(phongMaterial, cookTorrenceMaterial);
}
/// Based on PVP, polyvinylpyrrolidone
/// \return
Material MaterialsLibrary::gray_plastic() {
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.15*255, 0.15*255, 0.15*255);
    phongMaterial.diffuse = Vec4(0.3, 0.3, 0.3);
    phongMaterial.specular = Vec4(0.50, 0.50, 0.50);
    phongMaterial.shininess = 0.25;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.1*255, 0.1*255, 0.1*255);
    cookTorrenceMaterial.diffuse = Vec4(0.3, 0.3, 0.3);
    cookTorrenceMaterial.fresnell = Vec4(1.5245,1.5299,1.5413);
    cookTorrenceMaterial.shininess = 0.25;
    return Material(phongMaterial, cookTorrenceMaterial);
}

///rubber is similar to plastic for refractive indeces
Material MaterialsLibrary::black_rubber(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.02*255, 0.02*255, 0.02*255);
    phongMaterial.diffuse = Vec4(0.02, 0.02, 0.02);
    phongMaterial.specular = Vec4(0.4, 0.4, 0.4);
    phongMaterial.shininess = 0.015625;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.02*255, 0.02*255, 0.02*255);
    cookTorrenceMaterial.diffuse = Vec4(0.02, 0.02, 0.02);
    cookTorrenceMaterial.fresnell = Vec4(1.5245,1.5299,1.5413);
    cookTorrenceMaterial.shininess = 0.015625;
    return Material(phongMaterial, cookTorrenceMaterial);
}

///rubber is similar to plastic for refractive indeces
Material MaterialsLibrary::cyan_rubber(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.0*255, 0.05*255, 0.05*255);
    phongMaterial.diffuse = Vec4(0.4, 0.5, 0.5);
    phongMaterial.specular = Vec4(0.04, 0.7, 0.7);
    phongMaterial.shininess = 0.015625;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.0*255, 0.05*255, 0.05*255);
    cookTorrenceMaterial.diffuse = Vec4(0.4, 0.5, 0.5);
    cookTorrenceMaterial.fresnell = Vec4(1.5245,1.5299,1.5413);
    cookTorrenceMaterial.shininess = 0.015625;
    return Material(phongMaterial, cookTorrenceMaterial);
}

///rubber is similar to plastic for refractive indeces
Material MaterialsLibrary::green_rubber(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.0*255, 0.05*255, 0.0*255);
    phongMaterial.diffuse = Vec4(0.4, 0.5, 0.4);
    phongMaterial.specular = Vec4(0.04, 0.7, 0.7);
    phongMaterial.shininess = 0.015625;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.0*255, 0.05*255, 0.0*255);
    cookTorrenceMaterial.diffuse = Vec4(0.4, 0.5, 0.4);
    cookTorrenceMaterial.fresnell = Vec4(1.5245,1.5299,1.5413);
    cookTorrenceMaterial.shininess = 0.015625;
    return Material(phongMaterial, cookTorrenceMaterial);
}

///rubber is similar to plastic for refractive indeces
Material MaterialsLibrary::red_rubber(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.05*255, 0.0*255, 0.0*255);
    phongMaterial.diffuse = Vec4(0.5, 0.4, 0.4);
    phongMaterial.specular = Vec4(0.7, 0.04, 0.04);
    phongMaterial.shininess = 0.015625;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.05*255, 0.0*255, 0.0*255);
    cookTorrenceMaterial.diffuse = Vec4(0.5, 0.4, 0.4);
    cookTorrenceMaterial.fresnell = Vec4(1.5245,1.5299,1.5413);
    cookTorrenceMaterial.shininess = 0.015625;
    return Material(phongMaterial, cookTorrenceMaterial);
}

///rubber is similar to plastic for refractive indeces
Material MaterialsLibrary::white_rubber(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.15*255, 0.15*255, 0.15*255);
    phongMaterial.diffuse = Vec4(0.5, 0.5, 0.5);
    phongMaterial.specular = Vec4(0.7, 0.7, 0.7);
    phongMaterial.shininess = 0.015625;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.15*255, 0.15*255, 0.15*255);
    cookTorrenceMaterial.diffuse = Vec4(0.5, 0.5, 0.5);
    cookTorrenceMaterial.fresnell = Vec4(1.5245,1.5299,1.5413);
    cookTorrenceMaterial.shininess = 0.015625;
    return Material(phongMaterial, cookTorrenceMaterial);
}

///rubber is similar to plastic for refractive indeces
Material MaterialsLibrary::yellow_rubber(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.05*255, 0.05*255, 0.0*255);
    phongMaterial.diffuse = Vec4(0.5, 0.5, 0.4);
    phongMaterial.specular = Vec4(0.7, 0.7, 0.04);
    phongMaterial.shininess = 0.015625;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.05*255, 0.05*255, 0.0*255);
    cookTorrenceMaterial.diffuse = Vec4(0.5, 0.5, 0.4);
    cookTorrenceMaterial.fresnell = Vec4(1.5245,1.5299,1.5413);
    cookTorrenceMaterial.shininess = 0.015625;
    return Material(phongMaterial, cookTorrenceMaterial);
}

///rubber is similar to plastic for refractive indeces
Material MaterialsLibrary::gray_rubber() {
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0.1*255, 0.1*255, 0.1*255);
    phongMaterial.diffuse = Vec4(0.3, 0.3, 0.3);
    phongMaterial.specular = Vec4(0.4, 0.4, 0.4);
    phongMaterial.shininess = 0.015625;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0.1*255, 0.1*255, 0.1*255);
    cookTorrenceMaterial.diffuse = Vec4(0.3, 0.3, 0.3);
    cookTorrenceMaterial.fresnell = Vec4(1.5245,1.5299,1.5413);
    cookTorrenceMaterial.shininess = 0.015625;
    return Material(phongMaterial, cookTorrenceMaterial);
}
Material MaterialsLibrary::perfect_mirror(){
    PhongMaterial phongMaterial;
    phongMaterial.ambient = Vec4(0,0,0);
    phongMaterial.diffuse = Vec4(0,0,0);
    phongMaterial.specular = Vec4(0,0,0);
    phongMaterial.shininess = .9;
    phongMaterial.specularExponent = phongMaterial.shininess * 128;

    //cook torrance
    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0,0,0);
    cookTorrenceMaterial.diffuse = Vec4(0,0,0);
    cookTorrenceMaterial.fresnell = Vec4(1,1,1);
    cookTorrenceMaterial.shininess = 0.9;
    return Material(phongMaterial, cookTorrenceMaterial);
}


Material MaterialsLibrary::glass() {
    PhongMaterial phongMaterial;
    phongMaterial.relativeSpeed = 1.52;
    phongMaterial.transparency = .72;

    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(1,2,1);
    cookTorrenceMaterial.diffuse = Vec4(0.1,0.1,0.1);
    cookTorrenceMaterial.shininess = .1;
    cookTorrenceMaterial.roughness = .01;
    cookTorrenceMaterial.fresnell = Vec4(1.52,1.52,1.52);
    cookTorrenceMaterial.transparency = .90;

    return Material(phongMaterial, cookTorrenceMaterial);
}

Material MaterialsLibrary::lightSourceGlass(){
    PhongMaterial phongMaterial;
    phongMaterial.relativeSpeed = 1.52;
    phongMaterial.transparency = .72;

    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(0,0,0);
    cookTorrenceMaterial.diffuse = Vec4(0,0,0);
    cookTorrenceMaterial.shininess = 1;
    cookTorrenceMaterial.roughness = .2;
    cookTorrenceMaterial.fresnell = Vec4(1,1,1,1);
    cookTorrenceMaterial.transparency = 1;

    return Material(phongMaterial, cookTorrenceMaterial);
}

Material MaterialsLibrary::water() {
    PhongMaterial phongMaterial;

    CookTorrenceMaterial cookTorrenceMaterial;
    cookTorrenceMaterial.ambient = Vec4(6,3,30);
    cookTorrenceMaterial.diffuse = Vec4(0.1,0.1,0.2);
    cookTorrenceMaterial.shininess = 0.2;
    cookTorrenceMaterial.roughness = .3;
    cookTorrenceMaterial.fresnell = Vec4(1.33,1.33,1.33);
    cookTorrenceMaterial.transparency = 0.8;

    return Material(phongMaterial, cookTorrenceMaterial);
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
    {"perfect_mirror",MaterialsLibrary::perfect_mirror()},
    {"glass",MaterialsLibrary::glass()},
    {"lightSourceGlass",MaterialsLibrary::lightSourceGlass()},
    {"water",MaterialsLibrary::water()},
    });

