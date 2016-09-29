//  Created by Qichen on 9/17/16.
// As required opengl toolkit's api about any matrix and vector related
// calculations are not used. The author implemented them.
//  Copyright © 2016 Qichen Wang. All rights reserved.
//


#include <RotationHelper.h>
#include <UserInputManager.h>
#include <SimpleObjLoader.h>
#include <StringUtils.h>
#include <matrix/InterpolationHelper.h>

using namespace std;

GLuint object;
Preferences prefs;
GLfloat displayRotationVector[3] = {}, increment = 0.005;
GLfloat tVector[4]={}, quaternion[4] = {}, eulerAngle[3] = {}, translation[3] = {};
int window;

static char* OBJECT_FILE_NAME = (char *) "teddy.obj";

void drawFrame();


void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat) w / (GLfloat) h, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

/***
 * display the object when idle
 */
void displayObject() {
    glLoadIdentity();
    glPushMatrix();
    //move the model view away from the camera, so that we are not inside the object
    glMultMatrixf((GLfloat []){1,0,0,0,0,1,0,0,0,0,1,0,0,0,-150,1});
    glColor3f(0.1, 0.45, 0.1);
    //Rotate the object
    glMultMatrixf(RotationHelper::generateFlattenedTransformationMatrix(
            displayRotationVector, (GLfloat []){0,0,0}, false));
    glCallList(object);
    glPopMatrix();
    displayRotationVector[1] += (GLfloat) 0.6;
    if (displayRotationVector[1] > 360) {
        displayRotationVector[1] -= 360;
    }
}

/****
 * This function is for drawing the frames in the interpolated animation.
 */
void drawFrame() {
    glPushMatrix();
    //move the model view away from the camera, so that we are not inside the object
    glMultMatrixf((GLfloat []){1,0,0,0,0,1,0,0,0,0,1,0,0,0,-150,1});
    glColor3f(0.1, 0.45, 0.1);

    // prepare the T vector for current time, then increment time.
    if(prefs.getTimeProgress()<= 1.0){
        InterpolationHelper::prepareTimeVector(tVector, prefs.getTimeProgress());
        prefs.timeProceed(increment);
    }

    // prepare the translation vector
    InterpolationHelper::
    prepareTranslationOrEulerAngleVector(translation, tVector, prefs.translationCoefficientMatrix);

    if (prefs.getOrientationMode() == 0) {
        // if getting euler angle version of animation
        // prepare the euler angle vector
        InterpolationHelper::
        prepareTranslationOrEulerAngleVector(eulerAngle, tVector, prefs.eulerRotationCoefficientMatrix);
        // move the object
        glMultMatrixf(RotationHelper::generateFlattenedTransformationMatrix(eulerAngle, translation, false));
    } else {
        // if getting quaternion version of animation
        // prepare the quaternion vector
        InterpolationHelper::prepareQuaternionVector(quaternion, tVector, prefs.quaterRotationCoefficientMatrix);
        // move and rotate the object
        glMultMatrixf(RotationHelper::generateFlattenedTransformationMatrix(quaternion, translation, true));
    }
    // draw the faces of the object
    glCallList(object);
    glPopMatrix();
}

void display(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // the setup info char * on the bottom left corner on window when it is idle,
    // or the type of animation when playing animation
    UserInterfaceManager::renderStatusMessage(
            prefs.getOrientationMode(), prefs.getInterpolationMode(), prefs.getIsPlaying());
    if(!prefs.getIsPlaying()){
        displayObject();
    } else {
        drawFrame();
    }
    glutSwapBuffers(); //swap the buffers

}
/**
 * openGL works in a right-handed coordinate system by default
 * **/
int main(int argc, char **argv) {
    // initiate an instance of prefs to store the user preference
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 800);
    glutInitWindowPosition(100, 100);
    window = glutCreateWindow("CSCI 6555 project 1 : key frame, rotation and interpolation");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    UserInputManager(&window, &prefs);
    glutKeyboardFunc(UserInputManager::keyboardFunc);
    glutMouseFunc(UserInputManager::mouseFunc);
    object = SimpleObjLoader::loadObj(OBJECT_FILE_NAME);
    // Create the menu structure and attach it to the right mouse button
    UserInputManager::createMouseMenu();
    glutMainLoop();
    return 0;
}