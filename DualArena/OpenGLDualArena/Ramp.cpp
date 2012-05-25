#include "Ramp.h"

	void Ramp(void)
	{
		glBegin(GL_QUADS);
		//begin trapeze
		//zijkant 1
		glTexCoord2f(1,1);		glVertex3f(-7.5f,0.0f,-12.5f);
		glTexCoord2f(1,0);		glVertex3f(-7.5f,5.0f,-4.0f);
		glTexCoord2f(0,0);		glVertex3f(-7.5f,5.0f,4.0f);
		glTexCoord2f(0,1);		glVertex3f(-7.5f,0.0f,12.5f);

		//zijkant 2
		glTexCoord2f(1,1);		glVertex3f(7.5f,0.0f,-12.5f);
		glTexCoord2f(1,0);		glVertex3f(7.5f,5.0f,-4.0f);
		glTexCoord2f(0,0);		glVertex3f(7.5f,5.0f,4.0f);
		glTexCoord2f(0,1);		glVertex3f(7.5f,0.0f,12.5f);

		//zuid ramp
		glTexCoord2f(1,1);		glVertex3f(7.5f,0.0f,-12.5f);
		glTexCoord2f(1,0);		glVertex3f(7.5f,5.0f,-4.0f);
		glTexCoord2f(0,0);		glVertex3f(-7.5f,5.0f,-4.0f);
		glTexCoord2f(0,1);		glVertex3f(-7.5f,0.0f,-12.5f);

		//noord ramp
		glTexCoord2f(1,0.2);		glVertex3f(7.5f,0.0f,12.5f);
		glTexCoord2f(1,0);		glVertex3f(7.5f,5.0f,4.0f);
		glTexCoord2f(0,0);		glVertex3f(-7.5f,5.0f,4.0f);
		glTexCoord2f(0,1);		glVertex3f(-7.5f,0.0f,12.5f);

		//bovenkant ramp
		glTexCoord2f(1,1);		glVertex3f(7.5f,5.0f,-4.0f);
		glTexCoord2f(1,0);		glVertex3f(7.5f,5.0f,4.0f);
		glTexCoord2f(0,0);		glVertex3f(-7.5f,5.0f,4.0f);
		glTexCoord2f(0,1);		glVertex3f(-7.5f,5.0f,-4.0f);

		glEnd();
	}
