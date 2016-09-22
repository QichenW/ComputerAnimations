//  Created by Qichen on 8/28/16.
//  Copyright © 2016 SEAS. All rights reserved.
//


// standard
#include <assert.h>
#include <iostream>
#include <MatrixGenerator.h>
#include "SimpleObjLoader.h"

using namespace std;

GLuint object;
// pitch, yaw, roll, x, y, z
GLfloat KeyFrames[6][6];
float objectRotation;
int window;
bool areKeyFramesSet =false;
static char* OBJECT_FILE_NAME = (char *) "elepham.obj";
float m[] = { 1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 2.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, 0.0f, -10.0f, 1.0f };
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
// TODO the matrix goes here
    glMultMatrixf(MatrixGenerator::generateFromEulerAngle(m,m));
    //glMultMatrixf(m);

    glCallList(object);
    glPopMatrix();
}

void display(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(!areKeyFramesSet){
        displayObject();
    } else {
        drawFrame();
    }
    glutSwapBuffers(); //swap the buffers

}

void keyboard(unsigned char key, int x, int y) {
    switch ((char) key) {
        case 'a':
            areKeyFramesSet = true;
            break;
        case 'b':
            areKeyFramesSet= false;
            break;
        case 'q':
        case 'Q':
        case 27:    /* ESC */
            glutDestroyWindow(window);
            exit(0);
        default:
            break;
    }
    return;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 640);
    glutInitWindowPosition(100, 100);
    window = glutCreateWindow("lab1 : key frame");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    object = SimpleObjLoader::loadObj(OBJECT_FILE_NAME);//replace porsche.obj with radar.obj or any other .obj to display it
    glutMainLoop();
    return 0;
}
