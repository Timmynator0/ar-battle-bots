#include "Crate.h"


void Crate(float x, float y, float z)
{
	glBegin(GL_QUADS);
		//begin cube
		//zijkant links
		glVertex3f(x-2.5f,0.0f,z-2.5f);
		glVertex3f(x-2.5f,y,z-2.5f);
		glVertex3f(x-2.5f,y,z+2.5f);
		glVertex3f(x-2.5f,0.0f,z+2.5f);

		//zijkant rechts
		glVertex3f(x+2.5f,0.0f,z-2.5f);
		glVertex3f(x+2.5f,y,z-2.5f);
		glVertex3f(x+2.5f,y,z+2.5f);
		glVertex3f(x+2.5f,0.0f,z+2.5f);

		//zijkant zuid
		glVertex3f(x+2.5f,0.0f,z-2.5f);
		glVertex3f(x+2.5f,y,z-2.5f);
		glVertex3f(x-2.5f,y,z-2.5f);
		glVertex3f(x-2.5f,0.0f,z-2.5f);

		//zijkant noord
		glVertex3f(x+2.5f,0.0f,z+2.5f);
		glVertex3f(x+2.5f,y,z+2.5f);
		glVertex3f(x-2.5f,y,z+2.5f);
		glVertex3f(x-2.5f,0.0f,z+2.5f);

		//bovenkant ramp
		glVertex3f(x+2.5f,y,z+2.5f);
		glVertex3f(x+2.5f,y,z+2.5f);
		glVertex3f(x-2.5f,y,z+2.5f);
		glVertex3f(x-2.5f,y,z-2.5f);

		glEnd();
}
