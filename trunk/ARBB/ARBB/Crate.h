#pragma once
#include <stdlib.h>
#include <tchar.h>
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
#define FREEGLUT
#include <GL/glut.h>            // Windows FreeGlut equivalent
#endif
	
void Crate(float cx, float y, float cz,double playerx, double playerz);
void CollisionMove(float cx, float cz,double px, double pz);