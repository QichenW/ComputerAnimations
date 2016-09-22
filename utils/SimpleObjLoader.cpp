//
// Created by Qichen on 9/21/16.
//

#include "SimpleObjLoader.h"
#include <iostream>

using namespace std;

void loadObj() {
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
}