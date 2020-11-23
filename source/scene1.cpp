#ifdef _XBOX
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <windows.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "common.h"
#include "scene1.h"

extern SDL_Renderer *gRenderer;
extern uint8_t load_scene;

Scene1::Scene1() { background_texture = NULL; }

Scene1::~Scene1(void) {
  if (background_texture) {
    SDL_DestroyTexture(background_texture);
    background_texture = NULL;
  }
}

void Scene1::event(SDL_Event event) {
  switch (event.type) {
    default:
      break;
  }
}

void Scene1::render(SDL_Renderer *renderer) {
  if (background_texture) {
    SDL_DestroyTexture(background_texture);
    background_texture = NULL;
  }

  switch (test_counter) {
    case 0:
      background_texture =
          loadTexture(gRenderer, "D:\\assets\\backgrounds\\test_image_0.png");
      SDL_RenderCopy(gRenderer, background_texture, NULL, NULL);
      break;
    case 1:
      background_texture =
          loadTexture(gRenderer, "D:\\assets\\backgrounds\\test_image_1.png");
      SDL_RenderCopy(gRenderer, background_texture, NULL, NULL);
      break;
    case 2:
      background_texture =
          loadTexture(gRenderer, "D:\\assets\\backgrounds\\test_image_2.png");
      SDL_RenderCopy(gRenderer, background_texture, NULL, NULL);
      break;
    case 3:
      background_texture =
          loadTexture(gRenderer, "D:\\assets\\backgrounds\\test_image_3.png");
      SDL_RenderCopy(gRenderer, background_texture, NULL, NULL);
      break;
    case 4:
      background_texture =
          loadTexture(gRenderer, "D:\\assets\\backgrounds\\test_image_4.png");
      SDL_RenderCopy(gRenderer, background_texture, NULL, NULL);
      break;
    case 5:
      background_texture =
          loadTexture(gRenderer, "D:\\assets\\backgrounds\\test_image_5.png");
      SDL_RenderCopy(gRenderer, background_texture, NULL, NULL);
      break;
    case 6:
      background_texture =
          loadTexture(gRenderer, "D:\\assets\\backgrounds\\test_image_6.png");
      SDL_RenderCopy(gRenderer, background_texture, NULL, NULL);
      break;
    case 7:
      background_texture =
          loadTexture(gRenderer, "D:\\assets\\backgrounds\\test_image_7.png");
      SDL_RenderCopy(gRenderer, background_texture, NULL, NULL);
      break;
    default:
      load_scene = 0;
      break;
  }

  //
  if (test_counter > 0) {
    Sleep(5000);
  }

  //
  test_counter++;
}
