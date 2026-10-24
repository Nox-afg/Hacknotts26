#ifndef _EVA
#define _EVA

#include <SPI.h>
#include <TFT_eSPI.h>               // Display library
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#define SCREEN_CENTER_X (SCREEN_WIDTH/2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT/2)
#define FONT_SIZE 4
#include <EVA_TFT_eSPI_ext.h>

#include <XPT2046_Touchscreen.h>    // Touch library
#define XPT2046_IRQ 36 // Touchscreen pin definitions for CYD
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

#include <EVA_math.h>

namespace EVA {
  static SPIClass touchscreenSPI = SPIClass(VSPI);
  static XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);
  static int touchX, touchY, touchZ;

  static TFT_eSPI tft = TFT_eSPI();
  static TFT_eSPI_ext tfte = TFT_eSPI_ext(tft);

  static bool quitCurrentApp = false;

  static bool isTouchscreenTouched(Vec3i& position) {
    if (touchscreen.tirqTouched() && touchscreen.touched()) {
      TS_Point p = touchscreen.getPoint();

      position.x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
      position.y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
      position.z = p.z;

      return true;
    }

    return false;
  }
};
#endif