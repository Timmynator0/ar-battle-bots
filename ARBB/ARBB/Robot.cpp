#include "Robot.h"

vector<ObjModel*> RobotModels;

GLuint robotTextures[TEXTURE_COUNT];
const char *RobotTextureFiles[TEXTURE_COUNT] =
{ "robotcreator.tga","banden.tga" };

Robot::Robot()
{
	nummer = 0;
	speed = 0;
	weight = 0;
	damage = 0;	
	for(int i=0; i<6; i++) items[i] = 1;
	w1ani = 0;
	w2ani = 0;
	w3ani = 0;
	ani1 = true;
}
Robot::Robot(int Nummer, int Speed, int Weight,int Damage, int Items[6], int Health, vector< ObjModel*> modellen)
{
	nummer = Nummer;
	speed = Speed;
	weight = Weight;
	damage = Damage;
	health = 100;
	for(int i=0; i<6; i++) items[i] = Items[i];
	w1ani = 0;
	w2ani = 0;
	w3ani = 0;
	ani1 = true;
	RobotModels = modellen;
}
void Robot::Draw(float X, float Y, float Z, float RotationY, bool animation1, bool animation2, bool animation3, bool cam)
{
	x = X;
	y = Y;
	z = Z;
	rotationY = RotationY;
	anime1 = animation1;
	anime2 = animation2;
	anime3 = animation3;

	glPushMatrix();
	glTranslated(x,y+20,z);

	glPushMatrix();
	if(cam)
	{
		drawFace(8,8);
	}
	glTranslated(0,-20,0);

	glPushMatrix();
	glRotated(rotationY,0,1,0);
	glPushMatrix();
	glScaled(6,6,6);	
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
	glScaled(6,6,6);
	if(items[3] != 0){
		RobotModels[20]->draw(); // houvast wapens1
		glPushMatrix();
		glTranslated(-0.7,0.5,0);
		if(anime1)
		{
			glPushMatrix();
			glTranslated(0.5,0.1,0);
			if(ani1){
				w1ani -=5;
				if(w1ani < -15) ani1 = false;
			}
			else {
				w1ani +=5;
				if(w1ani >50){
					ani1 = true;
					anime1 = false;
				}
			}
			glPushMatrix();
			glRotated(w1ani,0,0,1);
		}
		else{ w1ani = 0;}
		switch(items[3]){
			case 1: RobotModels[23]->draw(); break;
			case 2: RobotModels[22]->draw(); break;
			case 3: RobotModels[24]->draw(); RobotModels[25]->draw(); break;
			case 4: RobotModels[21]->draw(); break;
		}
		if(anime1)
		{
			glPopMatrix();
			glTranslated(-0.5,-0.1,0);
			glPopMatrix();
		}
		glPopMatrix();
		/*if(animation2)
		{
			if(w1ani <=0) w1ani +=10;
			else if(w1ani >=100) w1ani -=10;
			glPushMatrix();
			glRotated(w1ani,0,0,1);
		}
		else w1ani = 0;*/
		if(items[4] != 0){
			switch(items[4]){
			case 1: RobotModels[29]->draw(); glPushMatrix(); glScaled(1,1,-1); RobotModels[29]->draw(); glPopMatrix(); break;
			case 2: RobotModels[28]->draw(); break;
			case 3: RobotModels[27]->draw(); glPushMatrix(); glScaled(1,1,-1); RobotModels[27]->draw(); glPopMatrix(); break;
			case 4: RobotModels[26]->draw(); break;
			}
			if(anime3)
			{
				w3ani += 5;
				glPushMatrix();
				glRotated(w3ani,0,1,0);
			}
			else w3ani = 0;
			if(items[5] != 0){
				switch(items[5]){
				case 2: RobotModels[32]->draw(); break;
				case 3: RobotModels[31]->draw(); break;
				case 4: RobotModels[30]->draw(); break;
				}
			}
			//if(animation2) glPopMatrix();
		}
		if(anime3) glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glDeleteTextures(GL_TEXTURE_2D,robotTextures);
	
	glutPostRedisplay();
}