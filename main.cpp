//  Created by Qichen on 8/28/16.
//  Copyright © 2016 SEAS. All rights reserved.
//


#include <MatrixGenerator.h>
#include <UserInputManager.h>
#include <SimpleObjLoader.h>

using namespace std;

GLuint object;
// TODO pitch, yaw, roll, x, y, z
GLfloat KeyFrames[6][6];
float objectRotation;
int window;
bool areKeyFramesSet =false;
static char* OBJECT_FILE_NAME = (char *) "elephant.obj";
float m[] = { 1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f, 0.0f,
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
    float *matrix;

    matrix  = MatrixGenerator::generateFromEulerAngle(m,m);
    glMultMatrixf(matrix);

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

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 640);
    glutInitWindowPosition(100, 100);
    window = glutCreateWindow("lab1 : key frame");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    UserInputManager(&window, &areKeyFramesSet);
    glutKeyboardFunc(UserInputManager::keyboardFunc);
    glutMouseFunc(UserInputManager::mouseFunc);
    object = SimpleObjLoader::loadObj(OBJECT_FILE_NAME);

    /* Create the menu structure and attach it to the right mouse button. */
    UserInputManager::createMouseMenu();

    glutMainLoop();
    return 0;
}