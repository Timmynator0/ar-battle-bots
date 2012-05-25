#include "Chainsaw.h"


void Chainsaw(float y)
{
	glTranslatef(-23.25,y,0);
	glPushMatrix();
	glRotated(90,0,1,0);
	createCircle(5, 5,360,1,false,0,0,0);
	glPopMatrix();
	glTranslatef(-5,y,0);
	glPushMatrix();
	createCircle(5, 5,360,1,false,0,0,0);
	glPopMatrix();
}
