// Triangle.cpp
#include <iostream>
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>
#include <stdio.h>
#include "Arena.h"

#include "loadTGA.h"
#include "robotCreateScreen.h"
#include "ObjModel.h"

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT
#include <GL/freeglut.h>            // Windows FreeGlut equivalent
#endif
GLBatch	triangleBatch;
GLShaderManager	shaderManager;
GLuint              textureID;
GLGeometryTransform	transformPipeline;
vector<ObjModel*> models;

int screenwidth= 1024, screenheight = 700;
int tex = 0;
int gamestage = 0; // 0 is niets/net opgestart, 1 is wachten op spelers, 2 is robot creeeren, 3 is spelen, 4 is einduitslag
int h,w ;
int selectedCreator= 0,selectedCreatorItem= 0;
bool acceptItem = false;
float rotation = 0;

void ChangeSize(int w, int h)
    {
	
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90, 1, 0.1, 150);
		switch(gamestage)
		{
		case 2:	
			gluLookAt(0,0,-2, 0,0,0, 0,1,0);
			break;
		case 3:
			gluLookAt(0,65,-60,0,0,0,0,1,0);
			break;
		}
		glMatrixMode(GL_MODELVIEW);
	
    }

void MouseButton(int button, int state, int x, int y)
{
	std::cout << "button : "<<button<< "state : "<<state<< std::endl;
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
}
void Keyboard(unsigned char key, int x, int y)
{
	std::cout << "key : "<<key<< std::endl;
	switch(gamestage){
	case 0:		//opstarten
		break;
	case 1:		//spelers queue
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
		break;
	case 4:		//uitslag
		break;
	}
	
	if(key == 27) exit (0); //escape key
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
//	


	glLoadIdentity();
	
    //glBindTexture(GL_TEXTURE_2D, textureID);
	glPushMatrix();
	//glRotated(rotation,0,1,0);
	if(rotation >= 360 ) rotation = 0;
	switch(gamestage){
	case 0:		//opstarten
		break;
	case 1:		//spelers queue
		break;
	case 2:		//robot creeeren
		
		createRCSBackground();
		break;
	case 3:		//het gevecht
		ArenaDisplay();
		break;
	case 4:		//uitslag
		break;
	}
	glPopMatrix();



	glutSwapBuffers();
	
}
void IdleFunc(void)
{
	switch(gamestage){
	case 0:		//opstarten
		break;
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
	//if(rotate){
		rotation += 1;

		glutPostRedisplay();
	//}
}

int main(int argc, char* argv[])
	{
	//gltSetWorkingDirectory(argv[0]);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
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
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glColorMaterial(GL_FRONT_AND_BACK,GL_EMISSION);
	glEnable(GL_COLOR_MATERIAL);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	shaderManager.InitializeStockShaders();
	shaderManager.InitializeStockShaders();
	gamestage = 3;
	//laadModellen();
    initCreators(models);
	glutMainLoop();
	return 0;
	}
