#include "faceCam.h"
using namespace cv;

CvCapture* capture = cvCaptureFromCAM(0);
GLuint faceTexture = 0;

int loadTexture_Ipl(IplImage *image, GLuint *text)
{ 
	if (image==NULL) return -1;
 
	glGenTextures(1, text);
 
	glBindTexture( GL_TEXTURE_2D, *text ); //bind the texture to it's array
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height,0, GL_BGR, GL_UNSIGNED_BYTE, image->imageData);
	return 0; 
}
void drawFace(float width, float height)
{
	IplImage *img;
	img=cvQueryFrame(capture);
	cvFlip( img, img, -1 );
	if( img )loadTexture_Ipl(img, &faceTexture);

	glBindTexture(GL_TEXTURE_2D, faceTexture);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.35, 0);		glVertex3f(-width/2,-height,0);		//1
	glTexCoord2f(0.65, 0);		glVertex3f(width/2,-height,0);		//2
	glTexCoord2f(0.2, 0.3);		glVertex3f(-width,-height/2,height*0.5);		//3
	glTexCoord2f(0.8, 0.3);		glVertex3f(width,-height/2,height*0.5);		//4
	glTexCoord2f(0.2, 0.6);		glVertex3f(-width,height/2,height*1);		//5
	glTexCoord2f(0.8,0.6);		glVertex3f(width,height/2,height*1);		//6
	glTexCoord2f(0.35, 0.9);		glVertex3f(-width/2,height,height*1.5);		//7
	glTexCoord2f(0.65,0.9);		glVertex3f(width/2,height,height*1.5);		//8
	glEnd();

	//cvReleaseImage(&img);
	glDeleteTextures(GL_TEXTURE_2D,&faceTexture);
}

