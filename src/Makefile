main.o: main.c
	gcc -Wall -c main.c -o main.o -I. -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video
functions.o: functions.c 
	gcc -Wall -c functions.c -o functions.o -I. -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video
main: main.o functions.o
	gcc -Wall functions.o main.o -o main -I. -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video
