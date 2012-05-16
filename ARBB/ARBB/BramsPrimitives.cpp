#include <iostream>
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>
#include <stdio.h>
#include "BramsPrimitives.h"

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>            // Windows FreeGlut equivalent
#endif

void createDiamondCube(float x, float y, float z)
{
	glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(0,y*2,-z);
			glVertex3f(-x,y,-z);
			glVertex3f(0,y*2,z);
			glVertex3f(-x,y,z);
			glVertex3f(x,y,z);
			glVertex3f(0,0,z);
			glVertex3f(x,y,-z);
			glVertex3f(0,0,-z);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(x,y,z);
			glVertex3f(0,y*2,z);
			glVertex3f(x,y,-z);
			glVertex3f(0,y*2,-z);
			glVertex3f(0,0,-z);
			glVertex3f(-x,y,-z);
			glVertex3f(0,0,z);
			glVertex3f(-x,y,z);
		glEnd();
}

void createPentagon(float x, float y, float z)
{
	glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0,y*3,z/5);

			glVertex3f(x,y*1.5,z);
			glVertex3f(x,0,z);
			glVertex3f(-x,0,z);
			glVertex3f(-x,y*1.5,z);
			glVertex3f(-x,y*1.5,-z);
			glVertex3f(0,y*3,-z);
			glVertex3f(x,y*1.5,-z);
			glVertex3f(x,y*1.5,z);
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
			glVertex3f(-x,0,-z);
			
			glVertex3f(-x,0,z);
			glVertex3f(-x,y*1.5,z);
			glVertex3f(-x,y*1.5,-z);
			glVertex3f(0,y*3,-z);
			glVertex3f(x,y*1.5,-z);
			glVertex3f(x,0,-z);
			glVertex3f(x,0,z);
			glVertex3f(-x,0,z);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);		
			glVertex3f(x,y*1.5,z);
			glVertex3f(x,0,z);
			glVertex3f(x,y*1.5,-z);
			glVertex3f(x,0,-z);
		glEnd();
}
void createTriangle(float x, float y, float z)
{
	glBegin(GL_TRIANGLES);
			glVertex3f(-x,0,z); glVertex3f(x,0,z); glVertex3f(0,y*2,z);
			glVertex3f(-x,0,-z); glVertex3f(x,0,-z); glVertex3f(0,y*2,-z);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
		glColor4f(1,0,0,1);
			glVertex3f(-x,0,z); 
			glVertex3f(-x,0,-z); 
			glVertex3f(x,0,z); 
			glVertex3f(x,0,-z);
			glVertex3f(0,y*2,z); 
			glVertex3f(0,y*2,-z);
			glVertex3f(-x,0,z); 
			glVertex3f(-x,0,-z); 
		glEnd();
}
/* This method creates a cube at X,Y,Z, with width,height,depth and with center at x, y+height,z+depth,
 * param u,v are meant for starting position @ the texture, uvsize is the size of x in the texture
*/
void createCube(float width, float height, float depth,float u, float v, float uvsize){	
	height=height/2;depth=depth/2;
	/*
	if(nr == 1){ uvsize = 0.1625; u = 0; v = 0;}
	if(nr == 2){ uvsize = 0.08125; u = 0; v = 0.675;}
	if(nr == 3){ uvsize = 0.052; u = 0.22; v = 0.54;}*/
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(uvsize*4+u, v+ uvsize);		glVertex3f(0,-height,-depth);		//1
	glTexCoord2f(uvsize*4+u, v+uvsize*3);		glVertex3f(width,-height,-depth);		//2
	glTexCoord2f(uvsize*3+u, v+uvsize);			glVertex3f(0,-height,depth);			//3
	glTexCoord2f(uvsize*3+u, v+uvsize*3);		glVertex3f(width,-height,depth);			//4

	glTexCoord2f(uvsize*2+u, v+uvsize);			glVertex3f(0,height,depth);			//5
	glTexCoord2f(uvsize*2+u, v+uvsize*3);		glVertex3f(width,height,depth);			//6
	glTexCoord2f(uvsize+u, v+uvsize);			glVertex3f(0,height,-depth);			//7
	glTexCoord2f(uvsize+u, v+uvsize*3);			glVertex3f(width,height,-depth);			//8
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0+u, v+0);			glVertex3f(0,-height,depth);			//3
	glTexCoord2f(uvsize+u, v+0);			glVertex3f(0,height,depth);			//5
	glTexCoord2f(0+u, v+uvsize);			glVertex3f(0,-height,-depth);		//1
	glTexCoord2f(uvsize+u, v+uvsize);			glVertex3f(0,height,-depth);			//7

	glTexCoord2f(0+u, v+uvsize*3);			glVertex3f(width,-height,-depth);		//2
	glTexCoord2f(uvsize+u, v+uvsize*3);			glVertex3f(width,height,-depth);			//8
	glTexCoord2f(0+u, v+uvsize*4);			glVertex3f(width,-height,depth);			//4
	glTexCoord2f(uvsize+u, v+uvsize*4);			glVertex3f(width,height,depth);			//6
	glEnd();
}
void createCircle(float radius, int segments,int part,bool texture, GLfloat u, GLfloat v, GLfloat uvsize)
{
    glBegin( GL_TRIANGLE_FAN );
	if(texture) glTexCoord2f(u,v);
    glVertex3f(0,0,0);
        for( int n = 0; n <= segments; n++ ) {
            float const t = (PI*2*(float)n/(float)segments)/part;
			if(texture) {
				if(part == 2){
					if(n > segments/2)
					glTexCoord2f((sin(t)*uvsize)+u,(cos(t)*uvsize)+v);
					else {
						glTexCoord2f(-(sin(t)*uvsize)+u,(cos(t)*uvsize)+v);
					}
				}
				if(part == 1)glTexCoord2f((sin(t)*uvsize)+u,(cos(t)*uvsize)+v);  
			}
			glVertex3f(sin(t)*radius/2,cos(t)*radius,0);
        }
    glEnd();
}

void createCylinder(float radius, int segments, float depth,int part, bool texture, float u, float v,float uvsize){
	createCircle(radius,segments,part,texture,u,v,uvsize);
	glBegin(GL_TRIANGLE_STRIP);
	float hoek = 360/segments;
	for(int i = 0; i< segments+1; i++){
        float const t = (PI*2*(float)i/(float)segments)/part;
		float vX = i%2; if(v==1) vX= 0.25;
		if(part==2) v/2;
		if(texture) glTexCoord2f(u,vX+v);			
		glVertex3f(sin(t)*radius/2,cos(t)*radius,0);
		if(texture) glTexCoord2f(u+uvsize,vX+v);				
		glVertex3f(sin(t)*radius/2,cos(t)*radius,depth);
	}
	glEnd();
	glPushMatrix();
	glTranslated(0,0,depth);
	createCircle(radius,segments,part,texture,u,v,uvsize);
	glPopMatrix();
}