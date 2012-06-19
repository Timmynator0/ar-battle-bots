#include "awaitingPlayerScreen.h"

vector< ObjModel*> apsmodellen;
GLuint apstextures[apsTEXTURE_COUNT];
const char *apsTextureFiles[apsTEXTURE_COUNT] =
{ "arena-muur.tga","APSfloor.tga","chainwheel.tga" };
bool Laps = false;
int iSecret = 0, robotZ;
Robot robot;

float driveDistance = 0;

void initAPS(vector< ObjModel*> Apsmodellen)
{
	apsmodellen = Apsmodellen;
	srand ( time(NULL) );
}

void drivingRobot(Robot robot, int direction)
{
	
	glPushMatrix();
	glScaled(2,2,2);
	if(driveDistance != 0)	robot.Draw((driveDistance-75)*direction,1,robotZ*2+5,90+(90*direction),false,false,true,false);
	glPopMatrix();
}
void whirlingSaw()
{
	float Y = driveDistance;
	if(driveDistance > 25) Y=(-Y)+50;
	
	glBindTexture(GL_TEXTURE_2D, apstextures[2]);
	
	glPushMatrix();
		glTranslatef(-75,Y-20,43);
		glPushMatrix();
			glRotated(160,0,1,0);
			createCircle(13,13,36,1,true,0.5,0.5,0.5);
		glPopMatrix();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-91,Y-20,49);
		glPushMatrix();
			glRotated(160,0,1,0);
			createCircle(13,13,36,1,true,0.5,0.5,0.5);
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(75,Y-20,43);
		glPushMatrix();
			glRotated(20,0,1,0);
			createCircle(13,13,36,1,true,0.5,0.5,0.5);
		glPopMatrix();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(91,Y-20,49);
		glPushMatrix();
			glRotated(20,0,1,0);
			createCircle(13,13,36,1,true,0.5,0.5,0.5);
		glPopMatrix();
	glPopMatrix();
}

void randomEvents()
{
	iSecret = rand() % 100;
	if (iSecret<4)
	{
		int items[] = { ((int)rand()%4+1),((int)rand()%4+1),((int)rand()%4+1),((int)rand()%4+1),((int)rand()%4+1),((int)rand()%4+1)};
		switch(iSecret){
		case 3:
			driveDistance = 150;
			robotZ = rand() % 10;
			robot = Robot(0,0,0,0,items,0, apsmodellen);
			drivingRobot(robot,-1);
			break;
		case 2:
			driveDistance = 150;
			robot = Robot(0,0,0,0,items,0, apsmodellen);
			drivingRobot(robot,1);
			break;
		case 1:
			driveDistance = 50;
			whirlingSaw();
			break;
		}
	}
}
void updateStatus()
{
	switch(iSecret)
	{
	case 3:
		drivingRobot(robot,-1);
		break;
	case 2:
		drivingRobot(robot,1);
		break;
	case 1:
		whirlingSaw();
		break;

	}
}

void createAPSBackground(float width, float height){
	width /= 8;
	height /= 10;
	float depth = 70;
	if(!Laps)
	{
		// het laden van de texture voor de achtergrond
		glGenTextures(apsTEXTURE_COUNT, apstextures);
		for(int i= 0; i < apsTEXTURE_COUNT; i++)
		{
			glBindTexture(GL_TEXTURE_2D, apstextures[i]);
			LoadTGATexture(apsTextureFiles[i], GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
		}
		Laps = true;
	}
	glBindTexture(GL_TEXTURE_2D, apstextures[0]);	
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);		glVertex3f(-width,0,depth);		//1
			glTexCoord2f(0,1);		glVertex3f(-width,height,depth);		//2
			glTexCoord2f(1,1);		glVertex3f(width,height,depth);			//3
			glTexCoord2f(1,0);		glVertex3f(width,0,depth);			//4
		glEnd();	
	glBindTexture(GL_TEXTURE_2D, apstextures[1]);	
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);		glVertex3f(-width,0,-20);		//1
			glTexCoord2f(0,1);		glVertex3f(-width,0,depth);		//2
			glTexCoord2f(1,1);		glVertex3f(width,0,depth);			//3
			glTexCoord2f(1,0);		glVertex3f(width,0,-20);			//4
		glEnd();	
	//glDeleteTextures(GL_TEXTURE_2D,apstextures);
		glPushMatrix();
		glColor4f(1.0f, 1.0f, 0.0f,1.0f);
		glRasterPos3f(10,60,60);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18,(unsigned char*) "Wachten op Spelers... ");
		glPopMatrix();
		glColor4f(1.0f, 1.0f, 1.0f,1.0f);
		if(driveDistance == 0 ) randomEvents();
		else{
			driveDistance-=1;
			updateStatus();
		}
		Sleep(10);
}