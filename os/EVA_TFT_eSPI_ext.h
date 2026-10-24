#ifndef _EVA_TFT_eSPI_ext
#define _EVA_TFT_eSPI_ext

#include <SPI.h>
#include <TFT_eSPI.h>    
#include <XPT2046_Touchscreen.h> 

#if !defined(SCREEN_WIDTH) || !defined(SCREEN_HEIGHT)
#error "Screen Info must be defined for tft eva extensions!"/Users/quent/Desktop/Stuff/make code/Arduino/Hacknotts26/os/EVA_Apps/menu.h
#endif

using namespace std;

class TFT_eSPI_ext {
public:
  TFT_eSPI tft;
  TFT_eSPI_ext(TFT_eSPI tftIn) : tft(tftIn) {}

  void drawStringWithBar(const char* string, int y, int font, int yPadding = 0) {
    int textWidth = tft.textWidth(string, font);
    int textHeight = tft.fontHeight(font);

    tft.setTextPadding(0);
    tft.fillRoundRect(0, y, SCREEN_WIDTH, textHeight - 7 + 2*yPadding, 0, TFT_WHITE);
    tft.setTextColor(TFT_RED);
    tft.drawString(string, SCREEN_CENTER_X - textWidth/2, y + yPadding, font);
  }
  
private:
};


#endif