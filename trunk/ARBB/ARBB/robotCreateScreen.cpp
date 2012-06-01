#include <iostream>
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>
#include <stdio.h>
#include <time.h>

#include "loadTGA.h"
#include "robotCreateScreen.h"
#include "BramsPrimitives.h"
#include "ObjModel.h"

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT
#include <GL/glut.h>            // Windows FreeGlut equivalent
#endif
#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif
#define TEXTURE_COUNT 2
vector<ObjModel*> RCSmodels;

GLuint textures[TEXTURE_COUNT];
const char *TextureFiles[TEXTURE_COUNT] =
{ "robotcreator.tga","banden.tga" };

CREATOR				creators[4];
float				ItemRotation = 0;

void updateItems(int stage, int place){
	srand ( time(NULL) );
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
		createDiamondCube(size,size, size/5);
		glPopMatrix();

		// pentagon
		glPushMatrix();
		glTranslated(0,0.4,0);
			glPushMatrix();
			if(creators[place].rotateRU)glRotated(ItemRotation,0,1,0);
		createPentagon(size,size,size/5);
		glPopMatrix();
		glPopMatrix();

		// cirkel 
		glPushMatrix();
		glTranslated(0.25,0.6,-size/2);
			glPushMatrix();
			if(creators[place].rotateLU)glRotated(ItemRotation,0,1,0);
			createCylinder(size/2, size,12,(size/2.5),1,false,0,0,0);
		glPopMatrix();
		glPopMatrix();

		//triangle
		glPushMatrix();
		glTranslated(0.25,0,0);
				glPushMatrix();
			if(creators[place].rotateLB)glRotated(ItemRotation,0,1,0);
		createTriangle(size,size,size/5);
		glPopMatrix();
		glPopMatrix();
		break;
	case 2:						//----------------Wielen Selectie --------------------	
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glPushMatrix();
		glTranslated(0,0.15,0);
		//houten Wielen
			glPushMatrix();
			if(creators[place].rotateRB) glRotated(ItemRotation,0,1,0);
			createCylinder(size/2,size,20,size/5,1,true,0.125,0.875,0.125);
		glPopMatrix();

		//rubberen Banden
		glPushMatrix();
		glTranslated(0,0.4,0);
			glPushMatrix();
			if(creators[place].rotateRU)glRotated(ItemRotation,0,1,0);
			createCylinder(size/2,size,20,size/5,1,true,0.375,0.875,0.125);
		glPopMatrix();
		glPopMatrix();

		//metalen wielen 
		glPushMatrix();
		glTranslated(0.3,0.4,-size/2);
			glPushMatrix();
			if(creators[place].rotateLU)glRotated(ItemRotation,0,1,0);
			createCylinder(size/2,size,20,size/5,1,true,0.625,0.875,0.125);
		glPopMatrix();
		glPopMatrix();

		//rupsbanden 
		glPushMatrix();
		glTranslated(0.25,0,0);
			glPushMatrix();
			if(creators[place].rotateLB)glRotated(ItemRotation,0,1,0);	
			createCylinder(size, size,20,size/5,1,true,0.875,0.875,0.125);	
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		break;
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glPushMatrix();
		glTranslated(0,0.15,0);
		//hout frame
			glPushMatrix();
			if(creators[place].rotateRB) glRotated(ItemRotation,0,1,0);
			glPushMatrix();
			glRotated(30,1,0,0);
			createCube(size/2,size/2,size/2,0,0.28,0.0625);
		glPopMatrix();
		glPopMatrix();
		
		size = size / 1.5;
		//staal frame
		glPushMatrix();
		glTranslated(0,0.4,0);
			glPushMatrix();
			if(creators[place].rotateRU)glRotated(ItemRotation,0,1,0);
			glPushMatrix();
			glTranslated(0,size,0);
			createCube(size,size/4,size*0.75,0.25,0.28,0.0625);
			glPopMatrix();
			createCube(size,size,size/5,0.25,0.28,0.0625);
			glPushMatrix();
			glTranslated(0,-size,0);
			createCube(size,size/4,size*0.75,0.25,0.28,0.0625);
			glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		//aluminium frame
		glPushMatrix();
		glTranslated(0.3,0.4,-size/2);
			glPushMatrix();
			if(creators[place].rotateLU)glRotated(ItemRotation,0,1,0);
			glPushMatrix();
			glRotated(67.5,1,0,0);
			createCube(size,size/5,size,0.5,0.28,0.0625);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		//carbon frame
		glPushMatrix();
		glTranslated(0.25,0,0);
			glPushMatrix();
			if(creators[place].rotateLB)glRotated(ItemRotation,0,1,0);	
			glPushMatrix();
			glRotated(67.5,1,0,0);
			createCube(size,size/10,size,0.75,0.28,0.0625);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		
		break;
	case 3:						//----------------Wapen 1 Selectie --------------------	
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glPushMatrix();
		glTranslated(0,0.15,0);
		//Hamer
			glPushMatrix();
			if(creators[place].rotateRB) glRotated(ItemRotation,0,1,0);
			glPushMatrix();// zet de hamer in een schuine hoek
			glRotated(45,1,0,0);
			createCylinder(size/5,size/3,10,size*1.5,1,true,0.125,0.875,0.125);
			glPushMatrix();glPushMatrix(); //de kop word op de steel getranslated, en geroteerd
			glRotated(90,1,0,0);
			glTranslated(0,0,-size*0.75);
			createCylinder(size/4,size/4,10,size*1.5,1,true,0.875,0.45,0.1);
			glPopMatrix();glPopMatrix();glPopMatrix(); // eind van kop translatie en rotatie, en hamer rotatie
		glPopMatrix();

		//CirkelZaag
		glPushMatrix();
		glTranslated(0,0.4,0);
			glPushMatrix();
			if(creators[place].rotateRU)glRotated(ItemRotation,0,1,0);
			glPushMatrix();// zet de hamer in een schuine hoek
			glRotated(45,1,0,0);
			createCylinder(size/5,size/3,10,size*1.5,1,true,0.625,0.875,0.125);
			glPushMatrix(); //de zaag word op de steel geroteerd
			glRotated(90,0,1,0);
			createCylinder(size,size,60,size/10,1,true,0.625,0.625,0.125);
			glPopMatrix();glPopMatrix(); // eind van zaag rotatie, en hamer rotatie
		glPopMatrix();
		glPopMatrix();

		//spike
		glPushMatrix();
		glTranslated(0.3,0.4,-size/2);
			glPushMatrix();
			if(creators[place].rotateLU)glRotated(ItemRotation,0,1,0);
			glPushMatrix();// zet de hamer in een schuine hoek
			glRotated(45,1,0,0);
			createCube(size/5,size/5,size,0.25,0.28,0.0625);
			glPushMatrix();glPushMatrix(); //de kop word op de steel getranslated, en geroteerd
			glRotated(180,0,0,1);
			glTranslated(0,size/5,-size*0.75);
			createPyramid(size/5,size, size/5, 0.5,0.28,0.05);
			glPopMatrix();glPopMatrix();glPopMatrix(); // eind van kop translatie en rotatie, en hamer rotatie
		glPopMatrix();
		glPopMatrix();

		//dubbelspike 
		glPushMatrix();
		glTranslated(0.25,0,0);
			glPushMatrix();
			if(creators[place].rotateLB)glRotated(ItemRotation,0,1,0);	
			glPushMatrix();// zet de hamer in een schuine hoek
			glRotated(45,1,0,0);
			createCube(size/5,size/5,size,0.25,0.28,0.0625);
			glPushMatrix();glPushMatrix(); //de kop word op de steel getranslated, en geroteerd
			glTranslated(0,size/5,-size*0.75);			
			createPyramid(size/5,size, size/5, 0.5,0.28,0.05);
			glPopMatrix(); glPushMatrix();
			glRotated(180,0,0,1);
			glTranslated(0,size/5,-size*0.75);
			createPyramid(size/5,size, size/5, 0.5,0.28,0.05);
			glPopMatrix();glPopMatrix();glPopMatrix(); // eind van kop translatie en rotatie, en hamer rotatie
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		break;
	case 4:						//----------------Wapen 2 Selectie --------------------	
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glPushMatrix();
		glTranslated(0,0.05,0);
		//Klauw (pakt van boven/onder kan optillen)
			glPushMatrix();
			if(creators[place].rotateRB) glRotated(ItemRotation,0,1,0);
			glPushMatrix();// zet de hamer in een schuine hoek
			glRotated(60,1,0,0);
			createCube(size/5,size/5,size/1.5,0.5,0.28,0.0625);

			for(int i = -1; i<2;i+=2){
			glPushMatrix();
			glTranslated(0,i*size/4,-size/1.5);
			glPushMatrix();
			glRotated(i*30,1,0,0);
			createCube(size/7,size/7,size/3,0.5,0.28,0.0625);
			glPopMatrix();
			
			glPushMatrix();
			glTranslated(0,i*size/5,-size/2);
			createCube(size/7,size/7,size/3,0.5,0.28,0.0625);		
			
			glPushMatrix();
			glTranslated(0,i*-size/5,-size/2);
			glPushMatrix();
			glRotated(-30*i,1,0,0);
			createCube(size/7,size/7,size/3,0.5,0.28,0.0625);
			glPopMatrix();glPopMatrix();
			glPopMatrix();

			glPopMatrix();
			}
			glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		//Grijper (pakt van links/rechts en kan vasthouden
		glPushMatrix();
		glTranslated(0,0.4,0);
			glPushMatrix();
			if(creators[place].rotateRU)glRotated(ItemRotation,0,1,0);
			glPushMatrix();// zet de hamer in een schuine hoek
			glRotated(90,1,0,0);
			for(int i = -1; i<2;i+=2){
			glPushMatrix();
			glTranslated(0,i*size/1.5,-size/1.5);
			glPushMatrix();
			glRotated(i*30,1,0,0);
			createCube(size/7,size/7,size/3,0.5,0.28,0.0625);
			glPopMatrix();
			
			glPushMatrix();
			glTranslated(0,i*size/5,-size/2);
			createCube(size/7,size/7,size/3,0.5,0.28,0.0625);		
			
			glPushMatrix();
			glTranslated(0,i*-size/5,-size/2);
			glPushMatrix();
			glRotated(-30*i,1,0,0);
			createCube(size/7,size/7,size/3,0.5,0.28,0.0625);
			glPopMatrix();glPopMatrix();
			glPopMatrix();

			glPopMatrix();
			}
			glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		//Flipper ( gooit een voertuig omhoog)
		glPushMatrix();
		glTranslated(0.3,0.6,-size/2);
			glPushMatrix();
			if(creators[place].rotateLU)glRotated(ItemRotation,0,1,0);
			glPushMatrix();// zet de hamer in een schuine hoek
			glRotated(-120,1,0,0);
			createCube(size/5,size/5,size/1.5,0.5,0.28,0.0625);
			glPushMatrix();
			glTranslated(0,size/6,-size/1.5);
			glPushMatrix();
			glRotated(30,1,0,0);
			createCube(size/7,size/7,size/3,0.5,0.28,0.0625);
			glPopMatrix();
			
			glPushMatrix();
			glTranslated(0,size/5,-size/2);
			createCube(size/7,size/7,size/3,0.5,0.28,0.0625);		
			glPopMatrix();

			glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		//Sidebars ( 2 balken aan de zijkant, die voertuigen weg kunne duwe /grijper openen) 
		glPushMatrix();
		glTranslated(0.25,0.15,0);
			glPushMatrix();
			if(creators[place].rotateLB)glRotated(ItemRotation,0,1,0);
			glPushMatrix();
			glRotated(60,1,0,0);
			for(int ii= -1; ii<2; ii+=2){
				glPushMatrix();
				glTranslated(0,ii*size,0);
				glPushMatrix();
				glRotated(ii*-90,1,0,0);

				createCube(size,size/4,size/8,0.25,0.28,0.0625);
				for(int i=-1;i<2;i++){
					glPushMatrix();
					glTranslated(i*size/1.4,0,-size/2.5);
					createCube(size/10,size/10,size/3, 0.5,0.28,0.0625);
					glPopMatrix();
				}
				glPopMatrix();
				glPopMatrix();
			}
			glPopMatrix();

		glPopMatrix();
		glPopMatrix();
		break;
	case 5:						//----------------Wapen 3 Selectie --------------------	
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glPushMatrix();
		glTranslated(0,0.15,0);
		//Maaier (geval Op het voertuig dat rondraait)
			glPushMatrix();
			if(creators[place].rotateRB) glRotated(ItemRotation*2,0,1,0);
			glPushMatrix();
			glRotated(45,0,0,1);
			for(int i = 0; i<3; i++){
				glPushMatrix();
				glRotated(120*i, 0,1,0);
				glTranslated(size/3,0,0);
				createCube(size/2,size/10,size/10, 0.5,0.28,0.0625);
				
				glPushMatrix();
				glTranslated(size/1.5,-size/6,0);
				glRotated(-60,0,0,1);
				createCube(size/2.5,size/10,size/10, 0.5,0.28,0.0625);

				glPushMatrix();
				glTranslated(size/2,0,0);
				glRotated(-30,0,0,1);
				createCube(size/10,size/10, size/1.4, 0.25,0.28,0.0625);

				for(int ii = -1; ii<2; ii++){
					glPushMatrix();
					glTranslated(0,size/8,ii*size/2);
					glRotated(-30,0,0,1);
					createPyramid(size/8,size/2,size/8, 0.5,0.28,0.05);
					glPopMatrix();
				}

				glPushMatrix();
				glRotated(60,1,0,0);
				glTranslated(0,size/2,size*1.1);
				createCube(size/10,size/10, size/1.4, 0.25,0.28,0.0625);

				for(int ii = -1; ii<2; ii++){
					glPushMatrix();
					glTranslated(0,size/8,ii*size/2);
					glRotated(-30,0,0,1);
					createPyramid(size/8,size/2,size/8, 0.5,0.28,0.05);
					glPopMatrix();
				}

				glPopMatrix();
				glPopMatrix();
				glPopMatrix();
				glPopMatrix();
			}
			glPopMatrix();
		glPopMatrix();

		//Vlammenwerper
		glPushMatrix();
		glTranslated(0,0.4,0);
			glPushMatrix();
			if(creators[place].rotateRU)glRotated(ItemRotation,0,1,0);
			glPushMatrix();
			glRotated(45,0,0,1);
			for(int i = 0; i<6; i++){
				glPushMatrix();
				glRotated(60*i, 0,1,0);
				glTranslated(size/8,0,0);
				createCube(size/2,size/10,size/10, 0.75,0.28,0.0625);
				
				glPushMatrix();
				glTranslated(size/1.5,0,0);
				createCube(size/7,size/9,size/9, 0.75,0.28,0.0625);

				glPushMatrix();
				glTranslated(size/2,0,0);
				int fo = rand() % 3;
				for(int ii=0; ii<1;ii++){
					glPushMatrix();
					glRotated(30*ii,1,0,0);
					glBegin(GL_TRIANGLE_STRIP);
						glTexCoord2f(0.17*fo,0.25);				glVertex3f(size/3,0,size/3);		//leftback
						glTexCoord2f(0.17*fo,0);					glVertex3f(-size/3,0,size/3);		//leftfront
						glTexCoord2f(0.17+0.13*fo,0.25);			glVertex3f(size/3,0,-size/3);		//rightfront
						glTexCoord2f(0.17+0.13*fo,0);				glVertex3f(-size/3,0,-size/3);		//rightback
					glEnd();
					glPopMatrix();
				}
				glPopMatrix();
				glPopMatrix();
				glPopMatrix();
			}
			glPopMatrix();

		glPopMatrix();
		glPopMatrix();

		//Pneumatic pin (geeft een stoot recht vooruit)
		glPushMatrix();
		glTranslated(0.3,0.4,-size/2);
			glPushMatrix();
			if(creators[place].rotateLU)glRotated(ItemRotation,0,1,0);			
				glPushMatrix();
				glTranslated(0,0,-size/2);
				createCylinder(size/4,size/4,10, size/1.5,1,true, 0.625,0.625,0.125);			
				glPopMatrix();
				createCylinder(size/6,size/6,10,size/2,1,true, 0.625,0.625,0.125);		
		glPopMatrix();
		glPopMatrix();

		//geen 
		glPushMatrix();
		glTranslated(0.25,0,0);
			glPushMatrix();
			if(creators[place].rotateLB)glRotated(ItemRotation,0,1,0);	
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		break;
	case 6:
		break;
	}
	glPopMatrix();
	glPopMatrix();
	glColor4f(1,1,1,1);
}

void robotPreview(int place, int items[])
{
	glPushMatrix();
	glTranslated(-1.4+0.9*place,-1.1,-0.2);
	glPushMatrix();
	glScaled(0.2,0.4,0.1);	
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	float size = 0.2;
	if(items[0] != 0){
		switch(items[0]){
		case 1: // triangle
			switch(items[1]){
			case 0: RCSmodels[0]->draw(); break;
			case 1: RCSmodels[5]->draw(); break;
			case 2: RCSmodels[4]->draw(); break;
			case 3: RCSmodels[6]->draw(); break;
			case 4: RCSmodels[7]->draw(); break;
			}break;
		case 2: // circle
			switch(items[1]){
			case 0: RCSmodels[2]->draw(); break;
			case 1: RCSmodels[13]->draw(); break;
			case 2: RCSmodels[12]->draw(); break;
			case 3: RCSmodels[14]->draw(); break;
			case 4: RCSmodels[15]->draw(); break;
			}break;
		case 3: // pentagon
			switch(items[1]){
			case 0: RCSmodels[3]->draw(); break;
			case 1: RCSmodels[17]->draw(); break;
			case 2: RCSmodels[16]->draw(); break;
			case 3: RCSmodels[18]->draw(); break;
			case 4: RCSmodels[19]->draw(); break;
			}break;
		case 4: // quad
			switch(items[1]){
			case 0: RCSmodels[1]->draw(); break;
			case 1: RCSmodels[9]->draw(); break;
			case 2: RCSmodels[8]->draw(); break;
			case 3: RCSmodels[10]->draw(); break;
			case 4: RCSmodels[11]->draw(); break;
			}break;
		}
	}
	glPopMatrix();
	if(items[2] != 0){
		glPushMatrix();
		glScaled(0.4,0.4,0.4);
		glPushMatrix();
		glRotated(90,0,1,0);
		switch(items[2]){
		case 4://houten Wielen
			for(int i=-1; i<2; i+=2){
				glPushMatrix();
				glTranslated(0.2*i,0,0);
				for(int ii=-1; ii<2; ii+=2){
					glPushMatrix();
					glTranslated(0.2*ii,0,0);
					createCylinder(size/2,size,20,size/5,1,true,0.125,0.875,0.125);
					glPopMatrix();
				}
				glPopMatrix();
			}
			break;
		case 3://rubberen Banden
			createCylinder(size/2,size,20,size/5,1,true,0.375,0.875,0.125);	
			break;
		case 2://metalen wielen 
			createCylinder(size/2,size,20,size/5,1,true,0.625,0.875,0.125);
			break;
		case 1://rupsbanden
			for(int i=-1; i<2; i+=2){
				glPushMatrix();
				glTranslated(0,0,0.15*i);
				createCylinder(size, size,20,size/5,1,true,0.875,0.875,0.125);
				glPopMatrix();
			} 
			break;
		}
		glPopMatrix();
		glPopMatrix();
		if(items[3] != 0){
			switch(items[3]){
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			}
			if(items[4] != 0){
				switch(items[4]){
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				}
				if(items[5] != 0){
					switch(items[5]){
					case 1:
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
					}
				}
			}
		}
	}
	glPopMatrix();
}

void createRCSBackground(){
	// de hoogte en breedte per achtergrond en een offset breedte zodat de 4 naast elkaar verschijnen
	float width = 1, height = 2 , newwidth = width *-1;
	
#ifndef TEXTURES
#define TEXTURES
	// het laden van de texture voor de achtergrond
	glGenTextures(TEXTURE_COUNT, textures);
	for(int i= 0; i < TEXTURE_COUNT; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		LoadTGATexture(TextureFiles[i], GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
	}
#endif

	//de 4 achtergronden creeeren
	for(int i =0; i<4; i++){	
	glBindTexture(GL_TEXTURE_2D, textures[0]);	
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
		robotPreview(i, creators[i].stageItems);
	}
}
void initCreators(vector< ObjModel*> modellen){
	RCSmodels = modellen;
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
	if(accept)
	{
		creators[selectedcreator].stageItems[creators[selectedcreator].createstage] = selecteditem+1;
		creators[selectedcreator].createstage++;	
		std::cout<<"creator : "<<selectedcreator<<" heeft: "<<creators[selectedcreator].stageItems[0]<<","<<creators[selectedcreator].stageItems[1]<<","<<creators[selectedcreator].stageItems[2]<<","<<creators[selectedcreator].stageItems[3]<<","<<creators[selectedcreator].stageItems[4]<<","<<creators[selectedcreator].stageItems[5]<<std::endl;
	}
	if(creators[selectedcreator].createstage >= 7) creators[selectedcreator].createstage = 6;

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