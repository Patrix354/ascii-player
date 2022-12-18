#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#define NUMBER_OF_RGB_COORDNATES 3 

char* process_frame(int* frame, int frame_width, int frame_height, char* character_space);
void display_frame(char* frame);


#endif