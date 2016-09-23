//
// Created by Qichen on 9/22/16.
//

#include "MatrixGenerator.h"


float* MatrixGenerator::generateFromEulerAngle(float* eulerAngle, float* coordinates){
    static float m[] ={ 1.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, -10.0f, 1.0f };
    return  m;
}