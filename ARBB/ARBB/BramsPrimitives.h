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

const long double PI = acos((long double) -1);

/* This method creates a cube at X,Y,Z, with width,height,depth and with center at x, y+height,z+depth,
 * param u,v are meant for starting position @ the texture, uvsize is the size of x in the texture
*/
void createCube(float width, float height, float depth,float u, float v, float uvsize);
void createCircle(float radius, int segments,int part,bool texture);
void createCylinder(float radius, int segments, float depth,int part, bool texture);