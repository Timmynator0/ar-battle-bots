#include "Chainsaw.h"


void Chainsaw(float x, float y, float z)
{
	glPushMatrix();
		glTranslatef(x,y,z);
		glPushMatrix();
			glRotated(90,0,1,0);
			createCircle(5, 5,360,1,false,0,0,0);
		glPopMatrix();
	glPopMatrix();
}
