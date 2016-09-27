//
// Created by Qichen on 9/26/16.
//

#include <iostream>
#include <cmath>
#include "InterpolationHelper.h"

static const GLfloat basisCatmullMatrix[4][4] = {
        {(const GLfloat) -0.5, 1.5, (const GLfloat) -1.5, 0.5},
        {1,                    (const GLfloat) -2.5, 2,  (const GLfloat) -0.5},
        {(const GLfloat) -0.5, 0,                    0.5,   0},
        {0, 1, 0, 0}
};
static const GLfloat basisBsplineMatrix[4][4] = {
        {(const GLfloat) (-1/6.0), 0.5, (const GLfloat) -0.5, (const GLfloat) (1/6.0)},
        {0.5,                    -1, 0.5,  0},
        {(const GLfloat) -0.5, 0,                    0.5,   0},
        {(const GLfloat) (1/6.0), (const GLfloat) (4/6.0), (const GLfloat) (1/6.0), 0}
};
/****
 * Get the coefficentMatrix
 * @param dest
 * @param interpolationMode
 * @param controlPoints
 */
void InterpolationHelper::calculateCoefficientMatrix(GLfloat (*dest)[3], int interpolationMode, float **controlPoints) {
    int i,j,k;
    for (i = 0; i < NUMBER_OF_CONTROL_POINTS; i++){
        for (j = 0; j < 3; j++){
            dest[i][j] = 0;
            for (k = 0;  k< NUMBER_OF_CONTROL_POINTS; k++){
                if (interpolationMode == 0) {
                    //use catmull-rom for interpolation
                    dest[i][j] += basisCatmullMatrix[i][k] * controlPoints[k][j];
                } else {
                    // use b-spline
                    dest[i][j] += basisBsplineMatrix[i][k] * controlPoints[k][j];
                }
            }
        }
    }

    //TODO for debug only
    for (i = 0; i < 4; i++) {
        for (j = 0; j< 3; j++) {
            cout<< dest[i][j] << '\t';
        }
        cout<< '\n';
    }

}

void InterpolationHelper::calculateCoefficientMatrix(GLfloat (*dest)[3], int interpolationMode,
                                                     int orientationMode, float **controlPoints) {
    if (orientationMode == 0) {
        // if the orientation is presented with euler angle, use the same function as for translation matrix
        calculateCoefficientMatrix(dest, interpolationMode, controlPoints);
    } else {
        //TODO implement the version for quaternion
    }

}

//TODO test this
/****
 * This function prepares the time vector
 * @param tVector the address of the vector to store the time vector elements
 * @param t the current time ranging from 0 to 1
 */
void InterpolationHelper::prepareTimeVector(GLfloat *tVector, GLfloat t) {
    *tVector = (GLfloat) pow(t, 3);
    *(tVector + 1) = (GLfloat) pow(t,2);
    *(tVector + 2) = t;
    *(tVector + 3) = 1;
}

//TODO test this
/****
 *
 * @param trans the address of the vector to store translation vector
 * @param tVector the time vector
 * @param coefficientMatrix the coefficient matrix
 */
void InterpolationHelper::prepareTranslationOrEulerAngleVector(GLfloat *trans, GLfloat *tVector,
                                                               GLfloat coefficientMatrix[4][3]) {
    int i,j;
    for(i = 0; i < 3; i++) {
        *(trans + i) = 0;
        for (j = 0; j < 4; j++) {
            *(trans + i) += *(tVector + j) * (*(coefficientMatrix + j))[i];
        }
    }

}

//TODO implement this
void
InterpolationHelper::prepareQuaternionVector(GLfloat *quaternion, GLfloat *tVector, GLfloat (*coefficientMatrix)[4]) {

}
