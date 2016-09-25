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
// TODO pitch, yaw, roll, x, y, z
GLdouble KeyFrames[6][6];
float objectRotation;
int window;

bool isQuaternion = false;
static char* OBJECT_FILE_NAME = (char *) "elephant.obj";

float eulerAngle[] = {45,45,45};
float quaternion[4] = {};
float trip[] = {300,0,0};

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
    glTranslatef(0, (GLfloat) -40.00, -150);
    glScalef(0.1, 0.1, 0.1);
    glColor3f(0.1, 0.45, 0.1);
    glRotatef(objectRotation, 0, 1, 0);
    glCallList(object);
    glPopMatrix();
    objectRotation = objectRotation + (float) 0.6;
    if (objectRotation > 360)objectRotation = objectRotation - 360;
}

void drawFrame() {
    glPushMatrix();
    glTranslatef(0, (GLfloat) -40.00, -150);
    glScalef(0.1, 0.1, 0.1);
    glColor3f(0.1, 0.45, 0.1);

// TODO the matrix goes here, quaternion version is not yet done
    glMultMatrixf(MatrixGenerator::generateFrameFromUserInput(eulerAngle, trip, isQuaternion));

    glCallList(object);
    glPopMatrix();
}

void display(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// TODO change the setup info char *
    UserInterfaceManager::renderStatusMessage(prefs.getInterpolationMode(),
                                              prefs.getOrientationMode(),
                                              prefs.arePointsSet());
    if(!prefs.areKeyFramesSet()){
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
    //TODO fix this
    UserInputManager(&window, &prefs);
    glutKeyboardFunc(UserInputManager::keyboardFunc);
    glutMouseFunc(UserInputManager::mouseFunc);
    object = SimpleObjLoader::loadObj(OBJECT_FILE_NAME);
    /* Create the menu structure and attach it to the right mouse button. */
    UserInputManager::createMouseMenu();

    glutMainLoop();
    return 0;
}