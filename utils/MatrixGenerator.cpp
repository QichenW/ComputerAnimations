//
// Created by Qichen on 9/22/16.
//

#include "MatrixGenerator.h"


float* MatrixGenerator::generateFromEulerAngle(float* eulerAngle, float* coordinates){
    return   (float[]) { 1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 2.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, 0.0f, -10.0f, 1.0f };
}