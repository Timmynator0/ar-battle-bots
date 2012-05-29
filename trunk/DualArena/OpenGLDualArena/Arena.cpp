#include "Chainsaw.h"
#include "Crate.h"
#include "Ramp.h"
#include "Arena.h"
#include "BramsPrimitives.h"
#include <string>
bool isTextureLoaded = false;
#define TEXTURE_COUNT 5
float y = 0.0f;
bool count = false;

double tx =0;	// used for the translation of the test cube
double ty =2;
double tz = 0; 
GLuint textures[TEXTURE_COUNT];
const char *TextureFiles[TEXTURE_COUNT] =
{"arena_floor.tga", "arena-muur.tga",
"crate.tga","stainless-steel.tga", "chainwheel.tga"};


void Stringtest(GLfloat x, GLfloat y, char *text)
  {
    char *p;

    glPushMatrix();
    glTranslatef(x, y, 0);
    for (p = text; *p; p++)
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *p);
    glPopMatrix();
  }

/*
*	@parameters Object1 (coordinates) object2 (coordinates)
*	@returns true if a collision is detected between object 1 and object 2
*/
bool checkCollision(float x1, float y1, /*float z1,*/ float x2, float y2/*, float z2*/)
{
	if(y1 == y2-4 && x1 == x2 || y1 == y2-4 && x1 == x2+1  || y1==y2-4 && x1 == x2-1)
    {
		return true;
    }
    //bottom of red colides with other cube
    if(y1 == y2 && x1 == x2 &&   y1 == y2 && x1 == x2+1 || y1 == y2 && x1 == x2-1)
    {
		return true;
    }
    //right of red
    if(x1==x2-2&&y1==y2-2 || x1==x2-2 && y1 == y2-3 || x1 == x2-2 && y1 == y2-1)
    {
		return true;
    }
    //left of red
    if(x1==x2+2&&y1==y2-2 || x1==x2+2&&y1==y2-3 || x1==x2+2&&y1==y2-1)
    {
        return true;
	}
	return false;
}

void Display(void)
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0,65,-60,0,0,0,0,1,0);
	if(!isTextureLoaded)
	{
		isTextureLoaded = true;
		// het laden van de texture voor de achtergrond
		glGenTextures(TEXTURE_COUNT, textures);
		for(int i= 0; i < TEXTURE_COUNT; i++)
		{
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			printf("loading %s\n",TextureFiles[i]);
			LoadTGATexture(TextureFiles[i], GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
		}
	}
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	glBegin(GL_QUADS);
		//begin kubus
		//onderkant5
	glColor3f(1,1,1);
	Stringtest(1,1,"test");
	glTexCoord2f(0,1);	glVertex3f(-50.0f,0.0f,-50.0f); 
	glTexCoord2f(0,0);	glVertex3f(-50.0f,0.0f,50.0f);
	glTexCoord2f(1,0);	glVertex3f(50.0f,0.0f,50.0f);
	glTexCoord2f(1,1);	glVertex3f(50.0f,0.0f,-50.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);
	
		//achterste muur
	glTexCoord2f(1,0.2);	glVertex3f(50.0f,0.0f,50.0f);
	glTexCoord2f(1,1);	glVertex3f(50.0f,100.0f,50.0f);
	glTexCoord2f(0,1);	glVertex3f(-50.0f,100.0f,50.0f);
	glTexCoord2f(0,0.2);	glVertex3f(-50.0f,0.0f,50.0f);
		
		//rechter muur
	glTexCoord2f(1,0.2);	glVertex3f(-50.0f,0.0f,50.0f);
	glTexCoord2f(1,1);	glVertex3f(-50.0f,100.0f,50.0f);
	glTexCoord2f(0,1);	glVertex3f(-50.0f,100.0f,-50.0f);
	glTexCoord2f(0,0.2);	glVertex3f(-50.0f,0.0f,-50.0f);
		
		//linker muur
	glTexCoord2f(1,0.2);	glVertex3f(50.0f,0.0f,50.0f);
	glTexCoord2f(1,1);	glVertex3f(50.0f,100.0f,50.0f);
	glTexCoord2f(0,1);	glVertex3f(50.0f,100.0f,-50.0f);
	glTexCoord2f(0,0.2);	glVertex3f(50.0f,0.0f,-50.0f);

	glEnd();

	//Ramp();
	glBindTexture(GL_TEXTURE_2D,textures[3]);
	Ramp();
	//crate
	glBindTexture(GL_TEXTURE_2D,textures[2]);
	Crate(20,5,20);
	//chainsaws
	glBindTexture(GL_TEXTURE_2D,textures[4]);
	Chainsaw(-23.25,y,0);
	Chainsaw(-27.25,y,0);
	Chainsaw(23.25,y,0);
	Chainsaw(27.25,y,0);


	//test cube for collision detection
	glPushMatrix();
	glTranslatef(tx,ty,tz);
	createCube(2,2,2,0,0,0);
	glPopMatrix();

	glutSwapBuffers();
}

void Reshape(GLint width, GLint height)
{
	glViewport(0,0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.01, 1000);
	glMatrixMode(GL_MODELVIEW);
}



void InitGraphics(void)
{

}

void MouseButton(int button, int state, int x, int y)
{
}

void MouseMotion(int x, int y)
{
}

void IdleFunc(void)
{
	if(y>=0)
	{
		count = true;
	}
	else if(y<=-6)
	{
		count = false;
	}
	if(count)
	{
		y-=.01;
	}
	else
	{
		y+=0.01;
		//printf("%02d", y);
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	printf("%c\n",key);
	switch (key)
	{
	case 27:             // ESCAPE key
		exit (0);
		break;
	case 'w':
		if(!checkCollision(0,50,0,tz+4))
			tz++;
		break;
	case 'a':
		if(!checkCollision(50,0,tx+3,0))
		tx++;
		break;
	case 's':
		if(!checkCollision(0,-50,0,tz))
		tz--;
		break;
	case 'd':
		if(!checkCollision(-50,0,tx-2,0))
		tx--;
		break;
	case 'e':
		ty++;
		break;
	case 'q':
		ty--;
		break;

	}
	printf("x:%d,z:%d\n",tx,tz);
}

int main(int argc, char* argv[])
{
	glutInit (&argc, argv);
	glutInitWindowSize (1024, 768);
	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow ("GLUT example");
	// Initialize OpenGL graphics state
	InitGraphics();
	// Register callbacks:
	glutDisplayFunc (Display);
	glutReshapeFunc (Reshape);
	glutKeyboardFunc (Keyboard);
	glutMouseFunc (MouseButton);
	glutMotionFunc (MouseMotion);
	glutIdleFunc (IdleFunc);
	// Turn the flow of control over to GLUT
		glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glutMainLoop ();
	return 0;
}
