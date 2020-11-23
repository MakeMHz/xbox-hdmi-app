#ifndef COMMON_H_
#define COMMON_H_

#ifdef _XBOX
#include <SDL.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>
#define XVideoSetMode(...)
#define debugPrint(f_, ...) printf((f_), ##__VA_ARGS__)
#define Sleep sleep
#define XReboot(...)
#endif

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

SDL_Texture* loadTexture(SDL_Renderer* renderer, char* file);
SDL_Texture* drawText(TTF_Font* font, SDL_Color font_color, char* text);

int8_t proccess_event(SDL_Event event);

#endif
