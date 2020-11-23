#ifdef _XBOX
#include <SDL.h>
#include <SDL_image.h>
#include <hal/debug.h>
#include <hal/video.h>
#include <hal/xbox.h>
#include <windows.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "common.h"

extern SDL_Renderer *gRenderer;

SDL_Texture *loadTexture(SDL_Renderer *renderer, char *file) {
  SDL_Texture *newTexture = NULL;

  SDL_Surface *surface = IMG_Load(file);
  if (surface == NULL) {
    debugPrint("Unable to load image %s! SDL_image Error: %s\n", file,
               IMG_GetError());
  } else {
    // Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (newTexture == NULL) {
      debugPrint("Unable to create texture from %s! SDL Error: %s\n", file,
                 SDL_GetError());
    }

    SDL_FreeSurface(surface);
  }

  return newTexture;
}

SDL_Texture* drawText(TTF_Font *font, SDL_Color font_color, char *text) {
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = TTF_RenderText_Blended(font, text, font_color);

	if(surface == NULL) {
		debugPrint("TTF_RenderText failed: %s", TTF_GetError());
		Sleep(2000);
	}

	texture = SDL_CreateTextureFromSurface(gRenderer, surface);
	SDL_FreeSurface(surface);
	if(texture == NULL) {
		debugPrint("Couldn't create texture: %s\n", SDL_GetError());
		Sleep(2000);
	}

	return texture;
}

int8_t proccess_event(SDL_Event event) {
  int8_t button_press = SDL_CONTROLLER_BUTTON_INVALID;

#ifdef _XBOX
  switch (event.type) {
    case SDL_CONTROLLERBUTTONDOWN:
      button_press = event.cbutton.button;
      break;
    default:
      break;
  }
#else
  switch (event.type) {
    case SDL_QUIT:
    case SDL_JOYHATMOTION:
      // D-Pad
      if (event.jhat.hat == 0) {
        if (event.jhat.value == SDL_HAT_UP) {
          button_press = SDL_CONTROLLER_BUTTON_DPAD_UP;
        }
        if (event.jhat.value == SDL_HAT_DOWN) {
          button_press = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
        }
        if (event.jhat.value == SDL_HAT_LEFT) {
          button_press = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
        }
        if (event.jhat.value == SDL_HAT_RIGHT) {
          button_press = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
        }
      }
      break;
    case SDL_JOYBUTTONDOWN:
      // A Press
      if (event.jbutton.button == 0) {
        button_press = SDL_CONTROLLER_BUTTON_A;
      }
      // B Press
      if (event.jbutton.button == 1) {
        button_press = SDL_CONTROLLER_BUTTON_B;
      }
      // X Press
      if (event.jbutton.button == 2) {
        button_press = SDL_CONTROLLER_BUTTON_X;
      }
      // Y Press
      if (event.jbutton.button == 3) {
        button_press = SDL_CONTROLLER_BUTTON_Y;
      }
      break;
    default:
      break;
  }
#endif

  return button_press;
}
