//
// Created by Qichen on 9/24/16.
//

#include "Preferences.h"


Preferences::Preferences() {
    keyFramesSet = false;
    pointsSet = false;
    interpolationMode = -1;
    orientationMode = -1;
}

// setters
void Preferences::setKeyFramesSet(bool value) {
    keyFramesSet = value;
}

void Preferences::setPointsSet(bool value) {
    pointsSet = value;
}

void Preferences::setInterpolationMode(int mode) {
    interpolationMode = mode;
}

void Preferences::setOrientationMode(int mode) {
    orientationMode = mode;
}

// getters
bool Preferences::areKeyFramesSet() {
    return keyFramesSet;
}

int Preferences::getOrientationMode() {
    return orientationMode;
}

int Preferences::getInterpolationMode() {
    return interpolationMode;
}

bool Preferences::arePointsSet() {
    return pointsSet;
}
