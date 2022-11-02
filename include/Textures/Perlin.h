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
        void setRoughness(double roughness);
        void setScale(const Vec3 &scale);
        void setOctaves(int octaves);

        static double lerp(double t, double a, double b);
        static Vec3 lerp(Vec3 a, Vec3 b, double t);
        /// Maps a value form 1 range to the other range
        /// \param value  the incoming value to be converted
        /// \param start1 lower bound of the value's current range
        /// \param stop1  upper bound of the value's current range
        /// \param start2 lower bound of the value's target range
        /// \param stop2  upper bound of the value's target range
        /// \return
        static double map(double value, double start1, double stop1, double start2, double stop2);


    protected:
        int pearsonHash(int value) const;
        const static int permutation[];
        int hash(int u) const ;
        int hash(int u, int v) const ;
        int hash(int u, int v, int w) const;

        static double grad(int hash, const double u){return 0.0;};
        static double grad(int hash, const double u, const double v);
        static double grad(int hash, const double u, const double v, const double w);

        static double fade(double t){
            return t * t * t * (t * (t * 6 - 15) + 10);
        }
        static double dfade(double t){
            //derivative of fade
            return 30.0*t*t*(t*(t-2.0)+1.0);
        }
        static int inc(int v) {
            return v+=1;
        }


        int seed = 0;
        double roughness = 1; //rougher = slower decrease in transparancy for increasing octaves
        int octaves = 11;
        Vec3 scale = Vec3(1,1,1);
    };
    class Perlin1D : public Perlin{
    public:
        /// Compute fractal perlin noise with given settings at point [u,v]
        /// \param u 1st coordinate of noise.
        /// \return noise value in range [-1,1]
        double compute(double u)const;
        /// Compute fractal perlin noise and its gradients with given settings at point [u,v]
        /// \param u 1st coordinate of noise.
        /// \return Vector with 3 values, 1st is perlin noise in range [-1,1], 2nd = gradient with respect to u, 3th = gradient with respect to v.
        Vec2 computeGradient(double u)const;

        /// Compute perlin noise with given scale at point [u,v]
        /// \param u 1st coordinate of noise.
        /// \return noise value in range [-1,1]
        double perlin(double u) const;
        /// Compute perlin noise and its gradients with given scale at point [u,v]
        /// \param u 1st coordinate of noise.
        /// \return Vector with 3 values, 1st is perlin noise in range [-1,1], 2nd = gradient with respect to u, 3th = gradient with respect to v.
        Vec2 perlinGradient(double u) const;
    };
    class Perlin2D : public Perlin{
    public:
        Perlin2D(){};

        /// Compute fractal perlin noise with given settings at point [u,v]
        /// \param u 1st coordinate of noise.
        /// \param v 2nd coordinate of noise.
        /// \return noise value in range [-1,1]
        double compute(double u, double v)const;
        /// Compute fractal perlin noise with given settings at point [u,v]
        /// \param vec Vector with [u,v] value of point.
        /// \return noise value in range [-1,1]
        double compute(Vec2 vec) const{return 0.0;}; //todo, try to accelerate with vectors //TODO: add intrinsics vec2 & vec3
        /// Compute fractal perlin noise and its gradients with given settings at point [u,v]
        /// \param u 1st coordinate of noise.
        /// \param v 2nd coordinate of noise.
        /// \return Vector with 3 values, 1st is perlin noise in range [-1,1], 2nd = gradient with respect to u, 3th = gradient with respect to v.
        Vec3 computeGradient(double u, double v)const;
        /// Compute fractal perlin noise and its gradients with given settings at point [u,v]
        /// \param vec Vector with [u,v] value of point.
        /// \return Vector with 3 values, 1st is perlin noise in range [-1,1], 2nd = gradient with respect to u, 3th = gradient with respect to v.
        Vec3 computeGradient(Vec2 vec){return Vec3();}; //todo, try to accelerate with vectors //TODO: add intrinsics vec2 & vec3

        /// Compute perlin noise with given scale at point [u,v]
        /// \param u 1st coordinate of noise.
        /// \param v 2nd coordinate of noise.
        /// \return noise value in range [-1,1]
        double perlin(double u, double v) const;
        /// Compute perlin noise with given scale at point [u,v]
        /// \param vec Vector with [u,v] value of point.
        /// \return noise value in range [-1,1]
        double perlin(Vec2 vec) const{return 0.0;}; //todo, try to accelerate with vectors  //TODO: add intrinsics vec2 & vec3
        /// Compute perlin noise and its gradients with given scale at point [u,v]
        /// \param u 1st coordinate of noise.
        /// \param v 2nd coordinate of noise.
        /// \return Vector with 3 values, 1st is perlin noise in range [-1,1], 2nd = gradient with respect to u, 3th = gradient with respect to v.
        Vec3 perlinGradient(double u, double v) const;
        /// Compute perlin noise and its gradients with given scale at point [u,v]
        /// \param vec Vector with [u,v] value of point.
        /// \return Vector with 3 values, 1st is perlin noise in range [-1,1], 2nd = gradient with respect to u, 3th = gradient with respect to v.
        Vec3 perlinGradient(Vec2 vec){return Vec3();}; //todo, try to accelerate with vectors //TODO: add intrinsics vec2 & vec3
    };

    class Perlin3D : public Perlin{
    public:
        Perlin3D(){};

        /// Compute fractal perlin noise with given settings at point [u,v,w]
        /// \param u 1st coordinate of noise.
        /// \param v 2nd coordinate of noise.
        /// \param w 3th coordinate of noise.
        /// \return noise value in range [-1,1]
        double compute(double u, double v, double w) const;
        /// Compute fractal perlin noise with given settings at point [u,v,w]
        /// \param vec Vector with [u,v,w] value of point.
        /// \return noise value in range [-1,1]
        double compute(Vec3 vec) const{return 0.0; }; //todo, try to accelerate with vectors //TODO: add intrinsics vec2 & vec3
        /// Compute fractal perlin noise and its gradients with given settings at point [u,v,w]
        /// \param u 1st coordinate of noise.
        /// \param v 2nd coordinate of noise.
        /// \param w 3th coordinate of noise.
        /// \return Vector with 4 values, 1st is perlin noise in range [-1,1], 2nd = gradient with respect to u, 3th = gradient with respect to v, 4th = gradient with respect to w.
        Vec4 computeGradient(double u, double v, double w) const;
        /// Compute fractal perlin noise and its gradients with given settings at point [u,v,w]
        /// \param vec Vector with [u,v,w] value of point.
        /// \return Vector with 4 values, 1st is perlin noise in range [-1,1], 2nd = gradient with respect to u, 3th = gradient with respect to v, 4th = gradient with respect to w.
        Vec4 computeGradient(Vec3 vec) const {return Vec4();}; //todo, try to accelerate with vectors //TODO: add intrinsics vec2 & vec3

        /// Compute perlin noise with given scale at point [u,v,w]
        /// \param u 1st coordinate of noise.
        /// \param v 2nd coordinate of noise.
        /// \param w 3th coordinate of noise.
        /// \return noise value in range [-1,1]
        double perlin(double u, double v, double w) const;
        /// Compute perlin noise with given scale at point [u,v,w]
        /// \param vec Vector with [u,v,w] value of point.
        /// \return noise value in range [-1,1]
        double perlin(Vec3 vec) const {return 0.0;}; //todo, try to accelerate with vectors //TODO: add intrinsics vec2 & vec3
        /// Compute perlin noise and its gradients with given scale at point [u,v]
        /// \param u 1st coordinate of noise.
        /// \param v 2nd coordinate of noise.
        /// \param w 3th coordinate of noise.
        /// \return Vector with 4 values, 1st is perlin noise in range [-1,1], 2nd = gradient with respect to u, 3th = gradient with respect to v, 4th = gradient with respect to w.
        Vec4 perlinGradient(double u, double v, double w) const;
        /// Compute perlin noise and its gradients with given scale at point [u,v]
        /// \param vec Vector with [u,v,w] value of point.
        /// \return Vector with 4 values, 1st is perlin noise in range [-1,1], 2nd = gradient with respect to u, 3th = gradient with respect to v, 4th = gradient with respect to w.
        Vec4 perlinGradient(Vec3 vec){return Vec4();}; //todo, try to accelerate with vectors //TODO: add intrinsics vec2 & vec3
    };


    //plot perlin for testing purpose
    class PerlinPlot{
    public:
        PerlinPlot(int screenwidth, int screenheight);

        //draw a 2d image sampled at height z
        void plot(Perlin2D& perlin, double minX, double maxX, double minY, double maxY);
        void plot(Perlin3D& perlin, double minX, double maxX, double minY, double maxY, double z);
private:
        int screenwidth = 1280;
        int screenheight = 720;
    };

}
#endif //I_COMPUTERGRAPHICS_PERLIN_H
