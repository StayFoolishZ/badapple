#include <opencv2/core/core.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  

#include "SSD1306.h"

using namespace cv;  
using namespace std;
  
int main (int argc, char **argv)  
{  
	int i,j;
	char d;
	unsigned sd;
	unsigned char *buff;
	if(wiringPiSetup()<0)
	{
		cout<<"Err"<<endl;
		return 0;
	}
	init(SSD1306_SWITCHCAPVCC);
    CvCapture *capture=cvCreateFileCapture("badapple.avi");
	IplImage *frame=NULL;
	do{
		frame=cvQueryFrame(capture);
		if(!frame)
		{
			break;
		}
		waitKey(30);
		clear_screen();
		for(i=0;i<64;i++)
		{
			for(j=0;j<128;j++)
			{
				sd=0;
				sd+=(unsigned)(((unsigned char*)frame->imageData)+i*frame->widthStep)[j*frame->nChannels+0];
				sd+=(unsigned)(((unsigned char*)frame->imageData)+i*frame->widthStep)[j*frame->nChannels+1];
				sd+=(unsigned)(((unsigned char*)frame->imageData)+i*frame->widthStep)[j*frame->nChannels+2];		
				if(sd>100)
				{
					draw_pixal(j,i,WHITE);
				}
			}
		}
		display();
	}
	while(frame);
	cvReleaseCapture(&capture);
    return 0;  
}  
