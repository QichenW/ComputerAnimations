//
// Created by Qichen on 9/24/16.
//

#include <iostream>
#include "Preferences.h"


Preferences::Preferences() {
    resetPreferences();
}

// setters
void Preferences::setKeyFramesLoaded(bool value) {
    areKeyFramesLoaded = value;
}

void Preferences::setInterpolationMode(int mode) {
    interpolationMode = mode;
}

void Preferences::setOrientationMode(int mode) {
    orientationMode = mode;
}

// getters
bool Preferences::setKeyFrameLoaded() {
    return areKeyFramesLoaded;
}

int Preferences::getOrientationMode() {
    return orientationMode;
}

int Preferences::getInterpolationMode() {
    return interpolationMode;
}

void Preferences::resetPreferences() {
    areKeyFramesLoaded = false;
    interpolationMode = -1;
    orientationMode = -1;
    keyFrameAmount = 0;
}


void Preferences::setKeyFrameAmount(int i) {
    keyFrameAmount = i;
    listOfPositions = new GLfloat*[i];
    listOfEulerAngle = new GLfloat*[i];
    listOfQuaternion = new GLfloat*[i];
}

int Preferences::getKeyFrameAmount() const {
    return keyFrameAmount;
}

void Preferences::addOnePosition(int index, GLfloat x, GLfloat y, GLfloat z) {
    listOfPositions[index] = new GLfloat[3];
    listOfPositions[index][0] = x;
    listOfPositions[index][1] = y;
    listOfPositions[index][2] = z;
}

void Preferences::addOneEulerAngle(int index, GLfloat pitch, GLfloat yaw, GLfloat roll) {
    listOfEulerAngle[index] = new GLfloat[3];
    listOfEulerAngle[index][0] = pitch;
    listOfEulerAngle[index][1] = yaw;
    listOfEulerAngle[index][2] = roll;
}

/****
 * print out the infomation for debug purposes
 */
void Preferences::printLoadedPreferences() {
    cout<< "number of key frames: "<< keyFrameAmount<<endl;
    cout<< "orientation / interpolation: "<< orientationMode << '/' << interpolationMode <<endl;
    int i ,j ;
    float l;
    for(i = 0; i < keyFrameAmount; i++) {
        for(j = 0; j < 3; j++) {
        l =listOfPositions[i][j];
            cout<< l << '\t';
        }
        cout<< '\n';
    }
    cout<< '\n';
    for(i = 0; i < keyFrameAmount; i++) {
        for(j = 0; j < 3; j++) {
            l =listOfEulerAngle[i][j];
            cout<< l << '\t';
        }
        cout<< '\n';
    }

}


