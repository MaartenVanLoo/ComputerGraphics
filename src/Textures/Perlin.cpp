//
// Created by maart on 28/10/2022.
//

#include <Textures/Perlin.h>
#include <iostream>
#include <iomanip>
#include <Utils/Stopwatch.h>

#pragma region permutation
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
#pragma endregion


#pragma region Perlin

MRay::Perlin::Perlin() {
}

MRay::Perlin::~Perlin() {
}

#pragma region getters & setters
void MRay::Perlin::setSeed(int seed) {
    this->seed = 0; //reset seed;
    this->seed = pearsonHash(seed); //compute new seed
}
void MRay::Perlin::setScale(const MRay::Vec3 &scale) {
    this->scale = scale;
}
void MRay::Perlin::setOctaves(int octaves) {
    this->octaves = octaves;
}
void MRay::Perlin::setRoughness(double roughness) {
    this->roughness = roughness;
}

#pragma endregion

#pragma region interpolation
double MRay::Perlin::lerp(double t, double a, double b){
    return a + t * (b - a);
}
MRay::Vec3 MRay::Perlin::lerp(MRay::Vec3 a, MRay::Vec3 b, double t){
    return a + t * (b - a);
}
double MRay::Perlin::map(double value, double start1, double stop1, double start2, double stop2){
    return start2 + (value - start1) * (stop2-start2)/(stop1-start1);
}
#pragma endregion

#pragma region hashing
int MRay::Perlin::pearsonHash(int value) const {
    int hash = this->seed;
    unsigned char const * p = reinterpret_cast<unsigned char const *>(&value);

    for (std::size_t i = 0; i != sizeof(float); ++i)
    {
        hash ^= permutation[p[i]];
    }
    return hash;
}
int MRay::Perlin::hash(int u) const{
    return this->pearsonHash(u);
}

int MRay::Perlin::hash(int u, int v) const{
    return this->pearsonHash(this->pearsonHash(u)+v);
}

int MRay::Perlin::hash(int u, int v, int w) const{
    return this->pearsonHash(this->pearsonHash(this->pearsonHash(u)+v)+w);
}

#pragma endregion


double MRay::Perlin::grad(int hash, const double u) {
    switch (hash & 0x1) {
        case 0x0: return u;   // (1   )
        case 0x1: return -u;   // (-1  )
        default:  return 0;
    }
}
double MRay::Perlin::grad(int hash, const double u, const double v){
    switch (hash & 0x3){
        case 0x0: return  u +  v;   // (1  ,1  )
        case 0x1: return -u +  v;   // (-1 ,1  )
        case 0x2: return  u + -v;   // (1  ,-1 )
        case 0x3: return -u + -v;   // (-1 ,-1 )
        default: return 0;
    }
}
double MRay::Perlin::grad(int hash, const double u, const double v, const double w) {
    switch (hash & 0xF){
        case 0x0: return  u +  v;   // (1  ,1  ,0 )
        case 0x1: return -u +  v;   // (-1 ,1  ,0 )
        case 0x2: return  u + -v;   // (1  ,-1 ,0 )
        case 0x3: return -u + -v;   // (-1 ,-1 ,0 )
        case 0x4: return  u +  w;   // (1  ,0  ,1 )
        case 0x5: return -u +  w;   // (-1 ,0  ,1 )
        case 0x6: return  u + -w;   // (1  ,0  ,-1)
        case 0x7: return -u + -w;   // (-1 ,0  ,-1)
        case 0x8: return  v +  w;   // (0  ,1  ,1 )
        case 0x9: return -v +  w;   // (0  ,-1 ,1 )
        case 0xA: return  v + -w;   // (0  ,1  ,-1)
        case 0xB: return -v + -w;   // (0  ,-1 ,-1)

        case 0xC: return  v +  u;   // (1  ,1  ,0 )
        case 0xD: return -v +  w;   // (0  ,-1 ,1 )
        case 0xE: return  v + -u;   // (-1 ,1  ,0 )
        case 0xF: return -v + -w;   // (0  ,-1 ,-1)
        default: return 0;
    }
}

double MRay::Perlin::fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}
double MRay::Perlin::dfade(double t) {
    //derivative of fade
    return 30.0*t*t*(t*(t-2.0)+1.0);
}
int MRay::Perlin::inc(int v) {
    return v+=1;
}


#pragma endregion

#pragma region Perlin1D
double MRay::Perlin1D::compute(double u) const{
    double total = 0;
    double freq = 1;
    double amplitude = 1;
    int octaves = this->octaves;

    double maxValue = 0; //used for normalizing
    do{
        double val = this->perlin(u*freq);
        total += val*amplitude;
        maxValue += amplitude;
        freq*=2;
        amplitude *= this->roughness;
        octaves--;
    }while(octaves >= 0 && amplitude >0.001);
    return total/maxValue;
}

MRay::Vec2 MRay::Perlin1D::computeGradient(double u) const {
    Vec2 total = Vec2(0,0);
    double freq = 1;
    double amplitude = 1;
    int octaves = this->octaves;

    double maxValue = 0;
    do {
        Vec2 val = this->perlinGradient(u*freq);
        total += val*amplitude;
        maxValue += amplitude;
        freq*=2;
        amplitude *= this->roughness;
        octaves--;
    }while(octaves >= 0 && amplitude > 0.001);
    return total/maxValue;
}

double MRay::Perlin1D::perlin(double u) const{
    u = u*this->scale.get<0>();

    int ui = (int)std::floor(u);

    double x = u -std::floor(u);

    double ufade = Perlin::fade(x);

    //gradients
    int ga,gb;
    ga = this->hash(ui); //ga
    gb = this->hash(inc(ui)); //gb


    double value = lerp(ufade,
                 grad(ga, x ),   //va
                 grad(gb, x-1)); //vb
    assert(value <= 1);
    assert(value >= -1);
    return value;
}

MRay::Vec2 MRay::Perlin1D::perlinGradient(double u) const {
    u = u*this->scale.get<0>();

    int ui = (int)std::floor(u);

    double x = u -std::floor(u);

    double fu = Perlin::fade(x);
    double dfu = Perlin::fade(x);

    //gradients
    int ga,gb;
    ga = this->hash(ui); //ga
    gb = this->hash(inc(ui)); //gb
    double va = grad(ga, x );
    double vb = grad(gb, x-1);

    double value = lerp(fu,va,vb);
    assert(value <= 1);
    assert(value >= -1);

    /*
     * Computing analytical gradients:
     * lerp(u,a,b)  with lerp(t,a,b) = a * (1- t) + b * t
     * <=> a * (1-u) + b* u
     * <=> a - ua + bu
     * du = u'(b-a)
     * u' = dfade()
     */
    double du = dfu * (vb - va);

    return Vec2(value, du);
}

#pragma endregion

#pragma region Perlin2D
double MRay::Perlin2D::compute(double u, double v) const {
    double total = 0;
    double freq = 1;
    double amplitude = 1;
    int octaves = this->octaves;

    double maxValue = 0; //used for normalizing
    do{
        double val = this->perlin(u*freq, v * freq);
        total += val*amplitude;
        maxValue += amplitude;
        freq*=2;
        amplitude *= this->roughness;
        octaves--;
    }while(octaves >= 0 && amplitude >0.001);
    return total/maxValue;
}

MRay::Vec3 MRay::Perlin2D::computeGradient(double u, double v) const{
    Vec3 total = Vec3(0,0,0);
    double freq = 1;
    double amplitude = 1;
    int octaves = this->octaves;

    double maxValue = 0;
    do {
        Vec3 val = this->perlinGradient(u*freq, v*freq);
        total += val*amplitude;
        maxValue += amplitude;
        freq*=2;
        amplitude *= this->roughness;
        octaves--;
    }while(octaves >= 0 && amplitude > 0.001);
    return total/maxValue;
}

double MRay::Perlin2D::perlin(double u, double v) const{
    u = u*this->scale.get<0>();
    v = v*this->scale.get<1>();

    int ui = (int)std::floor(u);
    int vi = (int)std::floor(v);

    double x = u -std::floor(u);
    double y = v -std::floor(v);

    double ufade = Perlin::fade(x);
    double vfade = Perlin::fade(y);

    int aa, ab, ba, bb;

    //gradients
    aa = this->hash(ui,        vi        ); //ga
    ab = this->hash(ui,        inc(vi)); //gb
    ba = this->hash(inc(ui),vi        ); //gc
    bb = this->hash(inc(ui),inc(vi)); //gd


    double value = lerp(vfade,
                lerp(ufade,
                     grad(aa, x,  y),   //va
                     grad(ba, x-1,y)),  //vb
                lerp(ufade,
                     grad(ab, x,  y-1),  //vc
                     grad(bb, x-1,y-1)) //vd
                     );
    assert(value <= 1);
    assert(value >= -1);
    return value;
}

//https://www.shadertoy.com/view/XdXBRH
MRay::Vec3 MRay::Perlin2D::perlinGradient(double u, double v) const{
    u = u*this->scale.get<0>();
    v = v*this->scale.get<1>();

    int ui = (int)std::floor(u);
    int vi = (int)std::floor(v);

    double x = u -std::floor(u);
    double y = v -std::floor(v);

    double uf = Perlin::fade(x);
    double vf = Perlin::fade(y);
    double duf = Perlin::dfade(x);
    double dvf = Perlin::dfade(y);

    int aa, ab, ba, bb;
    //gradients
    aa = this->hash(ui,        vi        ); //ga
    ab = this->hash(ui,        inc(vi)); //gb
    ba = this->hash(inc(ui),vi        ); //gc
    bb = this->hash(inc(ui),inc(vi)); //gd

    double va = grad(aa, x,  y);
    double vb = grad(ba, x-1,y);
    double vc = grad(ab, x,  y-1);
    double vd = grad(bb, x-1,y-1);

    double value = lerp(vf,
                        lerp(uf,
                             grad(aa, x,  y),   //va
                             grad(ba, x-1,y)),  //vb
                        lerp(uf,
                             grad(ab, x,  y-1), //vc
                             grad(bb, x-1,y-1)) //vd
    );
    /*
     * Computing analytical gradients:
     * lerp(v,lerp(u,a,b),lerp(u,c,d))  with lerp(t,a,b) = a * (1- t) + b * t
     * lerp(v,   a * (1 - u) + b * u,    c * (1 - u) + d * u)
     * <=> (a - au + bu) * (1-v) + (c-cu +du) * v
     * <=> a - au + bu - va + vau - bvu + cv - cvu + dvu
     * <=> a + u(b-a) + v (c-a) + vu(a - b - c + d)
     *
     * du = u'(b-a) + v * u'(a-b-c+d)
     * dv = v'(c-a) + v' * u(a-b-c+d)
     * u' = dfade()
     * v' = dfade()
     */
    double du = duf*(vb - va ) + vf * duf * (va - vb - vc + vd);
    double dv = dvf*(vc - va ) + dvf * uf * (va - vb - vc + vd);

    return Vec3(value,du, dv);
}
#pragma endregion

#pragma region Perlin3D
double MRay::Perlin3D::compute(double u, double v, double w) const{
    double total = 0;
    double freq = 1;
    double amplitude = 1;
    int octaves = this->octaves;

    double maxValue = 0; //used for normalizing
    do{
        double val = this->perlin(u*freq, v * freq, w*freq);
        total += val*amplitude;
        maxValue += amplitude;
        freq*=2;
        amplitude *= this->roughness;
        octaves--;
    }while(octaves >= 0 && amplitude >0.001);
    return total/maxValue;
}

MRay::Vec4 MRay::Perlin3D::computeGradient(double u, double v, double w) const {
    Vec4 total = Vec4();
    double freq = 1;
    double amplitude = 1;
    int octaves = this->octaves;

    double maxValue = 0; //used for normalizing
    do{
        Vec4 val = this->perlinGradient(u*freq, v * freq, w*freq);
        total += val*amplitude;
        maxValue += amplitude;
        freq*=2;
        amplitude *= this->roughness;
        octaves--;
    }while(octaves >= 0 && amplitude >0.001);
    return total/maxValue;
}

double MRay::Perlin3D::perlin(double u, double v, double w) const{
    u = u*this->scale.get<0>();
    v = v*this->scale.get<1>();
    w = w*this->scale.get<2>();

    int ui = (int)std::floor(u);
    int vi = (int)std::floor(v);
    int wi = (int)std::floor(w);

    double x = u -std::floor(u);
    double y = v -std::floor(v);
    double z = w -std::floor(w);

    double ufade = Perlin::fade(x);
    double vfade = Perlin::fade(y);
    double wfade = Perlin::fade(z);

    int aaa, aab, aba, baa, abb, bab, bba, bbb;
    aaa = this->hash(ui,        vi,        wi);           // ga
    aab = this->hash(ui,        vi,        inc(wi));   // gb
    aba = this->hash(ui,        inc(vi),wi);           // gc
    abb = this->hash(ui,        inc(vi),inc(wi));   // gd
    baa = this->hash(inc(ui),vi,        wi);           // ge
    bab = this->hash(inc(ui),vi,        inc(wi));   // gf
    bba = this->hash(inc(ui),inc(vi),wi);           // gg
    bbb = this->hash(inc(ui),inc(vi),inc(wi));   // gh


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

MRay::Vec4 MRay::Perlin3D::perlinGradient(double u, double v, double w) const {
    //TODO: implement
    u = u*this->scale.get<0>();
    v = v*this->scale.get<1>();
    w = w*this->scale.get<2>();

    int ui = (int)std::floor(u);
    int vi = (int)std::floor(v);
    int wi = (int)std::floor(w);

    double x = u -std::floor(u);
    double y = v -std::floor(v);
    double z = w -std::floor(w);

    double fu = Perlin::fade(x);
    double fv = Perlin::fade(y);
    double fw = Perlin::fade(z);
    double dfu = Perlin::dfade(x);
    double dfv = Perlin::dfade(y);
    double dfw = Perlin::dfade(z);

    int aaa, aab, aba, baa, abb, bab, bba, bbb;
    aaa = this->hash(ui,        vi,        wi);           // ga
    aab = this->hash(ui,        vi,        inc(wi));   // gb
    aba = this->hash(ui,        inc(vi),wi);           // gc
    abb = this->hash(ui,        inc(vi),inc(wi));   // gd
    baa = this->hash(inc(ui),vi,        wi);           // ge
    bab = this->hash(inc(ui),vi,        inc(wi));   // gf
    bba = this->hash(inc(ui),inc(vi),wi);           // gg
    bbb = this->hash(inc(ui),inc(vi),inc(wi));   // gh

    double va = grad(aaa, x,y,z);
    double vb = grad(baa, x-1,y,z);
    double vc = grad(aba, x, y-1, z);
    double vd = grad(bba,x-1,y-1,z);
    double ve = grad(aab, x,y,z-1);
    double vf = grad(bab, x-1,y,z-1);
    double vg = grad(abb, x, y-1, z-1);
    double vh = grad(bbb,x-1,y-1,z-1);

    double value = lerp(fw,
                        lerp(fv,
                             lerp(fu,
                                  grad(aaa, x,y,z),
                                  grad(baa, x-1,y,z)),
                             lerp(fu,
                                  grad(aba, x, y-1, z),
                                  grad(bba,x-1,y-1,z))
                        ),
                        lerp(fv,
                             lerp(fu,
                                  grad(aab, x,y,z-1),
                                  grad(bab, x-1,y,z-1)),
                             lerp(fu,
                                  grad(abb, x, y-1, z-1),
                                  grad(bbb,x-1,y-1,z-1))
                        )
    );

    /*
    * Computing analytical gradients:
    * lerp(w, lerp(v,lerp(u,a,b),lerp(u,c,d)),lerp(v,lerp(u,e,f),lerp(u,g,h)))  with lerp(t,a,b) = a * (1- t) + b * t
    * lerp(w, lerp(v,   a * (1 - u) + b * u,    c * (1 - u) + d * u), lerp(v,   e * (1 - u) + f * u,    g * (1 - u) + h * u)
    * lerp(w, //TODO: finish
    * <=> (a - au + bu) * (1-v) + (c-cu +du) * v
    * <=> a - au + bu - va + vau - bvu + cv - cvu + dvu
    * <=> a + u(b-a) + v (c-a) + vu(a - b - c + d)
    *
    * du = u'(b-a) + v * u'(a-b-c+d)
    * dv = v'(c-a) + v' * u(a-b-c+d)
    * u' = dfade()
    * v' = dfade()
    */
    double du = 0;
    double dv = 0;
    double dw = 0;
    return Vec4(value, u, dv, dw);
}
#pragma endregion





#pragma region Plot

MRay::PerlinPlot::PerlinPlot(int screenwidth, int screenheight) : screenwidth(screenwidth),
                                                                  screenheight(screenheight) {}

void MRay::PerlinPlot::plot(MRay::Perlin2D& perlin, double minX, double maxX, double minY, double maxY){
    Stopwatch stopwatch = Stopwatch();
    stopwatch.start();
    cv::Mat image = cv::Mat::zeros(cv::Size(this->screenwidth,this->screenheight),CV_8UC1);

    double minV = 255;
    double maxV = 0;
    for (int x = 0; x < this->screenwidth; x++){
        for (int y = 0; y < this->screenheight; y++){
            uchar & color = image.at<uchar>(y,x);
            //std::cout << perlin.compute(x*scaleX/xhigh,y*scaleY/yhigh, z*scaleZ) << "\n";
            double mapx = Perlin::map(x,0,this->screenwidth,minX, maxX);
            double mapy = Perlin::map(y,0,this->screenheight,minY, maxY);
            color = static_cast<uchar>(((perlin.compute(mapx,mapy)+1)*255/2));
            //std::cout << ((int)color) << "\n";
            if (minV > color) minV = color;
            if (maxV < color) maxV = color;
        }
    }
    //stretch to image contrast back to [0 , 255] from [min,max]
    for (int x = 0; x < this->screenwidth; x++){
        for (int y = 0; y < this->screenheight; y++){
            uchar & color = image.at<uchar>(y,x);
            color = static_cast<uchar>(Perlin::map(color, minV, maxV, 0, 255));
        }
    }
    stopwatch.stop();
    std::cout << stopwatch;
    std::cout << "min:" << int(minV) << "\n";
    std::cout << "max:" << int(maxV) << "\n";
    cv::imshow("Perlin2D", image);
    cv::waitKey(1);
    cv::imwrite("perlin2D.png", image);
    //gradient
    stopwatch.reset();
    stopwatch.start();
    image = cv::Mat::zeros(cv::Size(this->screenwidth,this->screenheight),CV_8UC3);

    minV = 255;
    maxV = -255;
    for (int x = 0; x < this->screenwidth; x++){
        for (int y = 0; y < this->screenheight; y++){
            cv::Vec3b & color = image.at<cv::Vec3b>(y,x);
            //std::cout << perlin.compute(x*scaleX/xhigh,y*scaleY/yhigh, z*scaleZ) << "\n";
            double mapx = Perlin::map(x,0,this->screenwidth,minX, maxX);
            double mapy = Perlin::map(y,0,this->screenheight,minY, maxY);
            Vec3 value = perlin.computeGradient(mapx, mapy);
            color[0] = //static_cast<uchar>((value.get<0>()+1)*255/2);
            color[1] = static_cast<uchar>(std::min(abs(value.get<1>())*128,255.0f));
            color[2] = static_cast<uchar>(std::min(abs(value.get<2>())*128,255.0f));
            if (minV > value.get<2>()) minV = value.get<2>();
            if (maxV < value.get<2>()) maxV = value.get<2>();
        }
    }
    stopwatch.stop();
    std::cout << stopwatch;
    cv::imshow("Perlin2D Gradient", image);
    cv::imwrite("perlin2D_gradient.png", image);
    cv::waitKey();
}
void MRay::PerlinPlot::plot(MRay::Perlin3D& perlin, double minX, double maxX, double minY, double maxY, double z) {
    Stopwatch stopwatch = Stopwatch();
    stopwatch.start();
    cv::Mat image = cv::Mat::zeros(cv::Size(this->screenwidth,this->screenheight),CV_8UC1);

    uchar min = 255;
    uchar max = 0;
    for (int x = 0; x < this->screenwidth; x++){
        for (int y = 0; y < this->screenheight; y++){
            uchar & color = image.at<uchar>(y,x);
            //std::cout << perlin.compute(x*scaleX/xhigh,y*scaleY/yhigh, z*scaleZ) << "\n";
            double mapx = Perlin::map(x,0,this->screenwidth,minX, maxX);
            double mapy = Perlin::map(y,0,this->screenheight,minY, maxY);
            color = static_cast<uchar>(((perlin.compute(mapx,mapy, z)+1)*255/2));
            if (min > color) min = color;
            if (max < color) max = color;
        }
    }
    //stretch to image contrast back to [0 , 255] from [min,max]
    for (int x = 0; x < this->screenwidth; x++){
        for (int y = 0; y < this->screenheight; y++){
            uchar & color = image.at<uchar>(y,x);
            color = static_cast<uchar>(Perlin::map(color,min,max,0, 255));
        }
    }
    stopwatch.stop();
    std::cout << "min:" << int(min) << "\n";
    std::cout << "max:" << int(max) << "\n";
    std::cout << stopwatch;
    cv::imshow("Perlin3D", image);
    cv::waitKey();
}


#pragma endregion





double MRay::Wave::f(double x) {
    //std::cout << "wave\n";
    return std::sin(this->freq * x)*0.5+0.5;
}

MRay::Wave::Wave(double freq) : freq(freq) {}
