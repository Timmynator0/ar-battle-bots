
#include "faceCam.h"
using namespace cv;

CvCapture* capture = cvCaptureFromCAM(1);
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
	if( img )loadTexture_Ipl(img, &faceTexture);

	glBindTexture(GL_TEXTURE_2D, faceTexture);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);		glVertex3f(-width,-height,0);		//1
	glTexCoord2f(1, 0);		glVertex3f(width,-height,0);		//2
	glTexCoord2f(0, 1);		glVertex3f(-width,height,height*2);		//3
	glTexCoord2f(1,1);		glVertex3f(width,height,height*2);		//4
	glEnd();

	//cvReleaseImage(&img);
	glDeleteTextures(GL_TEXTURE_2D,&faceTexture);
}

