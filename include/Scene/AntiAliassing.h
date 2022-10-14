//
// Created by maart on 11/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_ANTIALIASSING_H
#define I_COMPUTERGRAPHICS_ANTIALIASSING_H


#include <vector>
#include <Render/Shader.h>

namespace MRay {

    class SuperSampling {
    public:
        explicit SuperSampling(Shader *shader) : shader(shader) {};

        virtual ~SuperSampling() {
            delete this->top;
            delete this->bottom;
        }


    private:
        double computeGradient(Color3 &topLeft, Color3 &topRight, Color3 &bottomLeft, Color3 &bottomRight) {
            return 0.0;
        };

        void sample(int x_min, int x_max, int y_min, int y_max) {
            this->top->clear();
            this->bottom->clear();
            this->top->reserve(x_max - x_min);
            this->bottom->reserve(x_max - x_min);


            for (int y = y_min; y < y_max; y++) {
                if (y == y_min) top->push_back(this->shader->shade(x_min, y));
                bottom->push_back(this->shader->shade(x_min, y));
                for (int x = x_min; x < x_max; x++) {
                    if (y == y_min) top->push_back(this->shader->shade(x + 1, y));
                    bottom->push_back(this->shader->shade(x + 1, y + 1));

                    //4 corners have been computed:
                    // top.back()-1, top.back()
                    // bottom.back()-1, top.back()

                    //compute gradient?
                    double gradient = computeGradient(*(top->end() - 1), *(top->end()), *(bottom->end() - 1),
                                                      *(bottom->end()));
                    double threshold = 10;
                    if (gradient < threshold) {
                        //todo: sample more of the shader
                    }

                    //color = avg:
                    Color3 color
                }
                //set top as new bottom
                top = bottom;
                //clear bottom
                bottom->clear();
            }
        }

    private:
        Shader *shader = nullptr;
        std::vector<Color3> *top = new std::vector<Color3>();
        std::vector<Color3> *bottom = new std::vector<Color3>();
    }

}
#endif //I_COMPUTERGRAPHICS_ANTIALIASSING_H
