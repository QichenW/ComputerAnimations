//
// Created by Qichen on 9/24/16.
//

#include <cstring>
#include <cstdlib>
#include "StringUtils.h"

static const char * strReqestMouseInput ="Right click and load a setup (.txt) file";
static const char *strFileLoaded ="Setup file is loaded, right click to start animation or reset";
static char *strStatusInfo;


void UserInterfaceManager::renderStatusMessage(bool areKeyFramesSet) {

    if (areKeyFramesSet){
            strStatusInfo = buildString((const char *[]) {strFileLoaded}, 1);
        } else {
        strStatusInfo = buildString((const char *[]) {strReqestMouseInput}, 1);
    }
    printInWindow(strStatusInfo, true);
}

/***
 * This function prints a char * to the window.
 * @param strInfo is to be printed.
 * @param isStatusInfo true to print in the lower line; false to print in the upper line.
 */
void UserInterfaceManager::printInWindow(char *strInfo, bool isStatusInfo) {
    int x, y;
    if (isStatusInfo) {
        x = 10;
        y = 10;
    } else {
        x = 0;
        y = 0;
    }
//set the text position in the window and color
    glWindowPos2f(x,y);
    glColor3f(1.0f, 1.0f, 0.0f);
    int len = (int) strlen(strInfo);
//loop to display character by character
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, strInfo[i]);
    }
}

/****
 * buildString is the helper function to generate a char * , which is a piece of info to display in the window.
 * @param pointer points to an array of array of char
 * @param numberOfSegments is the size of *pointer
 * @return the char * ready to be printed in the window.
 */
char *UserInterfaceManager::buildString(const char **pointer, int numberOfSegments) {
    // allocate enough memory for this char*
    char *infoString= (char *) malloc(strlen(strFileLoaded)* 3);

    while(numberOfSegments > 0) {
        strcat(infoString, *pointer++);
        numberOfSegments--;
    }
    return infoString;
};