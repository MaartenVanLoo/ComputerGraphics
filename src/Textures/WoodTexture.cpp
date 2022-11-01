//
// Created by maart on 29/10/2022.
//

#include <Textures/WoodTexture.h>
#include "Light/Color3.h"
#include "Transform/Transform.h"

using namespace MRay;
MRay::Vec3 MRay::WoodTexture::compute(float x, float y, float z, float scale) {
    Vec3 color1 = Vec3(0.658*255,0.356*255,0.0588*255);
    Vec3 color2 = Vec3(0.952*255,0.713*255,0.470*255);

    double turbulenceFactor = 0.2;
    double rings = 7;
    double distValue = sqrt(x * x + y * y) + 0.3 * turbulence.compute(x, y, 0);
    double sineValue = 128.0 * fabs(sin(2 * rings * distValue * 3.14159 - z*z));
    Vec3 diffuse = Vec3(80 + sineValue,30 + sineValue,30);//double turb = turbulence.compute(t2.get<0>(), t2.get<1>(), t2.get<2>())*255;
    //if (x > 0 && y > 0){
    //    std::cout << "test\n";
    //}
    double turb = turbulence.compute(x, y, 0);
    //diffuse = Vec3(turb,turb,turb);
    return diffuse;
}

WoodTexture::WoodTexture() {
    noise1 = Perlin3D();
    turbulence = Perlin3D();
    //turbulence.setRoughness(20);
    //turbulence.setScale(Vec3(32,32,32));
}

void WoodTexture::preview(double x0, double x1, double y0, double y1) {
    cv::Mat image = cv::Mat::zeros(cv::Size(255*4,255*4),CV_8UC3);

    for (int i = 0; i < 1; i++){
        for (int j = 0; j < 1; j++){

    double z = (i*3+j);
    for (int x = 0; x < 512; x++){
        for (int y = 0; y < 512; y++){
            cv::Vec3b & color = image.at<cv::Vec3b>(y+i*512,x+j*512);

            Vec4 p = Vec4(x,y,z,1);
            p = AffineTransform::rotateX(1.1) * p;
            Color3 c = Color3(this->compute(x0+p.get<_X>()*(x1-x0)/255,y0 + p.get<_Y>()*(y1-y0)/255,p.get<_Z>(),0));
            color[0] = static_cast<unsigned char>(c.getBlue());
            color[1] = static_cast<unsigned char>(c.getGreen());
            color[2] = static_cast<unsigned char>(c.getRed());
        }
    }

        }
    }

    cv::imshow("Wood Texture", image);
    cv::waitKey();

}
