#include "scene0.h"

#include <SDL.h>
#include <SDL_image.h>
#include <hal/debug.h>
#include <hal/video.h>
#include <hal/xbox.h>
#include <windows.h>

#include "common.h"

extern SDL_Renderer *gRenderer;
extern uint8_t load_scene;
extern bool running;

Scene0::Scene0() {
  background_texture =
      loadTexture(gRenderer, "D:\\assets\\images\\screen0_background.png");
  arrow_texture = loadTexture(gRenderer, "D:\\assets\\images\\arrow.png");

  current_item = 0;
}

Scene0::~Scene0(void) {
  SDL_DestroyTexture(background_texture);
  SDL_DestroyTexture(arrow_texture);
}

void Scene0::event(SDL_Event event) {
  int8_t button_press = proccess_event(event);

  ULONG temp_read = 0;

  switch (button_press) {
    case SDL_CONTROLLER_BUTTON_A:
      load_scene = current_item + 1;
      break;
    case SDL_CONTROLLER_BUTTON_B:
      running = false;
      break;
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
      current_item = MAX(current_item - 1, 0);
      secret_counter = 0;
      break;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
      if (secret_found) {
        current_item = MIN(current_item + 1, 3);
      } else {
        current_item = MIN(current_item + 1, 2);
        secret_counter++;

        if (secret_counter > 20) {
          secret_found = true;
        }
      }
      break;
    default:
      break;
  }
}

void Scene0::render(SDL_Renderer *renderer) {
  SDL_RenderCopy(gRenderer, background_texture, NULL, NULL);
  SDL_RenderCopy(gRenderer, arrow_texture, NULL, &arrow_pos[current_item]);
}
