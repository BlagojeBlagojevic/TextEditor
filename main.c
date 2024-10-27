#include "defs.h"

//TTF_font *

void SDL_ERR(int code) {

	if((code) < 0) {
		LOG("SDL_ERROR: %s\n", SDL_GetError());
		exit(-1);
		}
	return;
	}

void *P_SDL_ERR(void *ptr) {
	if(ptr == NULL) {
		LOG("SDL_ERROR: %s\n", SDL_GetError());
		exit(-1);
		}
	return ptr;
	}

#define WIDTH  1500
#define HEIGHT 1200
#define WINDOW "Nesto", 100, 100, WIDTH, HEIGHT, 0
#define WHITE 255, 255, 255, 255
#define BLACK 0, 0, 0, 0

#define AT(y, x, value) (value[])

static inline void Text_Renderer_C(SDL_Renderer *renderer, TTF_Font *font,
                                   int startX, int startY, int w_c, int h_c, char* c) {
	static SDL_Color textColor = {255, 255, 255, 255}; //white color
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, c, textColor);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect = {startX, startY, w_c, h_c}; // rectangle where the text is drawn
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	//RENDER CURSOR
	textRect.x = cursor_x * 14;
	textRect.y = cursor_y * 20;
	textRect.w = 14;
	textRect.h = 20;
	SDL_SetRenderDrawColor(renderer, WHITE);
	SDL_RenderFillRect(renderer, &textRect);
	}



#define ENTER 13
#define BACKSPACE 8
#define LEFT_ARROW 1073741904
#define RIGHT_ARROW 1073741903
#define UP_ARROW 1073741906
#define DOWN_ARROW 1073741905
#define CAPS_LOCK 57
void Main_Renderer(SDL_Renderer *renderer, TTF_Font *font, Text* text) {



	SDL_RenderClear(renderer);
	for(int i = 0; i < MAX_LINES; i++)
		Text_Renderer_C(renderer, font, 0, i*20, 14 * text[i].char_in_line + 14, 20, text[i].c);


	SDL_SetRenderDrawColor(renderer, 0,0, 0, 0);
	SDL_RenderPresent(renderer);
	//SDL_Delay(1000);


	}


uint8_t Check_CapsLock() {
	int temp = SDL_GetModState();
	temp = temp & KMOD_CAPS;
	if(temp == KMOD_CAPS) {
		//printf("\nON\n");
		return 1;

		}

	return 0;
	}

void Even_Handler(SDL_Event *event, Text* text) {

	static uint8_t is_char = 0;



	if(SDL_WaitEvent(event))
		if(event->type == SDL_QUIT) {
			//free all assets

			exit(0);

			}
	switch(event->type) {
		case SDL_KEYDOWN:
			printf("KeyPressed\n");
			const uint32_t k = event->key.keysym.sym;
			printf("\nke%d\n", k);
			if(k ==  ENTER) {
				cursor_y++;
				cursor_x = 0;
				}
			else if(k == BACKSPACE) {
				if(cursor_x >= 0) {
					cursor_x--;
					text[cursor_y].char_in_line--;
					
					strcpy(&text[cursor_y].c[cursor_x], &text[cursor_y].c[cursor_x + 1]);
					
					}
				}
			else if(k == DOWN_ARROW) {
				cursor_y++;
				if(text[cursor_y].char_in_line != 0)
					cursor_x = text[cursor_y].char_in_line;
				else 
					cursor_x = 0;
				}
			else if(k == UP_ARROW) {
				if(cursor_y > 0) {
					cursor_y--;
					cursor_x = text[cursor_y].char_in_line;

					}
				else if(cursor_x == 0) {
					if(cursor_y > 0) {
						cursor_y--;
						cursor_x = text[cursor_y].char_in_line;

						}
					}
				else {};
				}
			else if(k == RIGHT_ARROW) {
				if(cursor_x < MAX_CHAR_IN_LINE && text[cursor_y].c[cursor_x]!='\0') {
					cursor_x++;
					//text[cursor_y].c[cursor_x] = ' ';
					//text[cursor_y].char_in_line = cursor_x -1;
					}

				}

			else if(k == LEFT_ARROW) {
				if(cursor_x > 0)
					cursor_x--;
				}
			//else if(k == CAPS_LOCK);
			//else if(k == 9 && Check_CapsLock());
			else {
				if(text[cursor_y].c[cursor_x] != '\0') {
					is_char = 1;
					}
				else {
					is_char = 0;
					}
				const uint8_t is = Check_CapsLock();
				if(k >= 0 && k <= 128) {
					Input(text, cursor_y, cursor_x, k, is_char);
					if(is && k >= 97 && k <= 121) {
						text[cursor_y].c[cursor_x]-=32;
						}
					cursor_x++;
					}

				}


		default:
			break;
		}

	}






int main() {


	char buffer[200];
	memset(buffer, 0, sizeof(char)*200);

	SDL_ERR(SDL_Init(SDL_INIT_VIDEO));
	TTF_Init();
	SDL_Window *window = P_SDL_ERR(SDL_CreateWindow(WINDOW));
	SDL_Renderer *renderer = P_SDL_ERR(SDL_CreateRenderer(window, 0, 0));
	SDL_Event event;
	TTF_Font *font;
	font = TTF_OpenFont("assets/f.ttf", 64); // specify the path to your font file and font size
	if(!font) {
		LOG("Failed to load font: %s\n", TTF_GetError());
		exit(-1);
		}
	Text* text = Alloc_Text();


	while(1) {

		Even_Handler(&event, text);
		Main_Renderer(renderer, font, text);
		}


	SDL_Quit();
	free(font);
	printf("Nesto\n\n");
	return 0;

	}