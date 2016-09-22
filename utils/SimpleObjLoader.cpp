//
// Created by Qichen on 9/21/16.
//

#include "SimpleObjLoader.h"
#include <iostream>

using namespace std;

GLuint SimpleObjLoader::loadObj(char *fileName) {
    FILE *filePointer;
    GLfloat x, y, z;
    GLuint object;
    char dump1, dump2;
    unsigned long vIndex1, vIndex2, vIndex3, vnIndex;
    vector<GLfloat> vx, vy,vz;
    char lineHeader[128];
    object = glGenLists(1);
    filePointer = fopen(fileName, "r");
    if (!filePointer) {
        printf("can't open file %s\n", fileName);
        exit(1);
    }

    glNewList(object, GL_COMPILE);

        // glBegin(GL_POINTS);
        while (1) {
            // read the first word of the line, if the return value is EOF then break
            if (fscanf(filePointer, "%s", lineHeader) == EOF) {
                break;
            }
            if (strcmp(lineHeader, "v") == 0) {
                fscanf(filePointer, "%f %f %f", &x, &y, &z);
                // glVertex3f(x, y, z);
                vx.push_back(x);
                vy.push_back(y);
                vz.push_back(z);
            }
        }
        // glEnd();
        fclose(filePointer);
        filePointer = fopen(fileName, "r");
        glLineWidth(1.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_TRIANGLES);
        while (true) {
            // %s ignores /r /0 /n in between lines
            if (fscanf(filePointer, "%s", lineHeader) == EOF) {
                break;
            }
            if (strcmp(lineHeader, "f") == 0) {

                fscanf(filePointer, "%lu %c %c %lu", &vIndex1, &dump1, &dump2, &vnIndex);
                fscanf(filePointer, "%lu %c %c %lu", &vIndex2, &dump1, &dump2, &vnIndex);
                fscanf(filePointer, "%lu %c %c %lu", &vIndex3, &dump1, &dump2, &vnIndex);
                glVertex3f(vx.at(vIndex1 - 1), vy.at(vIndex1 - 1), vz.at(vIndex1 - 1));
                glVertex3f(vx.at(vIndex2 - 1), vy.at(vIndex2 - 1), vz.at(vIndex2 - 1));
                glVertex3f(vx.at(vIndex3 - 1), vy.at(vIndex3 - 1), vz.at(vIndex3 - 1));
            }
        }
        glEnd();
        fclose(filePointer);

    glEndList();

    return object;
}
