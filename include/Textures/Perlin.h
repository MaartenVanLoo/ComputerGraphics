//
// Created by maart on 28/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_PERLIN_H
#define I_COMPUTERGRAPHICS_PERLIN_H

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "LinearAlgebra/Vector.h"

namespace MRay{
    //source:http://adrianb.io/2014/08/09/perlinnoise.html

//used as preprocessor for perlin noise
    class Profile{
    public:
        virtual ~Profile() {

        }

        virtual double f(double x){
            //std::cout << "linear\n";
            return x;
        };
        virtual std::string type(){
            return "linear";
        }
    };
    class Wave : public Profile{
    public:
        explicit Wave(double freq);

        double f(double x);

        virtual std::string type(){
            return "wave";
        }
    private:
        double freq = 1;
    };


    class Perlin{
    public:
        Perlin();
        virtual ~Perlin();

        void setSeed(int seed);
        void setProfile(Profile *profile);

        void setRoughness(double roughness);

        void setDetails(int details);

        void setStretch(double stretch);

        void setScale(const Vec3 &scale);


        static double lerp(double t, double a, double b){
            return a + t * (b - a);
        }
        static Vec3 lerp(Vec3 a, Vec3 b, double t){
            return a + t * (b - a);
        }
    protected:
        const static int permutation[];
        static int hash(const int u);
        static int hash(const int u, const int v);
        static int hash(const int u, const int v, const int w);
        static double grad(int hash, const double u){return 0.0;};
        static double grad(int hash, const double u, const double v){return 0.0;};
        static double grad(int hash, const double u, const double v, const double w);
        static double fade(double t){
            return t * t * t * (t * (t * 6 - 15) + 10);
        }

        static int inc(int v) {
            return v+=1;
        }

        static double mod289(double x)
        {
            return x - floor(x * (1.0 / 289.0)) * 289.0;
        }
        static double permute(double x)
        {
            return mod289(((x*34.0)+1.0)*x);
        }


        int seed;
        double roughness = 100; //rougher = slower decrease in transparancy for increasing octaves
        int details = 110; // 0 = 1 octave, 10 = 2 octaves, 20 = 3 octaves , 27 = 4 octaves, last with 70% visiblity
        double stretch = 1;
        Vec3 scale = Vec3(1,1,1);
        Profile* profile = nullptr;
    };
    class Perlin1D : public Perlin{
    public:
        double compute(double u) const{
            int ui = (int)u & 255;

            int a, b;
            a = hash(ui);
            b = hash(this->inc(ui));

            return 0.0;
        };
    };
    class Perlin2D : public Perlin{
    public:
        double compute(double u, double v)const {
            int ui = (int)u & 255;
            int vi = (int)v & 255;

            int aa, ab, ba, bb;
            aa = hash(ui,vi);
            ab = hash(ui,inc(vi));
            ba = hash(inc(ui),vi);
            bb = hash(ui,inc(vi));

            return 0.0;
        };
    };
    class Perlin3D : public Perlin{
    public:
        Perlin3D();

        double compute(double u, double v, double w);

        double perlin(double u, double v, double w);
    };


    //plot perlin for testing purpose
    class PerlinPlot{
    public:
/*        void plot(Perlin1D perlin, int samples, double scale){
            cv::Mat image = cv::Mat::zeros(cv::Size(screenwidth,screenheight),CV_8UC1);

            cv::imshow("Perlin1D", image);
        };

        void plot(Perlin2D perlin, int samples, double scaleX, double scaleY){
            cv::Mat image = cv::Mat::zeros(cv::Size(screenwidth,screenheight),CV_8UC1);
            int xhigh = int(double(samples)/double(screenheight));
            int yhigh = int(double(samples)/double(screenwidth));
            for (int x = 0; x < xhigh; x++){
                for (int y = 0; y < yhigh; y++){
                    uchar & color = image.at<uchar>(y,x);
                    color = static_cast<uchar>(perlin.compute(x*scaleX,y*scaleY));
                }
            }
            cv::imshow("Perlin2D", image);
        };
*/
        //draw a 2d image sampled at height z
        void plot(Perlin3D& perlin, double scaleX, double scaleY, double scaleZ, double z);
        void plot(Perlin3D& perlin1,Perlin3D& perlin2, double scaleX, double scaleY, double scaleZ, double z);
    private:
        int screenwidth = 1280;
        int screenheight = 720;
    };
}
#endif //I_COMPUTERGRAPHICS_PERLIN_H
