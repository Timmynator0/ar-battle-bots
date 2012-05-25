#include "Chainsaw.h"


void Chainsaw(float y)
{
	//glRotated(90,0,1,0);
	glTranslatef(-20,y,0);
	glutSolidTorus(8,10,4,4);
}
