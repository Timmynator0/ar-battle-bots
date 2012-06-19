#ifndef ENDSCREEN
#define ENDSCREEN

#include <stdlib.h>

#include <iostream>
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>
#include <stdio.h>
#include <time.h>
#include <sstream>

#include "loadTGA.h"
#include "Robot.h"
#include "Chainsaw.h"

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT 
#include <GL/freeglut.h>// Windows FreeGlut equivalent
#endif
#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif
#define esTEXTURE_COUNT 3

void initES(vector< ObjModel*> Esmodellen);
void createESBackground(float width, float height);
void setESRobots(Robot &r);

#endif