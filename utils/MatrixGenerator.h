//
// Created by Qichen on 9/22/16.
//

#ifndef GLUTPROJECT_MATRIXGENERATOR_H
#define GLUTPROJECT_MATRIXGENERATOR_H
// glut
#if defined(__APPLE__)

#include <GLUT/glut.h>
#include <string>
#include <vector>

#else
#include <GL/glut.h>
#endif

class MatrixGenerator
{
public:
    static float* generateFromEulerAngle(float* eulerAngle, float* coordinates);
};
#endif //GLUTPROJECT_MATRIXGENERATOR_H
