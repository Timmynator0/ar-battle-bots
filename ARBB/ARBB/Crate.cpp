#include "Crate.h"

float x,z;

void Crate(float cx, float y, float cz,double playerx, double playerz)
{
	CollisionMove(cx,cz,playerx,playerz);

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

		//bovenkant crate
		glTexCoord2f(1,1);	glVertex3f(x+2.5f,y,z-2.5f);
		glTexCoord2f(1,0);	glVertex3f(x+2.5f,y,z+2.5f);
		glTexCoord2f(0,0);	glVertex3f(x-2.5f,y,z+2.5f);
		glTexCoord2f(0,1);	glVertex3f(x-2.5f,y,z-2.5f);

		glEnd();
}

void CollisionMove(float cx, float cz,double px, double pz)
{
	if(cx+2.5 == px && (cz-2.5>=pz || cz+2.5>=pz))
	{
		x++;
	}
	else if(cx-2.5 == px && (cz-2.5>=pz || cz+2.5>=pz))
	{
		x--;
	}
	if(x>=47.5)
	{
		x=47.5;
	}
	else if(x<=-47.5)
	{
		x=-47.5;
	}
	else
	{
		if(cx+2.5 == px && (cz-2.5>=pz || cz+2.5>=pz))
		{
			x++;
		}
		else if(cx-2.5 == px && (cz-2.5>=pz || cz+2.5>=pz))
		{
			x--;
		}
	}
	if(cz>=47.5)
	{
		z=47.5;
	}
	else if(z<=-47.5)
	{
		cz=-47.5;
	}
	else
	{
		if(cz+2.5 == px && (cx-2.5>=pz || cx+2.5>=pz))
		{
			z++;
		}
		else if(cz-2.5 == px && (cx-2.5>=pz || cx+2.5>=pz))
		{
			z--;
		}
	}
}