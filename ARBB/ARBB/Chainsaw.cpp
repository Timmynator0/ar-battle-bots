#include "Chainsaw.h"


void Chainsaw(float x, float y, float z)
{
	glPushMatrix();
		glTranslatef(x,y,z);
		glPushMatrix();
			glRotated(90,0,1,0);
			createCircle(5, 5,360,1,true,0.625,0.625,0.125);
		glPopMatrix();
	glPopMatrix();
}
