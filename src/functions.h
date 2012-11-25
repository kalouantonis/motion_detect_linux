#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>

void release(CvMat* prev_img, CvMat* curr_img, CvCapture* webcam);
void save_image(IplImage* frame, char* save_location);
void create_file(char* save_location);
void error(char* msg);
//void check_clear(char* argv[], char* save_location);
