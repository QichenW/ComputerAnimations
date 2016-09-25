//
// Created by Qichen on 9/24/16.
//

#include <cstring>
#include <cstdlib>
#include "StringUtils.h"

static const char * strReqestMouseInput ="Right click for options, choose ";
static const char *strOrientation ="\"orientation representation\" ";
static const char *strInterpolation ="\"interpolation method\" ";
static const char *strInstructionForVectorInputs[3]= { "Please type in the pitch, yaw, roll for 4 key frames, ",
                                                "Please type in 4 quaternions, ",
                                                       "Please type in x-y-z coordinates for 4 key frames, "};
static const char *strFinishEnter = "then press enter";
static char *strStatusInfo;


void UserInterfaceManager::renderStatusMessage(int interpolationChosen, int orientationChosen, bool arePointsSet) {

    if ((interpolationChosen != -1 && orientationChosen!= -1)){
        if(arePointsSet){
            strStatusInfo = buildString((const char *[])
                                                {strInstructionForVectorInputs[orientationChosen], strFinishEnter}, 2);
        } else {
            strStatusInfo = buildString((const char *[]) {strInstructionForVectorInputs[2], strFinishEnter}, 2);
        }

    } else {
        if (interpolationChosen == -1 && orientationChosen== -1) {
            strStatusInfo = buildString((const char *[]) {strReqestMouseInput, strOrientation, strInterpolation},
                                        3);
        } else if (interpolationChosen!= -1) {
            strStatusInfo = buildString((const char *[]) {strReqestMouseInput, strOrientation}, 2);
        } else {
            strStatusInfo = buildString((const char *[]) {strReqestMouseInput, strInterpolation}, 2);
        }
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
    char *infoString= (char *) malloc(strlen(strInstructionForVectorInputs[1])* 8);

    while(numberOfSegments > 0) {
        strcat(infoString, *pointer++);
        numberOfSegments--;
    }
    return infoString;
};