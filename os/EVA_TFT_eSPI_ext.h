#ifndef _EVA_TFT_eSPI_ext
#define _EVA_TFT_eSPI_ext

#include <SPI.h>
#include <TFT_eSPI.h>    
#include <XPT2046_Touchscreen.h> 
#include <EVA_math.h>

#if !defined(SCREEN_WIDTH) || !defined(SCREEN_HEIGHT)
#error "Screen Info must be defined for tft eva extensions!"
#endif

using namespace std;

class TFT_eSPI_ext {
public:
  TFT_eSPI tft;
  TFT_eSPI_ext(TFT_eSPI tftIn) : tft(tftIn) {}

  EVA::Box drawStringWithBar(const String string, int y, int font, int textcolor, int bgcolor, int edgeColor = 0, int yPadding = 0) {
    int textWidth = tft.textWidth(string, font);
    int textHeight = tft.fontHeight(font);

    tft.setTextPadding(0);
    tft.fillRoundRect(0, y, SCREEN_WIDTH, textHeight - 7 + 2*yPadding, 0, bgcolor);
    if (edgeColor)
      tft.drawRoundRect(0, y, SCREEN_WIDTH, textHeight - 7 + 2*yPadding, 0, edgeColor);

    tft.setTextColor(textcolor);
    tft.drawString(string, SCREEN_CENTER_X - textWidth/2, y + yPadding, font);

    return EVA::Box(0, y, SCREEN_WIDTH, textHeight - 7 + 2*yPadding);
  }

  void fillRectGradient(EVA::Box rect, uint16_t c1, uint16_t c2, int anchorX, int anchorY) {
    float maxDistance = 0;

    for (int y = rect.y; y < rect.y+rect.h; y+=8) {
      for (int x = rect.x; x < rect.x+rect.w; x+=8) {
        float distance = EVA::Math::fastDistance(x, y, anchorX, anchorY);
        if (distance > maxDistance) maxDistance = distance;
      }
    }

    for (int y = rect.y; y < rect.y+rect.h; y++) {
      for (int x = rect.x; x < rect.x+rect.w; x++) {
        float nDistance = EVA::Math::fastDistance(x, y, anchorX, anchorY) / maxDistance;

        tft.drawPixel(x,y, EVA::Math::lerp565(c1, c2, nDistance));
      }
    }
  }
  
private:
};


#endif