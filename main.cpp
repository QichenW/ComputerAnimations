//  Created by Qichen on 8/28/16.
//  Copyright © 2016 SEAS. All rights reserved.
//


// standard
#include <assert.h>
#include <math.h>
#include<stdio.h>

// glut
#if defined(__APPLE__)

#include <GLUT/glut.h>
#include <string>
#include <vector>

#else
#include <GL/glut.h>
#endif

using namespace std;


//globals

vector<GLfloat> vx;
vector<GLfloat> vy;
vector<GLfloat> vz;

GLuint object;
float objectRotation;
char ch = '1';
int wd;

//other functions and main

//.obj loader code begins

void loadObj(char *fname) {
    FILE *fp;
    int read;
    GLfloat x, y, z;
    char dump1,dump2;
    unsigned long vIndex1,vIndex2,vIndex3, vnIndex;
    char lineHeader[128];
    char ch;
    object = glGenLists(1);
    fp = fopen(fname, "r");
    if (!fp) {
        printf("can't open file %s\n", fname);
        exit(1);
    }

    glNewList(object, GL_COMPILE);
    {
        glPushMatrix();
       // glBegin(GL_POINTS);
        while (1) {
            // read the first word of the line, if the return value is EOF then break
            // %s ignores /r /0 /n in between lines
            if (fscanf(fp, "%s", lineHeader) == EOF) {
                break;
            }
            if ( strcmp( lineHeader, "v" ) == 0 ){
                 fscanf(fp, "%f %f %f", &x, &y, &z);
                // glVertex3f(x, y, z);
                 vx.push_back(x);
                 vy.push_back(y);
                 vz.push_back(z);
            }
        }
       // glEnd();
        fclose(fp);
        fp = fopen(fname, "r");
        glLineWidth(1.0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glBegin(GL_TRIANGLES);
        while (1) {
            // read the first word of the line, if the return value is EOF then break
            // %s ignores /r /0 /n in between lines
            if (fscanf(fp, "%s", lineHeader) == EOF) {
                break;
            }
            if ( strcmp( lineHeader, "f" ) == 0 ){

                fscanf(fp, "%lu %c %c %lu", &vIndex1, &dump1, &dump2, &vnIndex);
                fscanf(fp, "%lu %c %c %lu", &vIndex2, &dump1, &dump2, &vnIndex);
                fscanf(fp, "%lu %c %c %lu", &vIndex3, &dump1, &dump2, &vnIndex);
                glVertex3f(vx.at(vIndex1 - 1),vy.at(vIndex1 - 1), vz.at(vIndex1 - 1));
                glVertex3f(vx.at(vIndex2 - 1),vy.at(vIndex2 - 1), vz.at(vIndex2 - 1));
                glVertex3f(vx.at(vIndex3 - 1),vy.at(vIndex3 - 1), vz.at(vIndex3 - 1));
            }
        }
        glEnd();
        fclose(fp);
        

    }
    glPopMatrix();
    glEndList();
    fclose(fp);
}

//.obj loader code ends here

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat) w / (GLfloat) h, 0.1, 1000.0);
    //glOrtho(-25,25,-2,2,0.1,100);
    glMatrixMode(GL_MODELVIEW);
}

void drawObject() {
    glPushMatrix();
//    glTranslatef(0,-1.5,-2);
//    glScalef(1,1,1);
//    glColor3f(1,1,1);
    glTranslatef(0, -40.00, -150);
    glScalef(0.1, 0.1, 0.1);
    glColor3f(0.1, 0.45, 0.1);
    glRotatef(objectRotation, 0, 1, 0);
    glCallList(object);
    glPopMatrix();
    objectRotation = objectRotation + 0.6;
    if (objectRotation > 360)objectRotation = objectRotation - 360;
}

void display(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawObject();
    glutSwapBuffers(); //swap the buffers

}

void keyboard(unsigned char key, int x, int y) {
    switch ((char) key) {
        case 'q':
        case 'Q':
        case '!':
        case 27:    /* ESC */
            glutDestroyWindow(wd);
            exit(0);
        default:
            break;
    }

    return;
}

int main(int argc, char **argv) {
//    printf("path %s\n", argv[0]);
//    FILE *fp;
//    char * path = strcat(argv[0], "/elepham.obj");
//    fp=fopen(path, "r");
//    if (!fp)
//    {
//        printf("can't open file %s\n", path);
//        exit(1);
//    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 640);
    glutInitWindowPosition(100, 100);
    wd = glutCreateWindow("lab1 : key frame");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    loadObj("elepham.obj");//replace porsche.obj with radar.obj or any other .obj to display it

    glutMainLoop();
    return 0;
}
