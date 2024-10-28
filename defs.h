#ifndef DEFS_H
#define DEFS_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_hints.h>
#include<SDL2/SDL_error.h>
#include<SDL2/SDL_log.h>
#include<SDL2/SDL_video.h>
#include<SDL2/SDL_render.h>
#include<SDL2/SDL_pixels.h>
#include<SDL2/SDL_rect.h>
#include<SDL2/SDL_surface.h>
#include<SDL2/SDL_clipboard.h>
#include<SDL2/SDL_events.h>

//TTF
#include<SDL2/SDL_ttf.h>

#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<unistd.h>

#define LOG(...) fprintf(stdout, __VA_ARGS__)

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#include<SDL2/SDL_image.h>



#undef main


#define MAX_CHAR_IN_LINE 100
#define MAX_LINES 100 
//global cursor
static int cursor_x = 0, cursor_y = 0;


//int allocated_lines = 0;
typedef struct{
	
	char*  c;
	int char_in_line;
	//int y;
	
}Text;


Text* Alloc_Text(void){
	Text* t = malloc(sizeof(Text) * MAX_LINES);
	for(int i = 0; i < MAX_LINES; i++){
		t[i].c = malloc(MAX_CHAR_IN_LINE * sizeof(char));
		memset(t[i].c, '\0', MAX_CHAR_IN_LINE * sizeof(char));
		t[i].char_in_line = 0;
		//t[i].y = 0;
	}	
	return t;
}
void Input(Text* text, int line, int pos, char c, uint8_t is_char){
	assert((line < MAX_LINES) && "Over line num");
	assert((pos < MAX_CHAR_IN_LINE) && "Over char num in line");
	text[line].c[pos] = c;
	if(!is_char)
		text[line].char_in_line = pos;  
	//printf("Text: %s, %d", text[line].c, text[line].char_in_line);
}




#endif