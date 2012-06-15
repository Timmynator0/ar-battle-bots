#include "loadTGA.h"
#include <stdlib.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>
#include <stdio.h>

#include "Robot.h"
#include "ObjModel.h"


#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT
#include <GL/freeglut.h>            // Windows FreeGlut equivalent
#endif

void setOrthographicProjection() ;
void resetPerspectiveProjection();
void renderBitmapString(float x, float y, void *font,char *string);
void ArenaDisplay(void);
void Reshape(GLint width, GLint height);
void InitGraphics(void);
void MouseButton(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void IdleFuncArena(void);
void KeyboardArena(unsigned char key, int x, int y);
void setRobots(Robot &r);
//int main(int argc, char* argv[]);
