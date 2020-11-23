#ifndef SCENE1_H_
#define SCENE1_H_

#if _XBOX
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "scene.h"

class Scene1 : public Scene {
 public:
  Scene1();
  virtual ~Scene1();
  void event(SDL_Event event);
  void render(SDL_Renderer* renderer);

 private:
  SDL_Texture* background_texture = NULL;

  uint16_t test_counter = 0;
};

#endif
