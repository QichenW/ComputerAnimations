//
// Created by Qichen on 9/21/16.
//

#include "SimpleObjLoader.h"
#include <iostream>

using namespace std;

FILE *filePointer;
char firstWord[16];
vector<GLfloat> vx, vy,vz;
GLuint SimpleObjLoader::loadObj(char *fileName) {

    GLfloat x, y, z;
    GLuint object;
    object = glGenLists(1);
    filePointer = fopen(fileName, "r");
    if (!filePointer) {
        printf("can't open file %s\n", fileName);
        exit(1);
    }

    while (1) {
        // read the first word of the line
        if (fscanf(filePointer, "%s", firstWord) == EOF) {
            break;
        }
        if (strcmp(firstWord, "v") == 0) {
            fscanf(filePointer, "%f %f %f", &x, &y, &z);
            // glVertex3f(x, y, z);
            vx.push_back(x);
            vy.push_back(y);
            vz.push_back(z);
        }
    }

    fclose(filePointer);
    filePointer = fopen(fileName, "r");
    glNewList(object, GL_COMPILE);
        glLineWidth(1.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // record the polygons of an object in a
        //TODO if is elephant.obj
        //recordObjectAsTrianglesWithNoVt();
        //TODO if is teddy.obj
        recordObjectAsTrianglesWithNoVtNoVn();
    glEndList();
    fclose(filePointer);


    return object;
}

/****
 * This function can load a obj file with no texture vector and describing the object in triangles
 */
void SimpleObjLoader::recordObjectAsTrianglesWithNoVt() {
    char dump1, dump2;
    unsigned long vIndex1, vIndex2, vIndex3, vnIndex;
    glBegin(GL_TRIANGLES);
    while (true) {
            // %s ignores /r /0 /n in between lines
            if (fscanf(filePointer, "%s", firstWord) == EOF) {
                break;
            }
            if (strcmp(firstWord, "f") == 0) {

                fscanf(filePointer, "%lu %c %c %lu", &vIndex1, &dump1, &dump2, &vnIndex);
                fscanf(filePointer, "%lu %c %c %lu", &vIndex2, &dump1, &dump2, &vnIndex);
                fscanf(filePointer, "%lu %c %c %lu", &vIndex3, &dump1, &dump2, &vnIndex);
                glVertex3f(vx.at(vIndex1 - 1), vy.at(vIndex1 - 1), vz.at(vIndex1 - 1));
                glVertex3f(vx.at(vIndex2 - 1), vy.at(vIndex2 - 1), vz.at(vIndex2 - 1));
                glVertex3f(vx.at(vIndex3 - 1), vy.at(vIndex3 - 1), vz.at(vIndex3 - 1));
            }
        }
    glEnd();
}

/****
 * This function can load a obj file with no texture vector, no normal vector and describing the object in triangles
 */
void SimpleObjLoader::recordObjectAsTrianglesWithNoVtNoVn() {
    unsigned long vIndex1, vIndex2, vIndex3;
    glBegin(GL_TRIANGLES);
    while (true) {
        // %s ignores /r /0 /n in between lines
        if (fscanf(filePointer, "%s", firstWord) == EOF) {
            break;
        }
        if (strcmp(firstWord, "f") == 0) {

            fscanf(filePointer, "%lu %lu %lu", &vIndex1, &vIndex2, &vIndex3);
            glVertex3f(vx.at(vIndex1 - 1), vy.at(vIndex1 - 1), vz.at(vIndex1 - 1));
            glVertex3f(vx.at(vIndex2 - 1), vy.at(vIndex2 - 1), vz.at(vIndex2 - 1));
            glVertex3f(vx.at(vIndex3 - 1), vy.at(vIndex3 - 1), vz.at(vIndex3 - 1));
        }
    }
    glEnd();
}
