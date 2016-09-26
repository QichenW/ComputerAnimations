//
// Created by Qichen on 9/26/16.
//

#include <iostream>
#include "InterpolationHelper.h"


/****
 * Get the coefficentMatrix
 * @param dest
 * @param basisMatrix
 * @param controlPoints
 */
void InterpolationHelper::calculateCoefficientMatrix(float (*dest)[3], const float (*basisMatrix)[4],
                                                     float **controlPoints) {
    int i,j,k;
    for (i = 0; i < NUMBER_OF_CONTROL_POINTS; i++){
        for (j = 0; j < 3; j++){
            dest[i][j] = 0;
            for (k = 0;  k< NUMBER_OF_CONTROL_POINTS; k++){
                dest[i][j] += basisMatrix[i][k] * controlPoints[k][j];
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
