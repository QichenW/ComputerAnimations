//
// Created by Qichen on 9/23/16.
//

#include <cstdlib>
#include <setup/Preferences.h>
#include "UserInputManager.h"

GLuint indexOfMenuInList = 2;

int pointsChosen,ySize,x1,y1;

static int* windowID;
Preferences *prefsPointer;
UserInputManager::UserInputManager(int * window, Preferences* preferences) {
    windowID = window;
    prefsPointer = preferences;
}

void UserInputManager::mainMenu (int id)
/* This is the callback function for the main menu. */
{
    double lineWidth, color[4];

    switch (id)
    {
        case 1 : /* TODO reset default values */

            break;
        case 2 : /* TODO start animation */

            break;
        default :
            break;
    }
}

void UserInputManager::orientationMenu(int id)
/* This is the callback function for the color menu. */
{
    glNewList (++indexOfMenuInList, GL_COMPILE_AND_EXECUTE);
    switch (id)
    {
        case 1 :
            (*prefsPointer).setOrientationMode(EULER_ANGLE_MODE);
            break;
        case 2 :
            (*prefsPointer).setOrientationMode(QUATERNION_MODE);
            break;

        default : /* for any case not covered above, leave color unchanged */
            break;
    }
    glEndList ();
    pointsChosen = 0;
}

void UserInputManager::inbetweeningMenu(int id) {
    glNewList (++indexOfMenuInList, GL_COMPILE_AND_EXECUTE);
    switch (id)
    {
        case 1 :
            (*prefsPointer).setInterpolationMode(CATMULL_ROM_MODE);
            break;
        case 2 :
            (*prefsPointer).setInterpolationMode(B_SPLINE_MODE);
            break;
        default :
            break;
    }
    glEndList ();
}

void UserInputManager::mouseFunc (int button, int state, int x, int y) {
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
        if (pointsChosen == 0)
        {
            x1 = x;
            y1 = ySize - y;
            pointsChosen = 1;
        }
        else
        {
            glNewList (++indexOfMenuInList, GL_COMPILE_AND_EXECUTE);
            glBegin (GL_LINES);
            glVertex2i (x1, y1);
            glVertex2i (x, ySize-y);
            glEnd ();
            glEndList ();
            //TODO figure out what above lines do
            glFlush ();
            pointsChosen = 0;
        }
}

void UserInputManager::createMouseMenu() {
    int orientation_menu, inbetweening_menu;
    orientation_menu = glutCreateMenu(orientationMenu);
    glutAddMenuEntry ("Euler Angle", 1);
    glutAddMenuEntry ("Quaternion", 2);
    inbetweening_menu = glutCreateMenu(UserInputManager::inbetweeningMenu);
    glutAddMenuEntry ("Catmul-Rom", 1);
    glutAddMenuEntry ("B-splines", 2);
    glutCreateMenu (UserInputManager::mainMenu);
    glutAddSubMenu ("Orientation", orientation_menu);
    glutAddSubMenu ("Inbetweening", inbetweening_menu);
    glutAddMenuEntry ("Reset", 1);
    glutAddMenuEntry ("Start", 2);
    glutAttachMenu (GLUT_RIGHT_BUTTON);
}


void UserInputManager::keyboardFunc(unsigned char key, int x, int y) {
    switch ((char) key) {
        case 'a':
            (*prefsPointer).setKeyFramesSet(true);
            break;
        case 'b':
            (*prefsPointer).setKeyFramesSet(false);
            break;
        case 'q':
        case 'Q':
        case 27:    /* ESC */
            glutDestroyWindow(*windowID);
            exit(0);
        default:
            break;
    }
    return;
}
