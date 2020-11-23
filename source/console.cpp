#ifdef _XBOX
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdarg.h>
#include <stdio.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "common.h"
#include "console.h"

extern SDL_Window *window;
extern SDL_Renderer *gRenderer;
extern TTF_Font *gFontSmall;

Console::Console(uint16_t pos_x, uint16_t pos_y) {
  for (uint8_t index = 0; index < CONSOLE_MAX_LINES; index++) {
    console_line_pos[index].x = pos_x;
    console_line_pos[index].y = 20 + (20 * index);
  }
}

Console::~Console(void) {
  for (uint8_t index = 0; index < CONSOLE_MAX_LINES; index++) {
    if (console_line[index] != NULL) {
      SDL_DestroyTexture(console_line[index]);
    }
  }
}

void Console::event(SDL_Event event) {}

void Console::render(SDL_Renderer *renderer) {}

void Console::print(const char *fmt, ...) {
  va_list args;

  // Shift all lines up one
  if (console_line[0] != NULL) {
    SDL_DestroyTexture(console_line[0]);
    console_line[0] = NULL;
  }

  memmove(console_line, console_line + 1,
          (CONSOLE_LAST_LINE * sizeof(SDL_Texture *)));

  for (uint8_t index = 0; index < CONSOLE_MAX_LINES - 1; index++) {
    console_line[index] = console_line[index + 1];

    console_line_pos[index].w = console_line_pos[index + 1].w;
    console_line_pos[index].h = console_line_pos[index + 1].h;
  }

  va_start(args, fmt);
  vsnprintf(line_buffer, sizeof(line_buffer), fmt, args);
  va_end(args);

  console_line[CONSOLE_LAST_LINE] =
      drawText(gFontSmall, font_color, line_buffer);
  SDL_QueryTexture(console_line[CONSOLE_LAST_LINE], NULL, NULL,
                   &console_line_pos[CONSOLE_LAST_LINE].w,
                   &console_line_pos[CONSOLE_LAST_LINE].h);
}

void Console::render() {
  for (uint8_t index = 0; index < CONSOLE_MAX_LINES; index++) {
    if (console_line[index] != NULL) {
      SDL_RenderCopy(gRenderer, console_line[index], NULL,
                     &console_line_pos[index]);
    }
  }
}
