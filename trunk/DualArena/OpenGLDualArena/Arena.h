#include <iostream>
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>
#include <stdio.h>

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>            // Windows FreeGlut equivalent
#endif

void Display(void);
void Reshape(GLint width, GLint height);
void InitGraphics(void);
void MouseButton(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void IdleFunc(void);
void Keyboard(unsigned char key, int x, int y);
int main(int argc, char* argv[]);
