#ifdef _XBOX
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <time.h>
#include <xboxkrnl/xboxkrnl.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif
#include "common.h"
#include "crc32.h"
#include "i2c_map.h"
#include "scene3.h"

extern SDL_Window *window;
extern SDL_Renderer *gRenderer;

extern uint8_t load_scene;

Scene3::Scene3() {
  background_texture =
      loadTexture(gRenderer, "D:\\assets\\images\\screen3_background.png");
  console = new Console(50, 20);
}

Scene3::~Scene3(void) {
  SDL_DestroyTexture(background_texture);
  delete console;
}

void Scene3::event(SDL_Event event) {
  int8_t button_press = proccess_event(event);

  switch (button_press) {
    case SDL_CONTROLLER_BUTTON_B:
      // Go back to main menu
      if (update_stage == UpdateState::End) {
        load_scene = 0;
      }
      break;
    default:
      break;
  }
}

void Scene3::render(SDL_Renderer *renderer) {
  switch (update_stage) {
    case UpdateState::Start: {
      console->print("Checking for XboxHDMI Board");
      update_stage = UpdateState::CheckFirmware;
      break;
    }
#ifdef _XBOX
    case UpdateState::CheckFirmware: {
      HalReadSMBusValue(I2C_HDMI_ADRESS, I2C_BOOT_MODE, false, &current_boot);

      console->print("Found... Revision: 3C");
      console->print("Firmware Mode: 0x%02X", current_boot);

      update_stage = UpdateState::GetFirmwareInfo;
      break;
    }
    case UpdateState::GetFirmwareInfo: {
      HalReadSMBusValue(I2C_HDMI_ADRESS, I2C_COMPILE_TIME0, false,
                        &compile_time_raw[0]);
      HalReadSMBusValue(I2C_HDMI_ADRESS, I2C_COMPILE_TIME1, false,
                        &compile_time_raw[1]);
      HalReadSMBusValue(I2C_HDMI_ADRESS, I2C_COMPILE_TIME2, false,
                        &compile_time_raw[2]);
      HalReadSMBusValue(I2C_HDMI_ADRESS, I2C_COMPILE_TIME3, false,
                        &compile_time_raw[3]);

      time_t compile_time = (compile_time_raw[0] << 24) +
                            (compile_time_raw[1] << 16) +
                            (compile_time_raw[2] << 8) + (compile_time_raw[3]);
      console->print("Firmware Date: %i", compile_time);

      update_stage = UpdateState::SwitchToBootrom;
      break;
    }
    case UpdateState::SwitchToBootrom: {
      if (current_boot != BOOT_HDMI_PROGRAM) {
        console->print("Switching to bootrom for flashing");
        HalWriteSMBusValue(I2C_HDMI_ADRESS, I2C_LOAD_APP, 0, 0x42);

        Sleep(2000);

        //
        HalReadSMBusValue(I2C_HDMI_ADRESS, I2C_BOOT_MODE, false, &current_boot);
        console->print("Firmware Mode: 0x%02X", current_boot);
      }

      update_stage = (current_boot == BOOT_HDMI_BOOTROM)
                         ? UpdateState::LoadFirmwareImage
                         : UpdateState::SwitchToBootromFailed;
      break;
    }
    case UpdateState::SwitchToBootromFailed: {
      console->print("Failed to switch to flash mode", current_boot);
      update_stage = UpdateState::End;
      break;
    }
    case UpdateState::LoadFirmwareImage: {
      console->print("Loading firmware.bin");
      FILE *fp = fopen("D:\\firmware.bin", "rb");

      if(fp) {

        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
        rewind(fp);

        firmware = (uint8_t *)malloc(fsize + 1);
        fread(firmware, 1, fsize, fp);
        fclose(fp);

        update_stage = UpdateState::CheckProgramStatus;
      } else {
        update_stage = UpdateState::LoadFirmwareImageFailed;
      }

      break;
    }
    case UpdateState::LoadFirmwareImageFailed: {
      console->print("Failed to load firmware.bin");

      update_stage = UpdateState::End;
      break;
    }
    case UpdateState::CheckProgramStatus: {
      HalReadSMBusValue(I2C_HDMI_ADRESS, I2C_PROG_BUSY, false, &return_value);
      if (return_value) {
        console->print("Flash is busy...");
        break;
      }
      HalReadSMBusValue(I2C_HDMI_ADRESS, I2C_PROG_FULL, false, &return_value);
      if (return_value) {
        console->print("Flash is busy...");
        break;
      }

      update_stage = UpdateState::WritePageCRC;
      break;
    }
    case UpdateState::WritePageCRC: {
      // Send each byte of the page
      crc_value = CRC_init();
      for (uint16_t index = 0; index < 1024; index++) {
        uint32_t file_offset = index + (current_page * 1024);

        if (file_offset < fsize) {
          crc_value = CRC_addByte(crc_value, firmware[file_offset]);
        } else {
          crc_value = CRC_addByte(crc_value, 0x00);
        }
      }
      crc_value = CRC_result(crc_value);

      HalWriteSMBusValue(I2C_HDMI_ADRESS, I2C_PROG_CRC3, 0,
                         (crc_value >> 24) & 0xFF);
      HalWriteSMBusValue(I2C_HDMI_ADRESS, I2C_PROG_CRC2, 0,
                         (crc_value >> 16) & 0xFF);
      HalWriteSMBusValue(I2C_HDMI_ADRESS, I2C_PROG_CRC1, 0,
                         (crc_value >> 8) & 0xFF);
      HalWriteSMBusValue(I2C_HDMI_ADRESS, I2C_PROG_CRC0, 0, (crc_value)&0xFF);

      console->print("Writing Page %02i (CRC: 0x%08X)", current_page,
                     crc_value);

      update_stage = UpdateState::WritePageData;
      break;
    }
    case UpdateState::WritePageData: {
      HalWriteSMBusValue(I2C_HDMI_ADRESS, I2C_PROG_WRITE, 0, current_page);

      // Send each byte of the page
      for (uint16_t index = 0; index < 1024; index++) {
        uint32_t file_offset = index + (current_page * 1024);
        if (file_offset < fsize) {
          HalWriteSMBusValue(I2C_HDMI_ADRESS, I2C_PROG_DATA, 0,
                             firmware[file_offset]);
        } else {
          HalWriteSMBusValue(I2C_HDMI_ADRESS, I2C_PROG_DATA, 0, 0x00);
        }
      }

      Sleep(1000);

      update_stage = UpdateState::CheckProgramStatus2;
      break;
    }
    case UpdateState::CheckProgramStatus2: {
      HalReadSMBusValue(I2C_HDMI_ADRESS, I2C_PROG_BUSY, false, &return_value);
      if (return_value) {
        console->print("Flash is busy...");
        break;
      }
      HalReadSMBusValue(I2C_HDMI_ADRESS, I2C_PROG_FULL, false, &return_value);
      if (return_value) {
        console->print("Flash is busy...");
        break;
      }

      update_stage = UpdateState::CheckProgramPageStatus;
      break;
    }
    case UpdateState::CheckProgramPageStatus: {
      HalReadSMBusValue(I2C_HDMI_ADRESS, I2C_PROG_ERROR, false, &return_value);
      switch (return_value) {
        case I2C_PROG_ERROR_ERASE:
          console->print("Failed to erase flash...");
          break;
        case I2C_PROG_ERROR_WRITE:
          console->print("Failed to write flash...");
          break;
        case I2C_PROG_ERROR_CRC:
          console->print("Failed to verify CRC...");
          break;
        default:
          current_page++;
          break;
      }

      update_stage = (current_page < 38) ? UpdateState::CheckProgramStatus
                                         : UpdateState::Completed;
      break;
    }
    case UpdateState::Completed: {
      console->print("Flash complete");
      console->print("Please restart console...");
      update_stage = UpdateState::End;
      break;
    }
#endif
    default: {
      break;
    }
  }

  SDL_RenderCopy(gRenderer, background_texture, NULL, NULL);
  console->render();

  if (update_stage != UpdateState::End) {
    Sleep(1000);
  }
}
