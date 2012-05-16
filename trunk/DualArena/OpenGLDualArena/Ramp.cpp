#include "Ramp.h"

	void Ramp(void)
	{
		glBegin(GL_QUADS);
		//begin trapeze
		//zijkant 1
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(-7.5f,0.0f,-12.5f);
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(-7.5f,5.0f,-4.0f);
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(-7.5f,5.0f,4.0f);
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(-7.5f,0.0f,12.5f);

		//zijkant 2
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(7.5f,0.0f,-12.5f);
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(7.5f,5.0f,-4.0f);
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(7.5f,5.0f,4.0f);
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(7.5f,0.0f,12.5f);

		//zuid ramp
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(7.5f,0.0f,-12.5f);
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(7.5f,5.0f,-4.0f);
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(-7.5f,5.0f,-4.0f);
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(-7.5f,0.0f,-12.5f);

		//noord ramp
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(7.5f,0.0f,12.5f);
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(7.5f,5.0f,4.0f);
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(-7.5f,5.0f,4.0f);
		glColor3f(1.0f,1.0f,0.0f);		glVertex3f(-7.5f,0.0f,12.5f);

		//bovenkant ramp
		glColor3f(1.0f,0.0f,1.0f);		glVertex3f(7.5f,5.0f,-4.0f);
		glColor3f(1.0f,0.0f,1.0f);		glVertex3f(7.5f,5.0f,4.0f);
		glColor3f(1.0f,0.0f,1.0f);		glVertex3f(-7.5f,5.0f,4.0f);
		glColor3f(1.0f,0.0f,1.0f);		glVertex3f(-7.5f,5.0f,-4.0f);

		glEnd();
	}
