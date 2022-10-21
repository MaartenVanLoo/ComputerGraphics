//
// Created by Maarten Van Loo on 7/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_MATERIAL_H
#define I_COMPUTERGRAPHICS_MATERIAL_H

#include <Light/Color3.h>
#include <LinearAlgebra/Vector.h>
#include <Utils/Options.h>

namespace MRay {

    struct PhongMaterial{
        Vec4 ambient = Vec4();
        Vec4 diffuse= Vec4();
        Vec4 specular= Vec4();
        float specularExponent = 0;
        float shininess = 0;
    };

    struct CookTorrenceMaterial{
        Vec4 ambient = Vec4();
        Vec4 diffuse = Vec4();
        Vec4 fresnell = Vec4();
        float shininess = 0;
    };

    class Material {
    public:
        Material();

        Material(float ambR, float ambG, float ambB,
                 float diffR, float diffG, float diffB,
                 float specR, float specG, float specB,
                 float shininess,
                 float nR, float nG, float nB);

        Material(double ambR, double ambG, double ambB,
                 double diffR, double diffG, double diffB,
                 double specR, double specG, double specB,
                 double shininess,
                 double nR, double nG, double nB);

        //phong model
        Vec3 ambient;
        Vec3 diffuse;
        Vec3 specular;
        float specularExponent;
        Color3 emissive = Color3();

        //Cook-Torrance model => RGB can be different
        Vec4 fresnell;

        //Reflection & transmission
        float shininess = 0;

        //Color3 color = Color3(0, 0, 0);

        template<ShaderTypes T>
        Vec4 getAmbient(){
            switch (T) {
                case ShaderTypes::Phong:
                    return phongMaterial.ambient;
                case ShaderTypes::CookTorrance:
                    return cookTorrenceMaterial.ambient;
            }
        }

        template<ShaderTypes T>
        Vec4 getDiffuse(){
            switch (T) {
                case ShaderTypes::Phong:
                    return phongMaterial.diffuse;
                case ShaderTypes::CookTorrance:
                    return cookTorrenceMaterial.diffuse;
            }
        }

        template<ShaderTypes T>
        Vec4 getSpecular(){
            switch (T){
                case ShaderTypes::Phong:
                    return phongMaterial.specular;
                case ShaderTypes::CookTorrance:
                    throw std::invalid_argument("No material known for this shader type " + toString<T>() + ".");
            }
        }
        template<ShaderTypes T>
        float getSpecularExponent(){
            switch (T){
                case ShaderTypes::Phong:
                    return phongMaterial.specularExponent;
                case ShaderTypes::CookTorrance:
                    throw std::invalid_argument("No material known for this shader type " + toString<T>() + ".");
            }
        }

        template<ShaderTypes T>
        float getShininess(){
            switch (T) {
                case ShaderTypes::Phong:
                    return phongMaterial.shininess;
                case ShaderTypes::CookTorrance:
                    return cookTorrenceMaterial.shininess;
            }
        }

    private:
        PhongMaterial phongMaterial;
        CookTorrenceMaterial cookTorrenceMaterial;
    };


}
#endif //I_COMPUTERGRAPHICS_MATERIAL_H
