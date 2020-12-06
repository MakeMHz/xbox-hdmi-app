#ifndef SCENE0_H_
#define SCENE0_H_

#if _XBOX
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "scene.h"

class Scene0 : public Scene {
 public:
  Scene0();
  virtual ~Scene0();
  void event(SDL_Event event);
  void render(SDL_Renderer *renderer);

 private:
  uint8_t current_item = 0;
  uint8_t secret_counter = 0;
  bool secret_found = false;

  SDL_Texture *background_texture;
  SDL_Texture *arrow_texture;
  const SDL_Color font_color = {0xFF, 0xFF, 0xFF, 0xFF};

  SDL_Texture *info_line[1] = { NULL };
  SDL_Rect info_line_pos[1] = {
      {80, 420, 0, 0},  // Firmware Version
  };

  const SDL_Rect arrow_pos[4] = {
      {406, 190 + (40 * 0), 24, 16},  // Self Test
      {406, 190 + (40 * 1), 24, 16},  // Advance
      {406, 190 + (40 * 2), 24, 16},  // Firemware Update
      {532, 406, 24, 16}              // Secret Menu
  };

  uint8_t firmware_version[3] = { 0 };
  char text_firmware[100] = { 0 };
};

#endif
