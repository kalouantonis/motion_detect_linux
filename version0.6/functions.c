/*
 * functions.c
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
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <errno.h> /* Needed for the errno variable*/
#include <string.h> /* Used for the strerror() function*/
#include "functions.h"

void error(char* msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

void release(CvMat* prev_img, CvMat* curr_img, CvCapture* webcam)
{
	cvReleaseMat(&prev_img);
	cvReleaseMat(&curr_img);
	cvReleaseCapture(&webcam);
}

void save_image(IplImage* frame, char* save_location)
{
	
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char location[255] = "";
	sprintf(location, "%s/%s.jpg", save_location, asctime(timeinfo));
	cvSaveImage(location, frame, 0);
}

void create_file(char* save_location)
{
	
	pid_t pid = fork();
	
	if(pid == -1)
		error("Can not fork process");
	if(!pid)
	{
		if(execl("/bin/mkdir", "/bin/mkdir", save_location, NULL) == -1)
			error("Can not run mkdir");
	}
}

int check_conf_file(FILE* f)
{
	if(f)
		return 1;
	else 
		return 0;
}

void create_conf_file(char* location, FILE* f)
{
	if(fprintf(f, "%s", location) == 1)
		error("Could not create conf file");
}

/*void check_clear(char* argv[], char* save_location)
{
	if(*argv[1] == "clear")
	pid_t pid = fork();
	
	if(pid == -1)
		error("Can't fork process");
	if(!pid)
	{
		if(execl("/bin/rm", "/bin/rm", "-r", save_location, NULL) == -1)
			error("Can not run rm");
	}
}*/
