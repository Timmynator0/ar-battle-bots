#include "Chainsaw.h"
#include "Crate.h"
#include "Ramp.h"
#include "Arena.h"
#include "Robot.h"
#include <string>
#include "BramsPrimitives.h"

#define OBJECT_COUNT 1
#define STATIC_OBJECT_COUNT 4
#define TEXTURE_COUNT_ARENA 6
#define pi 3.14159265

struct Vector3d
{
	double x,y,z;
};

bool isTextureLoaded = false;
float y = 0.0f;
bool count = false;
double width,height;
int timer;

double tx =20;	// used for the translation of the test cube
double ty =2;
double tz = 0; 
Vector3d staticObject[STATIC_OBJECT_COUNT];
Vector3d moveableObject[OBJECT_COUNT];
double cratex = 20;
double cratez = 20;
GLuint texturesArena[TEXTURE_COUNT_ARENA];
const char *TextureFilesArena[TEXTURE_COUNT_ARENA] =
{"arena_floor.tga", "arena-muur.tga",
"crate.tga","stainless-steel.tga", "chainwheel.tga", "HUD.tga"};

vector<Robot*> robots;

void setOrthographicProjection() 
{

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the 
	//settings for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
	glOrtho(0,0,width,height,-1,1);
	// invert the y axis, down is positive
	//glScalef(1, -1, 1);
	// mover the origin from the bottom left corner
	// to the upper left corner
	//glTranslatef(0, -height, 0);
	glMatrixMode(GL_MODELVIEW);
}
void setRobots(Robot &r){
	robots.push_back(&r);
}

void resetPerspectiveProjection() 
{
	// set the current matrix to GL_PROJECTION
	glMatrixMode(GL_PROJECTION);
	// restore previous settings
	glPopMatrix();
	// get back to GL_MODELVIEW matrix
	glMatrixMode(GL_MODELVIEW);
}

void DisplayHUD(int x, int y, int z)
{
	glPushMatrix();
	//player1
	glDisable(GL_DEPTH_TEST);
	setOrthographicProjection();

	glBindTexture(GL_TEXTURE_2D, texturesArena[5]);

	glScalef(0.1,0.1,0.1);
	glTranslatef(0, -10, 0);

	glBegin(GL_QUADS);
	glTexCoord2f(0,0);	glVertex2f(-10,0);
	glTexCoord2f(1,0);	glVertex2f(10,0);
	glTexCoord2f(1,1);	glVertex2f(10,4);
	glTexCoord2f(0,1);	glVertex2f(-10,4);
	glEnd();

	resetPerspectiveProjection();
	char buff[100];
	string speed;
	string damage;
	//speler 1
	glTranslatef(410,0,-626);
	glRasterPos3f(0,0,0);
	sprintf(buff, "Speed: %i",robots[0]->speed);
	speed = buff;
	sprintf(buff, "Damage: %i",robots[0]->damage);
	damage = buff;
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) speed.c_str());
	glTranslatef(-6,0,-26);
	glRasterPos3f(0,0,0);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) damage.c_str());
	//speler 2
	glTranslatef(-279,0,25);
	glRasterPos3f(0,0,0);
	sprintf(buff, "Speed: %i",robots[1]->speed);
	speed = buff;
	sprintf(buff, "Damage: %i",robots[1]->damage);
	damage = buff;
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) speed.c_str());
	glTranslatef(1,0,-26);
	glRasterPos3f(0,0,0);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) damage.c_str());
	//speler 3
	glTranslatef(-289,0,26);
	glRasterPos3f(0,0,0);
	sprintf(buff, "Speed: %i",robots[2]->speed);
	speed = buff;
	sprintf(buff, "Damage: %i",robots[2]->damage);
	damage = buff;
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) speed.c_str());
	glTranslatef(11,0,-26);
	glRasterPos3f(0,0,0);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) damage.c_str());
	//speler 4
	glTranslatef(-297,0,27);
	glRasterPos3f(0,0,0);
	sprintf(buff, "Speed: %i",robots[3]->speed);
	speed = buff;
	sprintf(buff, "Damage: %i",robots[3]->damage);
	damage = buff;
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) speed.c_str());
	glTranslatef(19,0,-27);
	glRasterPos3f(0,0,0);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) damage.c_str());
	
	glColor4f(1,1,1,1);
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
	
}

/*
*	@parameters Object1 (coordinates) object2 (coordinates)
*	@returns true if a collision is detected between object 1 and object 2
*/
bool checkCollision(float x1, float y1, /*float z1,*/ float x2, float y2/*, float z2*/)
{
	if(y1 == y2 && x1 == x2)
    {
		return true;
    }
	return false;
}
int testx,testy,testz;
void ArenaDisplay(void)
{
	if(!isTextureLoaded)
	{
		isTextureLoaded = true;
		// het laden van de texture voor de achtergrond
		glGenTextures(TEXTURE_COUNT_ARENA, texturesArena);
		for(int i= 0; i < TEXTURE_COUNT_ARENA; i++)
		{
			glBindTexture(GL_TEXTURE_2D, texturesArena[i]);
			printf("loading %s\n",TextureFilesArena[i]);
			LoadTGATexture(TextureFilesArena[i], GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
		}
		robots[0]->Draw(25,0,25,45,false,false,false);
		robots[1]->Draw(-25,0,25,135,false,false,false);
		robots[2]->Draw(-25,0,-25,-45,false,false,false);
		robots[3]->Draw(25,0,-25,-135,false,false,false);
	}
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturesArena[0]);
	//createHUD(tx,tz);
	glBegin(GL_QUADS);
		//begin kubus
		//onderkant5
	glColor3f(1,1,1);
	
	glTexCoord2f(0,1);	glVertex3f(-50.0f,0.0f,-50.0f); 
	glTexCoord2f(0,0);	glVertex3f(-50.0f,0.0f,50.0f);
	glTexCoord2f(1,0);	glVertex3f(50.0f,0.0f,50.0f);
	glTexCoord2f(1,1);	glVertex3f(50.0f,0.0f,-50.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texturesArena[1]);
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
	glBindTexture(GL_TEXTURE_2D,texturesArena[3]);
	Ramp();
	//crate
	glBindTexture(GL_TEXTURE_2D,texturesArena[2]);
	Crate(20,5,20,tx,tz);

	//chainsaws
	glBindTexture(GL_TEXTURE_2D,texturesArena[4]);
	Chainsaw(-23.25,y,0);
	Chainsaw(-27.25,y,0);
	Chainsaw(23.25,y,0);
	Chainsaw(27.25,y,0);
	DisplayHUD(testx,testy,testz);

	//test cube for collision detection
	glPushMatrix();
	int r = rampCollision(tx,ty,tz);
	
		switch (r)
	{
	case 1:             // ESCAPE key
		glRotatef(-330,1,0,0);
		ty=8;
		break;
	case 2:
		glRotatef(330,1,0,0);
		ty=8;
		break;
	case 3:
		ty=8;
		break;
	case 0:
		ty=2;
		break;
		}
	glBindTexture(GL_TEXTURE_2D,texturesArena[2]);
	glTranslatef(tx,ty,tz);
	createCube(2,2,2,0.625,0.625,0.125);
	glPopMatrix();

	robots[0]->Draw(robots[0]->x,robots[0]->y,robots[0]->z,robots[0]->rotationY,robots[0]->anime1,robots[0]->anime2,robots[0]->anime3);
	robots[1]->Draw(robots[1]->x,robots[1]->y,robots[1]->z,robots[1]->rotationY,robots[1]->anime1,robots[1]->anime2,robots[1]->anime3);
	robots[2]->Draw(robots[2]->x,robots[2]->y,robots[2]->z,robots[2]->rotationY,robots[2]->anime1,robots[2]->anime2,robots[2]->anime3);
	robots[3]->Draw(robots[3]->x,robots[3]->y,robots[3]->z,robots[3]->rotationY,robots[3]->anime1,robots[3]->anime2,robots[3]->anime3);
}

void Reshape(GLint w, GLint h)
{
	width = w;
	height = h;
	glViewport(0,0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.01, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void IdleFuncArena(void)
{/*
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
		y-=.1;
	}
	else
	{
		y+=0.1;
		//printf("%02d", y);
	}
	timer += 1;
	timer = timer %60;*/
}
void playerInput( char c, int speler)
{
	// d drive, l left, r right, 1 hakwapen (wapen1), 2 pinwapen (wapen2), 3 rotatewapen(wapen3)
	switch(c)
	{
	case'd' : robots[speler]->Draw(robots[speler]->x+(cos((robots[speler]->rotationY)* (pi/180))*1),robots[speler]->y,robots[speler]->z+(sin((robots[speler]->rotationY)* (pi/180))*-1),robots[speler]->rotationY,robots[speler]->anime1,robots[speler]->anime2,robots[speler]->anime3);
		break;
	case'l' :robots[speler]->Draw(robots[speler]->x,robots[speler]->y,robots[speler]->z,robots[speler]->rotationY+15,robots[speler]->anime1,robots[speler]->anime2,robots[speler]->anime3);
		break;
	case'r' :robots[speler]->Draw(robots[speler]->x,robots[speler]->y,robots[speler]->z,robots[speler]->rotationY-15,robots[speler]->anime1,robots[speler]->anime2,robots[speler]->anime3);
		break;
	case'1' :robots[speler]->Draw(robots[speler]->x,robots[speler]->y,robots[speler]->z,robots[speler]->rotationY,true,robots[speler]->anime2,robots[speler]->anime3);
		break;
	case'2' :robots[speler]->Draw(robots[speler]->x,robots[speler]->y,robots[speler]->z,robots[speler]->rotationY,robots[speler]->anime1,true,robots[speler]->anime3);
		break;
	case'3' :robots[speler]->Draw(robots[speler]->x,robots[speler]->y,robots[speler]->z,robots[speler]->rotationY,robots[speler]->anime1,robots[speler]->anime2,true);
		break;
	}
}

void KeyboardArena(unsigned char key, int x, int y)
{
	printf("%c\n",key);
	switch (key)
	{
	case 27:             // ESCAPE key
		exit (0);
		break;
	case 'w':
		if(!checkCollision(0,50,0,tz+2))
			tz++;
		break;
	case 'a':
		if(!checkCollision(50,0,tx+2,0))
		tx++;
		break;
	case 's':
		if(!checkCollision(0,-50,0,tz-2))
		tz--;
		break;
	case 'd':
		if(!checkCollision(-50,0,tx-2,0))
		tx--;
		break;

	case 'u':
		testx--;
		break;
	case 'i':
		testx++;
		break;
	case'j':
		testy--;
		break;
	case'k':
		testy++;
		break;
	case'n':
		testz--;
		break;
	case'm':
		testz++;
		break;
	}
	printf("x:%i,y:%i,z:%i\n",testx,testy,testz);
}
