#include "scene4.h"

#include <SDL.h>

#include "common.h"

extern SDL_Renderer *gRenderer;

extern uint8_t load_scene;

Scene4::Scene4() {
  background_texture =
      loadTexture(gRenderer, "D:\\assets\\images\\screen4_background.png");
}

Scene4::~Scene4(void) { SDL_DestroyTexture(background_texture); }

void Scene4::event(SDL_Event event) {
  switch (event.type) {
    case SDL_JOYBUTTONDOWN:
      // B Button - Go back to main menu
      if (event.jbutton.button == 1) {
        load_scene = 0;
      }
      break;
  }
}

void Scene4::render(SDL_Renderer *renderer) {
  SDL_RenderCopy(gRenderer, background_texture, NULL, NULL);
}
