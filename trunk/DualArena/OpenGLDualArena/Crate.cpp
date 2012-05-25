#include "Crate.h"


void Crate(float x, float y, float z)
{
	glBegin(GL_QUADS);
		//begin cube
		//zijkant links
		glTexCoord2f(1,1);	glVertex3f(x-2.5f,0.0f,z-2.5f);
		glTexCoord2f(1,0);	glVertex3f(x-2.5f,y,z-2.5f);
		glTexCoord2f(0,0);	glVertex3f(x-2.5f,y,z+2.5f);
		glTexCoord2f(0,1);	glVertex3f(x-2.5f,0.0f,z+2.5f);

		//zijkant rechts
		glTexCoord2f(1,1);	glVertex3f(x+2.5f,0.0f,z-2.5f);
		glTexCoord2f(1,0);	glVertex3f(x+2.5f,y,z-2.5f);
		glTexCoord2f(0,0);	glVertex3f(x+2.5f,y,z+2.5f);
		glTexCoord2f(0,1);	glVertex3f(x+2.5f,0.0f,z+2.5f);

		//zijkant zuid
		glTexCoord2f(1,1);	glVertex3f(x+2.5f,0.0f,z-2.5f);
		glTexCoord2f(1,0);	glVertex3f(x+2.5f,y,z-2.5f);
		glTexCoord2f(0,0);	glVertex3f(x-2.5f,y,z-2.5f);
		glTexCoord2f(0,1);	glVertex3f(x-2.5f,0.0f,z-2.5f);

		//zijkant noord
		glTexCoord2f(1,1);	glVertex3f(x+2.5f,0.0f,z+2.5f);
		glTexCoord2f(1,0);	glVertex3f(x+2.5f,y,z+2.5f);
		glTexCoord2f(0,0);	glVertex3f(x-2.5f,y,z+2.5f);
		glTexCoord2f(0,1);	glVertex3f(x-2.5f,0.0f,z+2.5f);

		//bovenkant ramp
		glTexCoord2f(1,1);	glVertex3f(x+2.5f,y,z+2.5f);
		glTexCoord2f(1,0);	glVertex3f(x+2.5f,y,z+2.5f);
		glTexCoord2f(0,0);	glVertex3f(x-2.5f,y,z+2.5f);
		glTexCoord2f(0,1);	glVertex3f(x-2.5f,y,z-2.5f);

		glEnd();
}
