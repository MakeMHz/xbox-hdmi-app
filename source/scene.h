#ifndef SCENE_H_
#define SCENE_H_

#if _XBOX
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class Scene {
 public:
  Scene(){};
  virtual ~Scene(){};
  virtual void event(SDL_Event event){};
  virtual void render(SDL_Renderer *renderer){};

 protected:
 private:
};

#endif
