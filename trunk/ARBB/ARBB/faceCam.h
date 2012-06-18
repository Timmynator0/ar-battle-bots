#ifndef FACECAM
#define FACECAM

#include "opencv2/imgproc/imgproc.hpp"

#include "cv.h"
#include "highgui.h"
#include <stdlib.h>

#include <GLTools.h>
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>

#ifdef _EiC
#define WIN32
#endif

using namespace cv;

int loadTexture_Ipl(IplImage *image, GLuint *text);
void drawFace(float width, float height);

#endif