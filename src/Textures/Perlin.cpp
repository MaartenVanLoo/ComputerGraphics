//
// Created by maart on 28/10/2022.
//

#include <Textures/Perlin.h>
#include <iostream>

const int MRay::Perlin::permutation[] = {
        151,160,137,91,90,15,                 // Hash lookup table as defined by Ken Perlin.  This is a randomly
        131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,    // arranged array of all numbers from 0-255 inclusive.
        190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
        88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
        77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
        102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
        135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
        5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
        223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
        129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
        251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
        49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
        138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,

        151,160,137,91,90,15,
        131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
        190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
        88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
        77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
        102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
        135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
        5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
        223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
        129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
        251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
        49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
        138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180

};

void MRay::Perlin::setSeed(int seed) {
    Perlin::seed = seed;
}

int MRay::Perlin::hash(int u) {
    return permutation[u];
}

int MRay::Perlin::hash(const int u, const int v) {
    return permutation[permutation[u]+v];
}

int MRay::Perlin::hash(const int u, const int v, const int w) {
    return permutation[permutation[permutation[u]+v]+w];
}

double MRay::Perlin::grad(int hash, const double u, const double v, const double w) {
    switch (hash & 0xF){
        case 0x0: return  u +  v;
        case 0x1: return -u +  v;
        case 0x2: return  u + -v;
        case 0x3: return -u + -v;
        case 0x4: return  u +  w;
        case 0x5: return -u +  w;
        case 0x6: return  u + -w;
        case 0x7: return -u + -w;
        case 0x8: return  v +  w;
        case 0x9: return -v +  w;
        case 0xA: return  v + -w;
        case 0xB: return -v + -w;
        case 0xC: return  v +  u;
        case 0xD: return -v +  w;
        case 0xE: return  v + -u;
        case 0xF: return -v + -w;
        default: return 0;
    }
}

void MRay::Perlin::setProfile(MRay::Profile *p) {
    delete this->profile;
    this->profile = p;
}

void MRay::Perlin::setRoughness(double roughness) {
    this->roughness = roughness;
}

void MRay::Perlin::setDetails(int details) {
    this->details = details;
}

MRay::Perlin::~Perlin() {
    delete this->profile;
    this->profile = nullptr;
}

MRay::Perlin::Perlin() {
    this->profile = new Profile();
}

void MRay::Perlin::setStretch(double stretch) {
    this->stretch = stretch;
}

void MRay::Perlin::setScale(const MRay::Vec3 &scale) {
    this->scale = scale;
}

double MRay::Perlin3D::compute(double u, double v, double w) {
    double total = 0;
    double freq = 1;
    double amplitude = 1;
    int octaves = this->details;
    double relTransparancy = this->roughness/100;

    double maxValue = 0; //used for normalizing
    do{
        amplitude = (octaves>=0)?amplitude:double(octaves+10)/10*amplitude;
        double val = this->perlin(u*freq*this->stretch*scale.get<0>(), v * freq*scale.get<1>(), w*freq*scale.get<2>());
        // to 0 -> 1 range
        val = (val + 1)/2;
        //val *= this->profile->f(val);
        total += val*amplitude;

        //std::cout << "octaves " << octaves << "\tval " << val << "\tamplitude " << amplitude << "\tfreq " << freq << "\ttransparancy " << relTransparancy << "\tprofile " << this->profile->type()  <<"\n";

        maxValue += amplitude;

        freq*=2;
        amplitude *= relTransparancy;
        octaves-=10;
    }while(octaves >= 0 && amplitude >0.001);
    return total/maxValue;
}
double MRay::Perlin3D::perlin(double u, double v, double w) {
    u = abs(u);
    v = abs(v);
    w = abs(w);
    int ui = (int)u & 255;
    int vi = (int)v & 255;
    int wi = (int)w & 255;

    double x = u -(int)u;
    double y = v -(int)v;
    double z = w -(int)w;



    double ufade = Perlin::fade(x);
    double vfade = Perlin::fade(y);
    double wfade = Perlin::fade(z);

    int aaa, aab, aba, baa, abb, bab, bba, bbb;
    aaa = Perlin::hash(ui,        vi,        wi);
    aab = Perlin::hash(ui,        vi,        inc(wi));
    aba = Perlin::hash(ui,        inc(vi),wi);
    abb = Perlin::hash(ui,        inc(vi),inc(wi));
    baa = Perlin::hash(inc(ui),vi,        wi);
    bab = Perlin::hash(inc(ui),vi,        inc(wi));
    bba = Perlin::hash(inc(ui),inc(vi),wi);
    bbb = Perlin::hash(inc(ui),inc(vi),inc(wi));


    double value = lerp(wfade,
        lerp(vfade,
             lerp(ufade,
                  grad(aaa, x,y,z),
                  grad(baa, x-1,y,z)),
             lerp(ufade,
                  grad(aba, x, y-1, z),
                  grad(bba,x-1,y-1,z))
        ),
        lerp(vfade,
             lerp(ufade,
                  grad(aab, x,y,z-1),
                  grad(bab, x-1,y,z-1)),
             lerp(ufade,
                  grad(abb, x, y-1, z-1),
                  grad(bbb,x-1,y-1,z-1))
         )
    );
    return value;
}

MRay::Perlin3D::Perlin3D() :Perlin(){
    this->profile = new Profile();
}

void MRay::PerlinPlot::plot(MRay::Perlin3D& perlin, double scaleX, double scaleY, double scaleZ, double z) {
    cv::Mat image = cv::Mat::zeros(cv::Size(255,255),CV_8UC1);

    uchar min = 255;
    uchar max = 0;
    for (int x = 0; x < 255; x++){
        for (int y = 0; y < 255; y++){
            uchar & color = image.at<uchar>(y,x);
            //std::cout << perlin.compute(x*scaleX/xhigh,y*scaleY/yhigh, z*scaleZ) << "\n";

            color = static_cast<uchar>((perlin.compute((x+0.5)*scaleX,(y+.5)*scaleY, (z+.5)*scaleZ)*255));
            //std::cout << ((int)color) << "\n";
            if (min > color) min = color;
            if (max < color) max = color;
        }
    }
    std::cout << "min:" << int(min) << "\n";
    std::cout << "max:" << int(max) << "\n";
    cv::imshow("Perlin3D", image);
    cv::waitKey();
}

void MRay::PerlinPlot::plot(MRay::Perlin3D& perlin1,MRay::Perlin3D& perlin2, double scaleX, double scaleY, double scaleZ, double z) {
    cv::Mat image = cv::Mat::zeros(cv::Size(255*4,255*4),CV_8UC1);

    uchar min = 255;
    uchar max = 0;
    for (int k = 0; k < 8; k++){
        std::cout << (k/4+1) << ',' << (k%4+1) << "\n";
        for (int x = 0; x < 255; x++){
            for (int y = 0; y < 255; y++){
                uchar & color = image.at<uchar>(y+k/4*255,x+k%4*255);

                //std::cout << perlin.compute(x*scaleX/xhigh,y*scaleY/yhigh, z*scaleZ) << "\n";



                int c = int((perlin1.compute((x+0.5)*scaleX,(y+.5)*scaleY, (z+.5)*scaleZ) +
                        perlin2.compute((x+0.5)*scaleX,(y+.5)*scaleY, (z+.5)*scaleZ)) * 255 / 2);
                color = static_cast<uchar>(c);
                //std::cout << ((int)color) << "\n";
                if (min > color) min = color;
                if (max < color) max = color;
            }
        }
    }
    std::cout << "min:" << int(min) << "\n";
    std::cout << "max:" << int(max) << "\n";
    cv::imshow("Perlin3D", image);
    cv::waitKey();
}


double MRay::Wave::f(double x) {
    //std::cout << "wave\n";
    return std::sin(this->freq * x)*0.5+0.5;
}

MRay::Wave::Wave(double freq) : freq(freq) {}
