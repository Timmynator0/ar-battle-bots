#pragma once

#include "cv.h"
#include "highgui.h"
#include "Arena.h"
#include <Windows.h>

void showWindows();
void processImage();
DWORD WINAPI processMovement(void* params);
DWORD WINAPI pollMovement(void* params);
void dealloc();