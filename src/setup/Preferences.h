//
// Created by Qichen on 9/24/16.
//

#ifndef GLUTPROJECT_PREFERENCEMANAGER_H
#define GLUTPROJECT_PREFERENCEMANAGER_H


class Preferences {
    /****
    * mode:
    * // orientationMode    -1: not chosen, 0 : euler angle, 1 : quaternion
    * // interpolationMode  -1: not chosen, 0 : Catmull-Rom, 1 : B-spline
    */
private:
    bool keyFramesSet, pointsSet;
    int interpolationMode, orientationMode;

public:
    Preferences();

    bool areKeyFramesSet();

    int getOrientationMode();

    int getInterpolationMode();

    bool arePointsSet();

    void setKeyFramesSet(bool value);

    void setPointsSet(bool value);

    void setInterpolationMode(int mode);

    void setOrientationMode(int mode);


};


#endif //GLUTPROJECT_PREFERENCEMANAGER_H
