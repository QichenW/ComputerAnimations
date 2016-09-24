//
// Created by Qichen on 9/24/16.
//

#include <cstring>
#include "UserInterfaceManager.h"


void UserInterfaceManager::renderString(int x, int y, char *string) {
//set the position of the text in the window using the x and y coordinates
    glWindowPos2f(x,y);
//get the length of the string to display
    int len = (int) strlen(string);
    glColor3f(1.0f, 1.0f, 0.0f);
//loop to display character by character
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
};