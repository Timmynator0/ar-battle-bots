#include <stdlib.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>
#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT
#include <GL/glut.h>            // Windows FreeGlut equivalent
#endif
	void Ramp(void);
