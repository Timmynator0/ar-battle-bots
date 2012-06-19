#include "Controls.h"

CvCapture* handCam = cvCaptureFromCAM(1);
CvSize sz = cvGetSize(cvQueryFrame(handCam));
IplImage* src = cvCreateImage(sz, 8, 3 );
IplImage* hsv_mask = cvCreateImage(sz, 8, 1);
IplImage* contour = cvCreateImage(sz, 8, 1);
CvScalar  hsv_min = cvScalar(0, 0, 0, 0);
CvScalar  hsv_max = cvScalar(55, 55, 55, 0);
CvMemStorage* storage;
CvConvexityDefect* convexDefect;
LPDWORD thread1ID;
LPDWORD thread2ID;
char command;
bool dead = false;

int initControls()
{
	int c = 0;
	cvQueryFrame(handCam);
	CreateThread(NULL, 0, processMovement, NULL, 0, thread1ID);
	CreateThread(NULL, 0, pollMovement, NULL, 0, thread2ID);
	if(dead) {
	TerminateThread(processMovement, 0);
	TerminateThread(pollMovement, 0);
	dealloc();
	}
	return 0;
}

void showWindows()
{
//	cvShowImage("src", src);
	cvInRangeS(src, hsv_min, hsv_max, hsv_mask);
	cvNot(hsv_mask, hsv_mask);
	cvShowImage("hsv-msk", hsv_mask);
	cvShowImage("Hand Contour", contour);
}

void processImage()
{
	cvInRangeS(src, hsv_min, hsv_max, hsv_mask);	//Threshold Image
	cvNot(hsv_mask, hsv_mask);						//Inverse Image
	//setHand(hsv_mask);
	hsv_mask->origin = 1;
	cvShowImage("hsv-msk", hsv_mask);
	//cvShowImage("Hand Contour", contour);
	//std::cout<<"hsv: "<<hsv_mask->nChannels<<std::endl;
	cvZero(contour);
}

DWORD WINAPI processMovement(void* params)
{
	int c = 0;
	CvSeq* defects = 0;
	CvSeq* contours = 0;
	CvSeq* hull = 0;
	CvPoint p1, p2;
	while(c != 27)
	{
		storage = cvCreateMemStorage();
		src = cvQueryFrame(handCam);
		cvFlip(src, src, 1);
		cvFindContours(hsv_mask, storage, &contours, sizeof(CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
		if(contours != NULL)
		{
			p1.x = 640;
			p1.y = 480;
			p2.x = 0;
			p2.y = 0;
			hull = cvConvexHull2(contours, 0, CV_CLOCKWISE, 0);
			defects = cvConvexityDefects(contours, hull, storage);
			int nomdef = defects->total;
			convexDefect = (CvConvexityDefect*)malloc(sizeof(CvConvexityDefect) * nomdef);
			cvCvtSeqToArray(defects, convexDefect, CV_WHOLE_SEQ);
			for(int i = 0; i < nomdef; i++)
			{
				cvLine(contour, *(convexDefect[i].start), *(convexDefect[i].depth_point), CV_RGB(255,255,255), 2, 8, 0);
				cvCircle(contour,*(convexDefect[i].depth_point), 5, CV_RGB(255, 255, 255), 3, 8, 0);
				cvCircle(contour,*(convexDefect[i].start), 5, CV_RGB(255, 255, 255), 3, 8, 0);
				cvLine(contour,*(convexDefect[i].depth_point), *(convexDefect[i].end), CV_RGB(255,255,255), 2, 8, 0);
				if(convexDefect[i].start->x < p1.x)
					p1.x = convexDefect[i].start->x;
				if(convexDefect[i].start->y < p1.y)
					p1.y = convexDefect[i].start->y;
				if(convexDefect[i].end->x > p2.x)
					p2.x = convexDefect[i].end->x;
				if(convexDefect[i].end->y > p2.y)
					p2.y = convexDefect[i].end->y;
			}
			cvRectangle(contour, p1, p2, CV_RGB(255, 255, 255), 3, 8, 0);
			contours = contours->h_next;
			if(p1.y <= 80 && p1.x >= 170 && p2.x <= 480)
				command = 'd';		//rechtdoor d
			else if(p1.x <= 100 && p1.y >= 100 && p2.x <= 450)
				command = 'l';		//links l
			else if(p1.x >= 200 && p1.y >= 100 && p2.x >= 500)
				command = 'r';		//rechts r
			else if(p1.x <= 100 && p1.y <= 80 && p2.x <= 450)
				command = '1';		//wapen 1
			else
				command = 's';		//stop s
			//cvReleaseMemStorage(&storage);
			c = cvWaitKey(10);
		}
		cvReleaseMemStorage(&storage);
		//showWindows();
		processImage();
	}
	dealloc();
	dead = true;
	return 0;
}

DWORD WINAPI pollMovement(void* params)
{
	while(!dead)
	{
		if(command != 0)
		{
			playerInput(command, 0);
			Sleep(10);
		}
	}
	return 0;
}

void dealloc()
{
	cvReleaseCapture(&handCam);
	cvReleaseMemStorage(&storage);
	free(convexDefect);
	cvDestroyAllWindows();
}