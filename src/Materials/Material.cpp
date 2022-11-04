//
// Created by Maarten Van Loo on 7/10/2022.
//

#include "Materials/Material.h"
using namespace MRay;


Material::Material() {

}


Material::Material(PhongMaterial &phong, CookTorrenceMaterial &cook): phongMaterial(phong), cookTorrenceMaterial((cook)){}

