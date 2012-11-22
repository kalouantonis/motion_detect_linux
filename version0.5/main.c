/*
 * main.c
 * 
 * Copyright 2012 Antonis Kalou <slacker@ubuntu-R580-R590>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <unistd.h>
#include "functions.h"
#define INDEX -1

int main(int argc, char **argv)
{
	char save_location[255];
	puts("Where would you like to store images?");
	scanf("%s", save_location);
	create_file(save_location);
	
	puts("\nWaiting 30 seconds for you to leave the room...\n");
	//sleep(30); /* 30 second delay so i can leave the room. */
	
	CvCapture *webcam = cvCaptureFromCAM(INDEX);
	
	short first_run = 0;
	short capture_first = 0;
	
	//check_clear(argv[1], save_location);	
	
	if(!webcam)
		error("Could not capture from webcam");
	
	CvMat *curr_img= 0 , *prev_img = 0;
	cvNamedWindow("Detect", 1);
	
	while(1)
	{
		IplImage *frame = cvQueryFrame(webcam);
		
		if(!frame)
			error("Could not capture from frame");
		
		if(!curr_img)
		{
			curr_img = cvCreateMat(frame->height, frame->width, CV_8UC1);
			prev_img = cvCreateMat(curr_img->rows, curr_img->cols, curr_img->type);
			first_run = 1;
		}
		cvCvtColor(frame, curr_img, CV_BGR2GRAY);
		if(first_run == 1)
		{
			double norm_L2 = cvNorm(prev_img, curr_img, CV_L2, NULL);
			if(norm_L2 > 30000 || capture_first == 0)
				norm_L2 = 0; capture_first = 1; /*There is a bug at launch that causes double
							  * to equal > 70000. This fixes the false alarm.*/
			if(norm_L2 > 3000)
			{
				printf("Intruder detected, saving image!\tnorm_L2 = %f\n", norm_L2);
				cvShowImage("Detect", curr_img);
				save_image(frame, save_location);
				/*if(i > 5)
				{
					//save_video();
					printf("Video is being saved instead! i = %i\n", i);
				} 
				else
					save_image(frame); */
				sleep(0.5); //delay 500 ms not to fill directory

			}
		}
		
		if(cvWaitKey(1) >= 0) //set cvWaitKey(1) for instant processing
			break;
		
		CvMat *temp;
		CV_SWAP(prev_img, curr_img, temp);
	}
	release(prev_img, curr_img, webcam);
	return 0;
}

