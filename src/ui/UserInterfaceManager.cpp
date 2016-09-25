//
// Created by Qichen on 9/24/16.
//

#include <cstring>
#include <cstdlib>
#include "UserInterfaceManager.h"

static const int NOT_CHOSEN = -1, FIRST_OPTION_CHOSEN = 0, SECOND_OPTION_CHOSEN = 1;
static const char * strReqestMouseInput ="Right click for options, choose ";
static const char *strOrientation ="\"orientation representation\" ";
static const char *strInterpolation ="\"interpolation method\" ";
static const char *strCoordinates ="Please type in the x-y-z coordinates for the ";
static const char *strInstructionForVectorInputs[3]= { "Please type in the pitch, yaw, roll for 4 key frames, ",
                                                "Please type in 4 quaternions, ",
                                                       "Please type in x-y-z coordinates for 4 key frames, "};
static const char *strFinishEnter = "then press enter";
//static const char *strIndices[4]= { "1st ", "2nd ", "3rd ", "4th "};
//const char * strKeyFrame = "key frame";
void UserInterfaceManager::renderString(int interpolationChosen, int orientationChosen, bool arePointsSet) {
    char *infoString;

    if ((interpolationChosen != -1 && orientationChosen!= -1)){
        if(arePointsSet){
            infoString = (char *) malloc(
                    strlen(strInstructionForVectorInputs[orientationChosen])
                    + strlen(strFinishEnter)  + 1);
            strcpy(infoString, strInstructionForVectorInputs[orientationChosen]);
            strcat(infoString,strFinishEnter);
        } else {
            infoString = (char *) malloc(
                    strlen(strInstructionForVectorInputs[2])
                    + strlen(strFinishEnter)  + 1);
            strcpy(infoString, strInstructionForVectorInputs[2]);
            strcat(infoString,strFinishEnter);
        }

    } else {
        if (!(interpolationChosen != -1|| orientationChosen!= -1)) {
            infoString = (char *) malloc(
                    strlen(strReqestMouseInput) + strlen(strOrientation) + strlen(strInterpolation) + 1);
            strcpy(infoString, strReqestMouseInput);
            strcat(infoString, strOrientation);
            strcat(infoString, strInterpolation);
        } else if (interpolationChosen!= -1) {
            infoString = (char *) malloc(
                    strlen(strReqestMouseInput) + strlen(strOrientation) + 1);
            strcpy(infoString, strReqestMouseInput);
            strcat(infoString, strOrientation);
        } else {
            infoString = (char *) malloc(
                    strlen(strReqestMouseInput) + strlen(strInterpolation) + 1);
            strcpy(infoString, strReqestMouseInput);
            strcat(infoString, strInterpolation);
        }
    }

    int x =10, y = 10;
//set the text position in the window
    glWindowPos2f(x,y);
    int len = (int) strlen(infoString);
    glColor3f(1.0f, 1.0f, 0.0f);
//loop to display character by character
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, infoString[i]);
    }
};