//
// Created by Qichen on 9/21/16.
//

#ifndef GLUTPROJECT_SIMPLEOBJLOADER_H
#define GLUTPROJECT_SIMPLEOBJLOADER_H

// glut
#if defined(__APPLE__)

#include <GLUT/glut.h>
#include <string>
#include <vector>

#else
#include <GL/glut.h>
#endif

class SimpleObjLoader
{
public:
    GLuint static loadObj(char *fileName);
};

#endif //GLUTPROJECT_SIMPLEOBJHEADER_H
