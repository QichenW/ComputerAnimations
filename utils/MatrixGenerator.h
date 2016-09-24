//
// Created by Qichen on 9/22/16.
//

#ifndef GLUTPROJECT_MATRIXGENERATOR_H
#define GLUTPROJECT_MATRIXGENERATOR_H
// glut
#if defined(__APPLE__)

#include <GLUT/glut.h>

#else
#include <GL/glut.h>
#endif

class MatrixGenerator
{
public:
    static float* generateFrameFromEulerAngle(float *eulerAngle, float *coordinates);
private:
    static void getHomogeneousWithEulerAngle(float *eulerAngle);
    static void initTransformationMatrixAsIdentity();

    static void initEulerAngleMatrices(float * matrix1, float * matrix2, float * matrix3);

    static void applyRotation(float rotationMatrix[4][4]);

    static void printTransformationMatrix();
};
#endif //GLUTPROJECT_MATRIXGENERATOR_H
