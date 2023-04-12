#include <python3.11/Python.h>
#include "interface.h"


static void* alocate_table(int dimention, int typesize)
{
	void* frame = malloc(dimention * typesize);
	return frame;
}

static char map(int x, int in_min, int in_max, int out_min, int out_max) 
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static char* map_frame(int* frame, int frame_width, int frame_height, int length_of_character_space)
{
    int index_offset = 0;
	static char* mapped_frame = NULL;
	if (mapped_frame == NULL)	mapped_frame = alocate_table(frame_width * frame_height, sizeof(int));

	for (int i = 0; i < frame_height; i++)
	{
		for (int j = 0; j < frame_width; j++)
		{
            index_offset = frame_width * i + j;
			mapped_frame[index_offset] = map(frame[index_offset], 0, 255, 0, length_of_character_space-1);
		}
	}

	return mapped_frame;
}

char* add_new_line_characters(char* frame, int frame_width, int frame_height, char* character_space)
{
    char current_pixel = 0;
    int index_offset_on_base_frame = 0;
	int index_offset_on_ASCII_frame = 0;;
	static char* frame_with_ASCIIart = NULL;
	if (frame_with_ASCIIart == NULL)	frame_with_ASCIIart = alocate_table((frame_width+1) * frame_height, sizeof(char));

    for (int i = 0; i < frame_height; i++)
	{
		for (int j = 0; j <= frame_width; j++)
		{
			index_offset_on_base_frame = frame_width * i + j;
			index_offset_on_ASCII_frame = (frame_width+1) * i + j;
			
            if(j == frame_width)	current_pixel = '\n';
            else	current_pixel = character_space[frame[index_offset_on_base_frame]];

			frame_with_ASCIIart[index_offset_on_ASCII_frame] = current_pixel;
        }
	}
    return frame_with_ASCIIart;
}

char* process_frame(int* frame, int frame_width, int frame_height, char* character_space)
{
	static char* frame_with_mapped_values = NULL;
    static char* frame_with_ASCIIart = NULL;
    int length_of_character_space = strlen(character_space);

	frame_with_mapped_values = map_frame(frame, frame_width, frame_height, length_of_character_space);
    frame_with_ASCIIart = add_new_line_characters(frame_with_mapped_values, frame_width, frame_height, character_space);

	return frame_with_ASCIIart;
}

void display_frame(char* frame)
{
	system("clear");
	printf("\r%s", frame);
	return;
}
