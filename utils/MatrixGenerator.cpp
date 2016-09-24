//
// Created by Qichen on 9/22/16.
//

#include "MatrixGenerator.h"
/* sine cosine */
#include <math.h>
#include <algorithm>

#include <iostream>
using namespace std;

static float transformationMatrix[4][4] ={};
static float flattenedTransformationMatrix[16] ={};

float* MatrixGenerator::generateFrameFromEulerAngle(float *eulerAngle, float *coordinates){
    float translationX = *coordinates;
    float translationY = *(coordinates + 1);
    float translationZ = *(coordinates + 2);
    initTransformationMatrixAsIdentity();
    //TODO debug only
    printTransformationMatrix();

    getHomogeneousWithEulerAngle(eulerAngle);

    transformationMatrix[0][3] += translationX;
    transformationMatrix[1][3] += translationY;
    transformationMatrix[2][3] += translationZ;
    //TODO debug only
    printTransformationMatrix();
    static float m[] ={ 1.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, -10.0f, 1.0f };
    int i,j;
    for(i = 0; i < 4; i++){
        for (j=0; j< 4; j++){
            flattenedTransformationMatrix[i * 4 + j] = transformationMatrix[i][j];
        }
    }
    return  flattenedTransformationMatrix;
}

void MatrixGenerator::getHomogeneousWithEulerAngle(float * eulerAngle) {
    /**
     * pitch, yaw, roll
     * */
    float pitch = (float) M_PI / 180 * (*eulerAngle);
    float yaw = (float) M_PI / 180 * ( *(eulerAngle +1));
    float roll = (float) M_PI / 180 * ( *(eulerAngle +2));

    float homogeneousPitch[4][4] = {}, homogeneousYaw[4][4] ={},homogeneousRoll[4][4] = {};

    initEulerAngleMatrices((float *)homogeneousPitch, (float *)homogeneousYaw, (float *)homogeneousRoll);


    // rotation pitch
    homogeneousPitch[1][1] = cosf(pitch);
    homogeneousPitch[2][2] = cosf(pitch);
    homogeneousPitch[1][2] = -1 * sinf(pitch);
    homogeneousPitch[2][1] = sinf(pitch);
    // rotation yaw
    homogeneousYaw[0][0] = cosf(yaw);
    homogeneousYaw[2][2] = cosf(yaw);
    homogeneousYaw[0][2] = sinf(yaw);
    homogeneousYaw[2][0] = -1 * sinf(yaw);
    // rotation roll
    homogeneousRoll[0][0] = cosf(roll);
    homogeneousRoll[1][1] = cosf(roll);
    homogeneousRoll[0][1] = -1 * sinf(roll);
    homogeneousRoll[1][0] = sinf(roll);

    // multiply the transformation matrix with three rotation matrices
    applyRotation(homogeneousPitch);
    //TODO debug only
    printTransformationMatrix();
    applyRotation(homogeneousYaw);
    //TODO debug only
    printTransformationMatrix();
    applyRotation(homogeneousRoll);

    //TODO debug only
    printTransformationMatrix();
}

/**
 * matrices multiplication
 * **/
void MatrixGenerator::applyRotation(float rotationMatrix[4][4]) {
    // temporarily hold the result
    float tempMatrix[4][4] ={};
    int i,j,m;
    for (i = 0; i < 4; i++){
        for(j =0; j< 4; j++){
            for (m = 0; m < 4; m++){
                tempMatrix[i][j] += *(rotationMatrix[i]+m) * transformationMatrix[m][j];
                //tempMatrix[i][j] = rotationMatrix[i][m] * transformationMatrix[m][j];
            }
        }
    }

    std::copy(&tempMatrix[0][0], &tempMatrix[0][0] + 16, &transformationMatrix[0][0]);
}

/**
 * Initialize the Euler Angle matrices as identity matrices
 * **/
void MatrixGenerator::initEulerAngleMatrices(float * matrix1, float * matrix2, float * matrix3) {

    std::copy(&transformationMatrix[0][0], &transformationMatrix[0][0] + 16, matrix1);
    std::copy(&transformationMatrix[0][0], &transformationMatrix[0][0] + 16, matrix2);
    std::copy(&transformationMatrix[0][0], &transformationMatrix[0][0] + 16, matrix3);
}

/**
 * Initialize the transformation matrix as an identity matrix
 * **/
void MatrixGenerator::initTransformationMatrixAsIdentity() {
    int i,j;
    for(i = 0; i < 4; i++) {
        for (j =0; j< 4; j++){
            if ( i == j) {
                transformationMatrix[i][j] = 1;
            } else {
                transformationMatrix[i][j] = 0;
            }
        }
    }
}

void MatrixGenerator::printTransformationMatrix() {
    int i,j;
    for(i = 0; i < 4; i++) {
        for (j =0; j< 4; j++){
            cout<< transformationMatrix[i][j];
                cout <<" ";
        }
        cout <<" "<<endl;
    }
    cout<<"transformationMatrix printed"<<endl;
}
