//  Created by Qichen on 9/17/16.
//  Copyright © 2016 Qichen Wang. All rights reserved.
//


#include <MatrixGenerator.h>
#include <UserInputManager.h>
#include <SimpleObjLoader.h>
#include <StringUtils.h>

using namespace std;

GLuint object;
Preferences prefs;
float objectRotation;
int window;

bool isQuaternion = false;
static char* OBJECT_FILE_NAME = (char *) "teddy.obj";
//static char* OBJECT_FILE_NAME = (char *) "elephant.obj";

float eulerAngle[] = {45,45,45};
float trip[] = {50,-4,6};

void drawFrame();


void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat) w / (GLfloat) h, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void displayObject() {
    glLoadIdentity();
    glPushMatrix();
    //TODO replace these 2 lines with self written matrix calculation
    glTranslatef(0, (GLfloat) 0.0, -150);
    glScalef(1, 1, 1);
    //glScalef(0.1, 0.1, 0.1);
    glColor3f(0.1, 0.45, 0.1);
    glRotatef(objectRotation, 0, 1, 0);
    glCallList(object);
    glPopMatrix();
    objectRotation = objectRotation + (float) 0.6;
    if (objectRotation > 360)objectRotation = objectRotation - 360;
}

void drawFrame() {
    glPushMatrix();
    //TODO replace these 2 lines with self written matrix calculation
    glTranslatef(0, (GLfloat) 0.0, -150);
    glScalef(1, 1, 1);
    //glScalef(0.1, 0.1, 0.1);
    glColor3f(0.1, 0.45, 0.1);

// TODO the matrix goes here, quaternion version is not yet done
    glMultMatrixf(MatrixGenerator::generateFrameFromUserInput(eulerAngle, trip, isQuaternion));

    glCallList(object);
    glPopMatrix();
}

void display(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // the setup info char * on the bottom left corner on window
    UserInterfaceManager::renderStatusMessage(prefs.setKeyFrameLoaded());
    if(!prefs.setKeyFrameLoaded()){
        displayObject();
    } else {
        drawFrame();
    }
    glutSwapBuffers(); //swap the buffers

}
/**
 * openGL works in a left-handed coordinate system by default
 * **/
int main(int argc, char **argv) {
    // initiate an instance of prefs to store the user preference
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 640);
    glutInitWindowPosition(100, 100);
    window = glutCreateWindow("CSCI 6555 lab1 : rotation, key frame and interpolation");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    UserInputManager(&window, &prefs);
    glutKeyboardFunc(UserInputManager::keyboardFunc);
    glutMouseFunc(UserInputManager::mouseFunc);
    object = SimpleObjLoader::loadObj(OBJECT_FILE_NAME);
    /* Create the menu structure and attach it to the right mouse button. */
    UserInputManager::createMouseMenu();

    glutMainLoop();
    return 0;
}