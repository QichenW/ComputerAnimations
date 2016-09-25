//
// Created by Qichen on 9/23/16.
//

#ifndef GLUTPROJECT_USERINPUTMANAGER_H
#define GLUTPROJECT_USERINPUTMANAGER_H

// glut
#if defined(__APPLE__)
#include <GLUT/glut.h>
#include <setup/Preferences.h>

#else
#include <GL/glut.h>
#endif

class UserInputManager {
private:
    static void mainMenu (int id);
    static void orientationMenu(int id);
    static void inbetweeningMenu(int id);
public:
    UserInputManager(int * window, Preferences * preferences);
    static void createMouseMenu();
    static void mouseFunc (int button, int state, int x, int y);
    static void keyboardFunc(unsigned char, int, int);
};


#endif //GLUTPROJECT_USERINPUTMANAGER_H
