#pragma once

#include "cv.h"
#include "highgui.h"
#include <stdlib.h>
#include <GLTools.h>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>

#ifdef _EiC
#define WIN32
#endif

using namespace cv;

int loadTexture_Ipl(IplImage *image, GLuint *text);
void drawFace(float width, float height);