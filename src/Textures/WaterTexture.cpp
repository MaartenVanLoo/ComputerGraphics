//
// Created by Maarten Van Loo on 2/11/2022.
//

#include "Textures/WaterTexture.h"

MRay::WaterTexture::WaterTexture(MRay::Vec3& scale) {
    noise.setScale(scale);
}

MRay::WaterTexture::WaterTexture(double su, double sv) {
    noise.setScale(Vec3(su,sv,1.0));
    noise.setOctaves(9);
    noise.setRoughness(0.8);

}
