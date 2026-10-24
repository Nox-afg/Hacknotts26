#ifndef _EVA
#define _EVA

// Display library
#include <SPI.h>
#include <TFT_eSPI.h>               
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#define SCREEN_CENTER_X (SCREEN_WIDTH/2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT/2)
#define FONT_SIZE 4
#include <EVA_TFT_eSPI_ext.h>

// Touch library
#include <XPT2046_Touchscreen.h>    
// Touchscreen pin definitions for CYD
#define XPT2046_IRQ 36 
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

#include <EVA_App.h>
#include <EVA_math.h>

#include <pocketpy.h>

namespace EVA {
  inline SPIClass touchscreenSPI = SPIClass(VSPI);
  inline XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);
  inline bool touched = false;
  inline Vec3i touchpoint;

  inline TFT_eSPI tft = TFT_eSPI();
  inline TFT_eSPI_ext tfte = TFT_eSPI_ext(tft);

  inline App* currentApp;
  inline String switchToApp = "";

  inline void pollTouchscreen() {
    if (touchscreen.tirqTouched() && touchscreen.touched()) {
      TS_Point p = touchscreen.getPoint();

      touchpoint.x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
      touchpoint.y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
      touchpoint.z = p.z;

      touched = true;
      return;
    }

    touched = false;
  }
};
#endif