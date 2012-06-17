#ifndef ROBOT
#define ROBOT
#include <vector>
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>

#include "loadTGA.h"
#include "ObjModel.h"
#include "faceCam.h"

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT 
#include <GL/freeglut.h>// Windows FreeGlut equivalent
#endif


using namespace std;

class ObjModel;

class Robot{
private :	
    int nummer;
	
	int weight;
	
	int items[6];
	float w1ani,w2ani,w3ani; //weapon animations
	bool ani1;
public :
	int	damage;
	int speed;
	int health;
	float x, y, z,rotationY;
	bool anime1;
	bool anime2;
	bool anime3;
	Robot();
	Robot(int Nummer, int Speed, int Weight,int Damage, int Items[6],vector< ObjModel*> modellen);
	void Draw(float X, float Y, float Z, float RotationY, bool animation1, bool animation2, bool animation3);
};

#endif ROBOT