#include "Robot.h"
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>

#include "loadTGA.h"
#include "ObjModel.h"

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT 
#include <GL/freeglut.h>// Windows FreeGlut equivalent
#endif


vector<ObjModel*> RobotModels;

GLuint robotTextures[TEXTURE_COUNT];
const char *RobotTextureFiles[TEXTURE_COUNT] =
{ "robotcreator.tga","banden.tga" };

Robot::Robot()
{

}
Robot::Robot(int Nummer, int Speed, int Weight,int Damage, int Items[6])
{
	nummer = Nummer;
	speed = Speed;
	weight = Weight;
	damage = Damage;
	for(int i=0; i<6; i++) items[i] = Items[i];
}
void Robot::Draw(float x, float y, float z, float rotationY, bool animation1, bool animation2, bool animation3)
{	
	glPushMatrix();
	glTranslated(x,y,z);
	glPushMatrix();
	glScaled(0.4,0.4,0.4);	
	glBindTexture(GL_TEXTURE_2D, robotTextures[1]);
	float size = 0.2;
	if(items[0] != 0){
		switch(items[0]){
		case 1: // triangle
			switch(items[1]){
			case 1: RobotModels[5]->draw(); break;
			case 2: RobotModels[4]->draw(); break;
			case 3: RobotModels[6]->draw(); break;
			case 4: RobotModels[7]->draw(); break;
			}break;
		case 2: // circle
			switch(items[1]){
			case 1: RobotModels[13]->draw(); break;
			case 2: RobotModels[12]->draw(); break;
			case 3: RobotModels[14]->draw(); break;
			case 4: RobotModels[15]->draw(); break;
			}break;
		case 3: // pentagon
			switch(items[1]){
			case 1: RobotModels[17]->draw(); break;
			case 2: RobotModels[16]->draw(); break;
			case 3: RobotModels[18]->draw(); break;
			case 4: RobotModels[19]->draw(); break;
			}break;
		case 4: // quad
			switch(items[1]){
			case 1: RobotModels[9]->draw(); break;
			case 2: RobotModels[8]->draw(); break;
			case 3: RobotModels[10]->draw(); break;
			case 4: RobotModels[11]->draw(); break;
			}break;
		}
	}
	glPopMatrix();
	glPushMatrix();
	glScaled(0.4,0.4,0.4);
	if(items[3] != 0){
		RobotModels[20]->draw(); // houvast wapens1
		glPushMatrix();
		glTranslated(-0.5,0.5,0);
		switch(items[3]){
			case 1: RobotModels[23]->draw(); break;
			case 2: RobotModels[22]->draw(); break;
			case 3: RobotModels[24]->draw(); RobotModels[25]->draw(); break;
			case 4: RobotModels[21]->draw(); break;
		}
		glPopMatrix();
		if(items[4] != 0){
			switch(items[4]){
			case 1: RobotModels[29]->draw(); glPushMatrix(); glScaled(1,1,-1); RobotModels[29]->draw(); glPopMatrix(); break;
			case 2: RobotModels[28]->draw(); break;
			case 3: RobotModels[27]->draw(); glPushMatrix(); glScaled(1,1,-1); RobotModels[27]->draw(); glPopMatrix(); break;
			case 4: RobotModels[26]->draw(); break;
			}
			if(items[5] != 0){
				switch(items[5]){
				case 2: RobotModels[32]->draw(); break;
				case 3: RobotModels[31]->draw(); break;
				case 4: RobotModels[30]->draw(); break;
				}
			}
		}
	}
	glPopMatrix();
	glPopMatrix();
}