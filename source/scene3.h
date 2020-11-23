#ifndef SCENE3_H_
#define SCENE3_H_

#if _XBOX
#include <SDL.h>
#include <hal/debug.h>
#include <hal/video.h>
#include <windows.h>
#include <xboxkrnl/xboxkrnl.h>
#else
#include <SDL2/SDL.h>
#endif
#include "console.h"
#include "scene.h"

class Scene3 : public Scene {
 public:
  Scene3();
  virtual ~Scene3();
  void event(SDL_Event event);
  void render(SDL_Renderer *renderer);

 private:
  SDL_Texture *background_texture;
  Console *console;

  uint16_t counter = 0;

  enum UpdateState {
    Start = 0,
    CheckFirmware,
    GetFirmwareInfo,
    SwitchToBootrom,
    SwitchToBootromFailed,
    LoadFirmwareImage,
    LoadFirmwareImageFailed,
    CheckProgramStatus,
    WritePageCRC,
    WritePageData,
    CheckProgramStatus2,
    CheckProgramPageStatus,
    Completed,
    End
  };

  UpdateState update_stage = Start;

#ifdef _XBOX
  ULONG current_boot;
  ULONG compile_time_raw[4];
  uint16_t current_page = 0;
  uint8_t *firmware = NULL;
  uint32_t crc_value = NULL;

  ULONG return_value;
  long fsize;
#endif
};

#endif
