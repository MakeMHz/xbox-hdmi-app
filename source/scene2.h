#ifndef SCENE2_H_
#define SCENE2_H_

#if _XBOX
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "scene.h"

class Scene2 : public Scene {
 public:
  Scene2();
  virtual ~Scene2();
  void event(SDL_Event event);
  void render(SDL_Renderer *renderer);

 private:
  void readConfig(void);
  void updateConfig(void);
  void saveConfig(void);
  void recalcSliders(void);

  uint8_t cursor_pos = 0;

  SDL_Texture *background_texture;
  SDL_Texture *menu_texture;
  SDL_Texture *menu_backdrop;

  SDL_Texture *box_unselected_texture;
  SDL_Texture *box_selected_texture;
  SDL_Texture *box_highlight_texture;

  SDL_Texture *texture_video_luma = NULL;
  SDL_Texture *texture_video_cb = NULL;
  SDL_Texture *texture_video_cr = NULL;

  SDL_Texture *bar_unselected_texture;
  SDL_Texture *bar_selected_texture;

  const SDL_Color font_color = {0xFF, 0xFF, 0xFF, 0xFF};

  const SDL_Rect menu_pos = {392, 35, 306, 406};
  const SDL_Rect box_video0_pos = {412, 160, 22, 22};
  const SDL_Rect box_video1_pos = {550, 160, 22, 22};
  const SDL_Rect box0_selected_pos = {412, 192, 115, 4};
  const SDL_Rect box1_selected_pos = {550, 192, 115, 4};

  const SDL_Rect box_wide0_pos = {412, 84, 22, 22};
  const SDL_Rect box_wide1_pos = {505, 84, 22, 22};
  const SDL_Rect box_wide2_pos = {600, 84, 22, 22};
  const SDL_Rect box_wide0_selected_pos = {412, 115, 85, 4};
  const SDL_Rect box_wide1_selected_pos = {505, 115, 85, 4};
  const SDL_Rect box_wide2_selected_pos = {600, 115, 85, 4};

  // Text position
  SDL_Rect video_luma_pos = {630, 220, 0, 0};
  SDL_Rect video_cb_pos = {630, 278, 0, 0};
  SDL_Rect video_cr_pos = {630, 338, 0, 0};

  // Slider position
  SDL_Rect video_luma_slider_pos = {414, 230, 5, 24};
  SDL_Rect video_cb_slider_pos = {414, 286, 5, 24};
  SDL_Rect video_cr_slider_pos = {414, 345, 5, 24};

  const char *test_images[7] = {"assets/backgrounds/test_image_0.png",
                                "assets/backgrounds/test_image_1.png",
                                "assets/backgrounds/test_image_2.png",
                                "assets/backgrounds/test_image_3.png",
                                "assets/backgrounds/test_image_4.png",
                                "assets/backgrounds/test_image_5.png",
                                "assets/backgrounds/test_image_6.png"};

  int8_t video_widescreen = 0;
  int8_t video_mode_out = 0;
  int8_t video_adjust_luma = 0;
  int8_t video_adjust_cb = 0;
  int8_t video_adjust_cr = 0;

  bool text_dirty = true;
  bool show_help = false;
};

#endif
