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

namespace EVA {
  static SPIClass touchscreenSPI = SPIClass(VSPI);
  static XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);
  static int touchX, touchY, touchZ;

  static TFT_eSPI tft = TFT_eSPI();
  static TFT_eSPI_ext tfte = TFT_eSPI_ext(tft);

  static bool quitCurrentApp = false;
};
#endif