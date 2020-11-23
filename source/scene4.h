#ifndef SCENE4_H_
#define SCENE4_H_

#include <SDL.h>

#include "scene.h"

class Scene4 : public Scene {
 public:
  Scene4();
  virtual ~Scene4();
  void event(SDL_Event event);
  void render(SDL_Renderer* renderer);

 private:
  SDL_Texture* background_texture;
};

#endif
