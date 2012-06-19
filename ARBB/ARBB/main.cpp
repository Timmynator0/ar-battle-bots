// Triangle.cpp
#include <iostream>
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>
#include <stdio.h>
#include "arena.h"
#include "awaitingPlayerScreen.h"
#include "endScreen.h"

#include "loadTGA.h"
#include "robotCreateScreen.h"
#include "ObjModel.h"
#include "Robot.h"

#include "faceCam.h"
#include "cv.h"
#include "highgui.h"
#include <stdlib.h>

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT
#include <GL/freeglut.h>            // Windows FreeGlut equivalent
#endif

#define Main_TEXTURE_COUNT 1

GLBatch	triangleBatch;
GLShaderManager	shaderManager;

GLuint maintextures[TEXTURE_COUNT];
const char *mainTextureFiles[TEXTURE_COUNT] =
{ "opstartscherm.tga"};
GLGeometryTransform	transformPipeline;
vector<ObjModel*> models;
IplImage *faceBackground;

int screenwidth= 1024, screenheight = 700;
int tex = 0,opstartcount = 0;
int gamestage = 0; // 0 is niets/net opgestart, 1 is wachten op spelers, 2 is robot creeeren, 3 is spelen, 4 is einduitslag
int h,w ;
int selectedCreator= 0;
	int selectedCreatorItem= 0;
bool acceptItem = false;
float rotation = 0;
bool firsttime = true,Loaded = false;

void ChangeSize(int w, int h)
    {
	
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90, 1, 0.1, 150);
		switch(gamestage)
		{
		case 1:
			gluLookAt(0,75,-10,0,0,50,0,1,0);
			break;
		case 2:	
			gluLookAt(0,0,-2, 0,0,0, 0,1,0);
			break;
		case 3:
			gluLookAt(0,75,-60,0,0,0,0,1,0);
			break;
		case 4:
			gluLookAt(0,45,-10,0,5,50,0,1,0);
			break;
		}
		glMatrixMode(GL_MODELVIEW);
	
    }

void MouseButton(int button, int state, int x, int y)
{
	std::cout << "button : "<<button<< "state : "<<state<< std::endl;
}
void startScreen()
{
	if(!Loaded)
	{
		glGenTextures(Main_TEXTURE_COUNT, maintextures);
		for(int i= 0; i < Main_TEXTURE_COUNT; i++)
		{
			glBindTexture(GL_TEXTURE_2D, maintextures[i]);
			LoadTGATexture(mainTextureFiles[i], GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
		}
		Loaded = true;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-screenwidth,screenwidth,-screenheight,screenheight,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, maintextures[0]);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex3f(-screenwidth,-screenheight,0.2);
		glTexCoord2f(0,1); glVertex3f(-screenwidth,screenheight,0.2);
		glTexCoord2f(1,1); glVertex3f(screenwidth,screenheight,0.2);
		glTexCoord2f(1,0); glVertex3f(screenwidth,-screenheight,0.2);
	glEnd();
}
void laadModellen()
{
	models.push_back(new ObjModel("models/previews/triangle.obj"));
	models.push_back(new ObjModel("models/previews/cube.obj"));
	models.push_back(new ObjModel("models/previews/cylinder.obj"));
	models.push_back(new ObjModel("models/previews/penta.obj"));
	models.push_back(new ObjModel("models/previews/aluTriangle.obj"));
	models.push_back(new ObjModel("models/previews/carbonTriangle.obj"));
	models.push_back(new ObjModel("models/previews/steelTriangle.obj"));
	models.push_back(new ObjModel("models/previews/woodTriangle.obj"));
	models.push_back(new ObjModel("models/previews/aluCube.obj"));
	models.push_back(new ObjModel("models/previews/carbonCube.obj"));
	models.push_back(new ObjModel("models/previews/steelCube.obj"));
	models.push_back(new ObjModel("models/previews/woodCube.obj"));
	models.push_back(new ObjModel("models/previews/aluCylinder.obj"));
	models.push_back(new ObjModel("models/previews/carbonCylinder.obj"));
	models.push_back(new ObjModel("models/previews/steelCylinder.obj"));
	models.push_back(new ObjModel("models/previews/woodCylinder.obj"));
	models.push_back(new ObjModel("models/previews/aluPenta.obj"));
	models.push_back(new ObjModel("models/previews/carbonPenta.obj"));
	models.push_back(new ObjModel("models/previews/steelPenta.obj"));
	models.push_back(new ObjModel("models/previews/woodPenta.obj"));
	models.push_back(new ObjModel("models/previews/wapenSchanier.obj"));
	models.push_back(new ObjModel("models/previews/Hamer.obj"));
	models.push_back(new ObjModel("models/previews/singelPin.obj"));
	models.push_back(new ObjModel("models/previews/dubbelPin.obj"));
	models.push_back(new ObjModel("models/previews/zaagHouvast.obj"));
	models.push_back(new ObjModel("models/previews/zaag.obj"));
	models.push_back(new ObjModel("models/previews/klauw.obj"));
	models.push_back(new ObjModel("models/previews/grijper.obj"));
	models.push_back(new ObjModel("models/previews/flipper.obj"));
	models.push_back(new ObjModel("models/previews/pushbar.obj"));
	models.push_back(new ObjModel("models/previews/maaier.obj"));
	models.push_back(new ObjModel("models/previews/vlammenwerper.obj"));
	models.push_back(new ObjModel("models/previews/pneumaticPin.obj"));
}
void Keyboard(unsigned char key, int x, int y)
{
	std::cout << "key : "<<key<< std::endl;
	switch(gamestage){
	case 0:		//opstarten
		break;
	case 1:		//spelers queue
		if( key == ' '){
				gamestage++;
				ChangeSize(screenwidth,screenheight);
		}
		break;
	case 2:		//robot creeeren
		switch (key)
		{
		case '1': selectedCreator = 0;	//deze 4 worden later gewoon 4 losse handen ipv een toets
			break;
		case '2': selectedCreator = 1;
			break;
		case '3': selectedCreator = 2;
			break;
		case '4': selectedCreator = 3;
			break;
		case 'q': selectedCreatorItem = 0; // deze 5 worden de handgebaren voor 0 - 5 (waarbij 0 de acceptatie is)
			break;
		case 'w': selectedCreatorItem = 1;
			break;
		case 'e': selectedCreatorItem = 2;
			break;
		case 'r': selectedCreatorItem = 3;
			break;
		case 't': acceptItem = true;
			break;
		}
		updateCreators(selectedCreator, selectedCreatorItem,acceptItem);
		acceptItem = false;
		break;
	case 3:		//het gevecht
		KeyboardArena(key, x, y);
		if( key == ' '){
				gamestage++;
				ChangeSize(screenwidth,screenheight);
		}
		break;
	case 4:		//uitslag
		break;
	}
	
	if(key == 27) //escape key
		exit (0); 
}

void SpecialKeys(int key, int x, int y)
    {
	std::cout << "specialkey : "<<key<< std::endl;
}

void RenderScene(void)
	{
	float x = 2,y= 1,z=1;
   // static GLfloat vLightPos [] = { 1.0f, 1.0f, 0.0f };
    static GLfloat vWhite [] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f );

	glLoadIdentity();
	
    //glBindTexture(GL_TEXTURE_2D, textureID);
	glPushMatrix();
	//glRotated(rotation,0,1,0);
	if(rotation >= 360 ) rotation = 0;
	switch(gamestage){
	case 0:		//opstarten
		startScreen();
		break;
	case 1:		//spelers queue
		createAPSBackground(screenwidth,screenheight);
		break;
	case 2:		//robot creeeren
		if(createRCSBackground()){
			gamestage++;
			for(int i=0;i<4;i++)
			{			
				setRobots(*getRobots(i));
				setESRobots(*getRobots(i));
			}
			ChangeSize(screenwidth,screenheight);
		}
		else {
			increaseRotation();
			break;
		}
	case 3:		//het gevecht
		ArenaDisplay();
		break;
	case 4:		//uitslag
		createESBackground(screenwidth,screenheight);
			ChangeSize(screenwidth,screenheight);
		break;
	}
	glPopMatrix();



	glutSwapBuffers();
	
}
void IdleFunc(void)
{
	Sleep(15);
	switch(gamestage){
	case 0:		//opstarten
		opstartcount++;
		if(opstartcount > 500){
			gamestage ++;
			ChangeSize(screenwidth,screenheight);
		}
		else break;
	case 1:		//spelers queue
		break;
	case 2:		//robot creeeren
		updateCreators(selectedCreator, selectedCreatorItem,acceptItem);
		break;
	case 3:		//het gevecht
		IdleFuncArena();
		break;
	case 4:		//uitslag
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
	{
	//gltSetWorkingDirectory(argv[0]);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(screenwidth, screenheight);
	
	glutCreateWindow("Kontje");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
	glutKeyboardFunc (Keyboard);
	glutIdleFunc (IdleFunc);
	glutMouseFunc(MouseButton);
	glutSpecialFunc(SpecialKeys);
	
	GLenum err = glewInit();
	if (GLEW_OK != err) 
	{
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glColorMaterial(GL_FRONT_AND_BACK,GL_EMISSION);
	glEnable(GL_COLOR_MATERIAL);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	shaderManager.InitializeStockShaders();
	gamestage = 0;
	laadModellen();
    initCreators(models);
	initAPS(models);
	initES(models);
	glutMainLoop();
	return 0;
	}
