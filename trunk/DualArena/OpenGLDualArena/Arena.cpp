#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

#include "FreeImage.h"

#include "Ramp.h"
#include "Arena.h"


double eyex = 0;
double eyey = 20;
double eyez = -60;
double upy = 1;
double centerx,centery,centerz,upx,upz = 0;
unsigned int textureId;
void Display(void)
{

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	gluLookAt(eyex,eyey,eyez,centerx,centery,centerz,upx,upy,upz);

	glBegin(GL_QUADS);
		//begin kubus
	
		//onderkant
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-50.0f,0.0f,-50.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-50.0f,0.0f,50.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(50.0f,0.0f,50.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(50.0f,0.0f,-50.0f);
		
		//achterste muur
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(50.0f,0.0f,50.0f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(50.0f,50.0f,50.0f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-50.0f,50.0f,50.0f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-50.0f,0.0f,50.0f);
		
		//rechter muur
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-50.0f,0.0f,50.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-50.0f,50.0f,50.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-50.0f,50.0f,-50.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-50.0f,0.0f,-50.0f);
		
		//linker muur
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(50.0f,0.0f,50.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(50.0f,50.0f,50.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(50.0f,50.0f,-50.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(50.0f,0.0f,-50.0f);
	glEnd();
	Ramp();

	
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
	case 'q':
		
		break;
	case 'w':
		if(eyez!= -20)
			eyez +=5;
		break;
	case 'a':
		centerx += 1;
		eyex += 1;
		break;
	case 's':
		if(eyez!= -70)
			eyez -=5;
		break;
	case 'd':
		centerx -= 1;
		eyex -= 1;
		break;

	}

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
	
	glutMainLoop ();
	return 0;
}
