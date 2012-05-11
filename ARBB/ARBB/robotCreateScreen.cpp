#include <iostream>
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>
#include <stdio.h>

#include "loadTGA.h"
#include "robotCreateScreen.h"
#include "BramsPrimitives.h"

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>            // Windows FreeGlut equivalent
#endif

GLuint              textureID2;
CREATOR				creators[4];
float				ItemRotation = 0;

void updateItems(int stage, int place){
	glPushMatrix();
	glTranslated(-1.6,-0.15,-0.2);
	glPushMatrix();
	glTranslated(0.9*place,0,0);
	float size = 0.11;
	switch(stage){
	case 0:					//----------------Vorm Selectie --------------------
			glColor4f(0.5,0.5,0.5,1);
		//rect
			glPushMatrix();
			if(creators[place].rotateRB) glRotated(ItemRotation,0,1,0);
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(0,size*2,-size/5);
			glVertex3f(-size,size,-size/5);
			glVertex3f(0,size*2,size/5);
			glVertex3f(-size,size,size/5);
			glVertex3f(size,size,size/5);
			glVertex3f(0,0,size/5);
			glVertex3f(size,size,-size/5);
			glVertex3f(0,0,-size/5);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(size,size,size/5);
			glVertex3f(0,size*2,size/5);
			glVertex3f(size,size,-size/5);
			glVertex3f(0,size*2,-size/5);
			glVertex3f(0,0,-size/5);
			glVertex3f(-size,size,-size/5);
			glVertex3f(0,0,size/5);
			glVertex3f(-size,size,size/5);
		glEnd();
		glPopMatrix();

		// pentagon
		glPushMatrix();
		glTranslated(0,0.4,0);
			glPushMatrix();
			if(creators[place].rotateRU)glRotated(ItemRotation,0,1,0);
		glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0,size*3,size/5);

			glVertex3f(size,size*1.5,size/5);
			glVertex3f(size,0,size/5);
			glVertex3f(-size,0,size/5);
			glVertex3f(-size,size*1.5,size/5);
			glVertex3f(-size,size*1.5,-size/5);
			glVertex3f(0,size*3,-size/5);
			glVertex3f(size,size*1.5,-size/5);
			glVertex3f(size,size*1.5,size/5);
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
			glVertex3f(-size,0,-size/5);
			
			glVertex3f(-size,0,size/5);
			glVertex3f(-size,size*1.5,size/5);
			glVertex3f(-size,size*1.5,-size/5);
			glVertex3f(0,size*3,-size/5);
			glVertex3f(size,size*1.5,-size/5);
			glVertex3f(size,0,-size/5);
			glVertex3f(size,0,size/5);
			glVertex3f(-size,0,size/5);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);		
			glVertex3f(size,size*1.5,size/5);
			glVertex3f(size,0,size/5);
			glVertex3f(size,size*1.5,-size/5);
			glVertex3f(size,0,-size/5);
		glEnd();
		glPopMatrix();
		glPopMatrix();

		// cirkel 
		glPushMatrix();
		glTranslated(0.25,0.6,-size/2);
			glPushMatrix();
			if(creators[place].rotateLU)glRotated(ItemRotation,0,1,0);
			createCylinder(size,12,(size/2.5),1,false);
		glPopMatrix();
		glPopMatrix();

		//triangle
		glPushMatrix();
		glTranslated(0.25,0,0);
				glPushMatrix();
			if(creators[place].rotateLB){
			/*	glPushMatrix();
				glTranslated(0.2,-1,0);
				glPushMatrix();
				glRotated(25,1,0,0);
				size*=3;
				glBegin(GL_TRIANGLES);
					glVertex3f(-size,0,size/5); glVertex3f(size,0,size/5); glVertex3f(0,size*2,size/5);
					glVertex3f(-size,0,-size/5); glVertex3f(size,0,-size/5); glVertex3f(0,size*2,-size/5);
				glEnd();
				glBegin(GL_TRIANGLE_STRIP);
					glVertex3f(-size,0,size/5); 
					glVertex3f(-size,0,-size/5); 
					glVertex3f(size,0,size/5); 
					glVertex3f(size,0,-size/5);
					glVertex3f(0,size*2,size/5); 
					glVertex3f(0,size*2,-size/5);
					glVertex3f(-size,0,size/5); 
					glVertex3f(-size,0,-size/5); 
				glEnd();
				size/=3;
				glPopMatrix();
				glPopMatrix();*/
				glRotated(ItemRotation,0,1,0);
			}
		glBegin(GL_TRIANGLES);
			glVertex3f(-size,0,size/5); glVertex3f(size,0,size/5); glVertex3f(0,size*2,size/5);
			glVertex3f(-size,0,-size/5); glVertex3f(size,0,-size/5); glVertex3f(0,size*2,-size/5);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
		glColor4f(1,0,0,1);
			glVertex3f(-size,0,size/5); 
			glVertex3f(-size,0,-size/5); 
			glVertex3f(size,0,size/5); 
			glVertex3f(size,0,-size/5);
			glVertex3f(0,size*2,size/5); 
			glVertex3f(0,size*2,-size/5);
			glVertex3f(-size,0,size/5); 
			glVertex3f(-size,0,-size/5); 
		glEnd();
		glPopMatrix();
		glPopMatrix();
		break;
	case 1:						//----------------Wielen Selectie --------------------	
		//houten Wielen
			glPushMatrix();
			if(creators[place].rotateRB) glRotated(ItemRotation,0,1,0);
		glPopMatrix();

		//rubberen Banden
		glPushMatrix();
		glTranslated(0,0.4,0);
			glPushMatrix();
			if(creators[place].rotateRU)glRotated(ItemRotation,0,1,0);
		glPopMatrix();
		glPopMatrix();

		//metalen wielen 
		glPushMatrix();
		glTranslated(0.25,0.6,-size/2);
			glPushMatrix();
			if(creators[place].rotateLU)glRotated(ItemRotation,0,1,0);
		glPopMatrix();
		glPopMatrix();

		//rupsbanden 
		glPushMatrix();
		glTranslated(0.25,0,0);
			glPushMatrix();
			if(creators[place].rotateLB)glRotated(ItemRotation,0,1,0);		
		glPopMatrix();
		glPopMatrix();
		break;
		break;
	case 2:						//----------------Materiaal Selectie --------------------	
		break;
	case 3:						//----------------Wapen 1 Selectie --------------------	
		break;
	case 4:						//----------------Wapen 2 Selectie --------------------	
		break;
	case 5:						//----------------Wapen 3 Selectie --------------------	
		break;
	}
	glPopMatrix();
	glPopMatrix();
	glColor4f(1,1,1,1);
}

void createRCSBackground(){
	// de hoogte en breedte per achtergrond en een offset breedte zodat de 4 naast elkaar verschijnen
	float width = 1, height = 2 , newwidth = width *-1;
	
	// het laden van de texture voor de achtergrond
	glGenTextures(1, &textureID2);
    glBindTexture(GL_TEXTURE_2D, textureID2);
    LoadTGATexture("robotcreator.tga", GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);

	//de 4 achtergronden creeeren
	for(int i =0; i<4; i++){		
		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(1,1);		glVertex3f(newwidth- width,height,0);		//1
			glTexCoord2f(0,1);		glVertex3f(newwidth,height,0);		//2
			glTexCoord2f(1,0);		glVertex3f(newwidth- width,-height,0);			//3
			glTexCoord2f(0,0);		glVertex3f(newwidth,-height,0);			//4
		glEnd();	
		glPushMatrix();
		float correction = 0.39*creators[i].createstage;
		glTranslated(0.82,-0.5+correction,-0.2);
		float size = 0.075;
		newwidth -= (0.1*i);
		glBegin(GL_TRIANGLE_FAN);
			glColor4f(0.6,0.6,1,0.6);
			glVertex3f(newwidth- width+size,0,0);
			glVertex3f(newwidth- width+(size*2),0,0);
			glVertex3f(newwidth- width+(size*3),size,0);
			glVertex3f(newwidth- width+(size*3),size*2,0);
			glVertex3f(newwidth- width+(size*2),size*3,0);
			glVertex3f(newwidth- width+size,size*3,0);
			glVertex3f(newwidth- width,size*2,0);
			glVertex3f(newwidth- width,size,0);
			glColor4f(1,1,1,1);
		glEnd();	
		newwidth += (0.1*i);
		glPopMatrix();
		newwidth += width;
		updateItems(creators[i].createstage,i);
	}
}
void initCreators(){
	for(int i = 0; i<4; i++){
		// stel de creators in
		creators[i].nummer = i;
		creators[i].createstage = 0;
		creators[i].damage = 0;
		creators[i].infobordHeight = 0;
		creators[i].speed = 0;
		creators[i].weight = 0;
		updateCreators(i,0,false);
	}
}
void updateCreators(int selectedcreator, int selecteditem, bool accept){
	ItemRotation += 6.0; if(ItemRotation >= 360) ItemRotation = 0;
	if(accept) creators[selectedcreator].createstage++;	
	if(creators[selectedcreator].createstage >= 6) creators[selectedcreator].createstage = 5;

	switch(selecteditem){
	case 0 :	creators[selectedcreator].rotateLB= true; creators[selectedcreator].rotateLU =false; creators[selectedcreator].rotateRU = false; creators[selectedcreator].rotateRB = false;
		break;
	case 1 :	creators[selectedcreator].rotateLB=false; creators[selectedcreator].rotateLU =true; creators[selectedcreator].rotateRU = false; creators[selectedcreator].rotateRB = false;
		break;
	case 2 :	creators[selectedcreator].rotateLB=false; creators[selectedcreator].rotateLU = false; creators[selectedcreator].rotateRU = true; creators[selectedcreator].rotateRB = false;
		break;
	case 3 :	creators[selectedcreator].rotateLB=false; creators[selectedcreator].rotateLU = false; creators[selectedcreator].rotateRU = false; creators[selectedcreator].rotateRB = true;
		break;
	}
}