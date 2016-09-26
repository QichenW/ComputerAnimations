//
// Created by Qichen on 9/26/16.
//

#ifndef GLUTPROJECT_INTERPOLATIONHELPER_H
#define GLUTPROJECT_INTERPOLATIONHELPER_H

#if defined(__APPLE__)
#include <GLUT/glut.h>
#include <string>
#include <vector>

#else
#include <GL/glut.h>
#endif
using namespace std;
class InterpolationHelper {

public:
    //TODO implement solutions for more than 4 points, now hard coded to allow only 4 key frames
    const static int NUMBER_OF_CONTROL_POINTS = 4;
    static void calculateCoefficientMatrix(GLfloat dest[4][3], int interpolationMode, float **controlPoints);

    static void calculateCoefficientMatrix(GLfloat (*dest)[3], int interpolationMode,
                                           int orientationMode, float **controlPoints);
};


#endif //GLUTPROJECT_INTERPOLATIONHELPER_H
