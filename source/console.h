#ifndef CONSOLE_H_
#define CONSOLE_H_

#if _XBOX
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#define CONSOLE_MAX_LINES 20
#define CONSOLE_LAST_LINE CONSOLE_MAX_LINES - 1

class Console {
 public:
  Console(uint16_t pos_x, uint16_t pos_y);
  virtual ~Console();
  void event(SDL_Event event);
  void render(SDL_Renderer *renderer);
  void print(const char *fmt, ...);
  void render();

 protected:
 private:
  const SDL_Color font_color = {0xFF, 0xFF, 0xFF, 0xFF};

  SDL_Texture *console_line[CONSOLE_MAX_LINES] = {NULL};
  SDL_Rect console_line_pos[CONSOLE_MAX_LINES];

  char line_buffer[300];
};

#endif
