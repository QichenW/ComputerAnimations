//
// Created by Qichen on 9/23/16.
//

#include <cstdlib>
#include <setup/Preferences.h>
#include <nfd.h>
#include <setup/SetupFileLoader.h>
#include "UserInputManager.h"

GLuint indexOfMenuInList = 2;

static int pointsChosen,ySize,x1,y1;
static int* windowID;

Preferences *prefsPointer;

UserInputManager::UserInputManager(int * window, Preferences* preferences) {
    windowID = window;
    prefsPointer = preferences;
}

void UserInputManager::mainMenu (int id){
    switch (id)
    {
        case 1: /* TODO  test if matrix is correct */
            // choose the user provided text file in a "native file dialog"
            prefsPointer->setKeyFramesLoaded(loadUserInputFromFileDialog());
            // then calculate the coefficient matrices for interpolation use
            prefsPointer->calculateCoefficientMatrices();
            break;
        //reset the preferences
        case 2 :
            prefsPointer->resetPreferences();
            break;
        case 3 : /* TODO  test if start animation */
            prefsPointer->setIsPlaying(true);

            break;
        default :
            break;
    }
}

/** sub-menus not implemented for now **/
//void UserInputManager::orientationMenu(int id){
//    //Foolproof, do not respond if the status message does not suggest you to choose
//    if((*prefsPointer).areBothOptionSelected()){
//        return;
//    }
//    glNewList (++indexOfMenuInList, GL_COMPILE_AND_EXECUTE);
//    switch (id) {
//        case 1 :
//            (*prefsPointer).setOrientationMode(EULER_ANGLE_MODE);
//            break;
//        case 2 :
//            (*prefsPointer).setOrientationMode(QUATERNION_MODE);
//            break;
//
//        default : /* for any case not covered above, leave color unchanged */
//            break;
//    }
//    glEndList ();
//    pointsChosen = 0;
//}
//
//void UserInputManager::inbetweeningMenu(int id) {
//    //Foolproof, do not respond if the status message does not suggest you to choose
//    if((*prefsPointer).areBothOptionSelected()){
//        return;
//    }
//    glNewList (++indexOfMenuInList, GL_COMPILE_AND_EXECUTE);
//    switch (id)
//    {
//        case 1 :
//            (*prefsPointer).setInterpolationMode(CATMULL_ROM_MODE);
//            break;
//        case 2 :
//            (*prefsPointer).setInterpolationMode(B_SPLINE_MODE);
//            break;
//        default :
//            break;
//    }
//    glEndList ();
//}

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

    glutCreateMenu (UserInputManager::mainMenu);

/** sub-menus not implemented for now **/
//    int orientation_menu = glutCreateMenu(orientationMenu);
//    glutAddMenuEntry ("Euler Angle", 1);
//    glutAddMenuEntry ("Quaternion", 2);
//    int inbetweening_menu = glutCreateMenu(UserInputManager::inbetweeningMenu);
//    glutAddMenuEntry ("Catmul-Rom", 1);
//    glutAddMenuEntry ("B-splines", 2);
//    glutAddSubMenu ("Orientation", orientation_menu);
//    glutAddSubMenu ("Inbetweening", inbetweening_menu);
    glutAddMenuEntry ("Load", 1);
    glutAddMenuEntry ("Reset", 2);
    glutAddMenuEntry ("Start", 3);
    glutAttachMenu (GLUT_RIGHT_BUTTON);
}


void UserInputManager::keyboardFunc(unsigned char key, int x, int y) {
    switch ((char) key) {
        case 'a':
            prefsPointer->setIsPlaying(true);
            break;
        case 'b':
            prefsPointer->setIsPlaying(false);
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

/****
 *
 * @return true if loaded; false if not
 */
bool UserInputManager::loadUserInputFromFileDialog() {
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_OpenDialog( NULL, NULL, &outPath );

    if ( result == NFD_OKAY ) {
        SetupFileLoader::loadPreferencesFromTextFile(outPath, prefsPointer);
        puts("Success!");
        puts(outPath);
        free(outPath);
        return true;
    }
    else if ( result == NFD_CANCEL ) {
        puts("User pressed cancel.");
    }
    else {
        printf("Error: %s\n", NFD_GetError() );
    }

    return false;
}
