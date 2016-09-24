//
// Created by Qichen on 9/24/16.
//

#ifndef GLUTPROJECT_USERINTERFACEMANAGER_H
#define GLUTPROJECT_USERINTERFACEMANAGER_H

// glut
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class UserInterfaceManager {
public:
    static void renderString(int interpolationChosen, int orientationChosen, bool arePointsSet);
};


#endif //GLUTPROJECT_USERINTERFACEMANAGER_H
