//
// Created by Qichen on 9/26/16.
//

#ifndef GLUTPROJECT_INTERPOLATIONHELPER_H
#define GLUTPROJECT_INTERPOLATIONHELPER_H

using namespace std;
class InterpolationHelper {

public:
    const static int NUMBER_OF_CONTROL_POINTS = 4;
    static void calculateCoefficientMatrix(float dest[4][3], const float basisMatrix[4][4], float **controlPoints);
};


#endif //GLUTPROJECT_INTERPOLATIONHELPER_H
