//
// Created by Qichen on 9/23/16.
//

#include <cstdlib>
#include "UserInputManager.h"

GLuint indexOfMenuInList = 2;

int pointsChosen,ySize,x1,y1;

static int* windowID;
static bool* isReset;
UserInputManager::UserInputManager(int * window, bool * areKeyFrameSet) {
    windowID = window;
    isReset = areKeyFrameSet;
}

void UserInputManager::mainMenu (int id)
/* This is the callback function for the main menu. */
{
    double lineWidth, color[4];

    switch (id)
    {
        case 1 : /* reset default values */
            glNewList (++indexOfMenuInList, GL_COMPILE_AND_EXECUTE);
            glColor3d (0.0, 0.0, 0.0);
            glLineWidth (1.0);
            glEndList ();
            break;
        case 2 : /* clear the screen */
            glDeleteLists (1, indexOfMenuInList);
            indexOfMenuInList = 2;
            glGetDoublev (GL_LINE_WIDTH, &lineWidth);
            glGetDoublev (GL_CURRENT_COLOR, color);
            glNewList (++indexOfMenuInList, GL_COMPILE);
            glColor4dv (color);
            glLineWidth ((GLfloat) lineWidth);
            glEndList ();
            glutPostRedisplay ();
            break;
        default : /* in case none of the above occur */
            break;
    }
}

void UserInputManager::orientationMenu(int id)
/* This is the callback function for the color menu. */
{
    glNewList (++indexOfMenuInList, GL_COMPILE_AND_EXECUTE);
    switch (id)
    {
        case 1 : //TODO Euler Angle
            break;
        case 2 : //TODO Quaternion
            break;

        default : /* for any case not covered above, leave color unchanged */
            break;
    }
    glEndList ();
    pointsChosen = 0;
}

void UserInputManager::inbetweeningMenu(int id)
/* This is the callback function for the size menu. */
{
    glNewList (++indexOfMenuInList, GL_COMPILE_AND_EXECUTE);
    switch (id)
    {
        case 1 : //TODO Catmul-Rom

            break;
        case 2 : //TODO B-Spline
            break;
        default :
            break;
    }
    glEndList ();
}

void UserInputManager::mouseFunc (int button, int state, int x, int y)
/* This is the callback function that gets executed when a mouse button is pressed. */
{
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
    glutAddMenuEntry ("Reset defaults", 1);
    glutAddMenuEntry ("Clear window", 2);
    glutAttachMenu (GLUT_RIGHT_BUTTON);
}


void UserInputManager::keyboardFunc(unsigned char key, int x, int y) {
    switch ((char) key) {
        case 'a':
            *isReset = true;
            break;
        case 'b':
            *isReset= false;
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
