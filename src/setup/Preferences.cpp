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

void Preferences::setInterpolationMode(int interpolationMode) {
    interpolationMode = interpolationMode;
}

void Preferences::setOrientationMode(int orientationMode) {
    orientationMode = orientationMode;
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
