#include "EVA_time.h"
#ifndef _sketch
#define _sketch

#include <EVA.h>
#include <EVA_app.h>

class SketchApp : public EVA::App {
  public:
      Box canvasBox = Box(10, 10, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 60);

      Box colorBox = Box(10, 10 + SCREEN_HEIGHT - 60 + 10, 20, 20);
      bool colorBoxDebounce = false;

      //0 Red
      //1 Green
      //2 Blue
      //3 Cyan
      //4 Yellow
      //5 Magenta
      //6 Black
      //7 White
      int color = 0;
      int colorMap[8] = {TFT_RED, TFT_GREEN, TFT_BLUE, TFT_CYAN, TFT_YELLOW, TFT_MAGENTA, TFT_BLACK, TFT_WHITE};

      Box brushBox = Box(10 + 20 + 10, 10 + SCREEN_HEIGHT - 60 + 10, 20, 20);
      bool brushBoxDebounce = false;

      //0 Pencil
      //1 Brush
      int tool = 0;

      bool sizeBoxActive = false;
      Box sizeBox = Box(10 + 20 + 10 + 20 + 10, 10 + SCREEN_HEIGHT - 60 + 10, 20, 20);
      bool sizeBoxDebounce = false;

      //0 Small
      //1 Med
      //2 Large
      int size = 0;

      Box closeBox = Box(SCREEN_WIDTH - 30, 10 + SCREEN_HEIGHT - 60 + 10, 20, 20);
      int closeBoxBuildup = 0;

      SketchApp() : EVA::App("Sketch", false) {
        EVA::Time::setVSync(true, 600);

        EVA::tft.fillScreen(0xfe94);

        EVA::tft.fillRect(boxDecompose(canvasBox), TFT_WHITE);
        EVA::tft.drawRect(boxDecompose(canvasBox), TFT_DARKGREY);

        EVA::tft.fillRect(boxDecompose(colorBox), TFT_RED);

        EVA::tft.fillRect(boxDecompose(brushBox), TFT_WHITE);
        EVA::tft.setTextColor(TFT_BLACK);
        EVA::tft.drawCentreString("P", brushBox.x + brushBox.w/2, brushBox.y + brushBox.h/2 - 7, 2);

        EVA::tft.drawRect(boxDecompose(closeBox), TFT_RED);
        EVA::tft.setTextColor(TFT_RED);
        EVA::tft.drawCentreString("X", closeBox.x + closeBox.w/2, closeBox.y + closeBox.h/2 - 7, 2);
      }

      ~SketchApp() override {}

      bool touchedLastFrame = false;
      Vec3i lastPoint;

      void colorRedraw() {
        EVA::tft.fillRect(boxDecompose(colorBox), colorMap[color]);

        if (colorMap[color] == TFT_BLACK) {
          EVA::tft.drawRect(boxDecompose(colorBox), TFT_WHITE);
        }
      }

      void toolRedraw() {
        sizeBoxActive = false;

        EVA::tft.fillRect(boxDecompose(brushBox), TFT_WHITE);
        EVA::tft.setTextColor(TFT_BLACK);

        switch (tool) {
          case 0: EVA::tft.drawCentreString("P", brushBox.x + brushBox.w/2, brushBox.y + brushBox.h/2 - 7, 2); break;;
          case 1: 
            EVA::tft.drawCentreString("B", brushBox.x + brushBox.w/2, brushBox.y + brushBox.h/2 - 7, 2);
            sizeBoxActive = true;
            break;
          default:;
        }

        sizeRedraw();
      }

      void sizeRedraw() {
        if (!sizeBoxActive) {
          EVA::tft.fillRect(boxDecompose(sizeBox), 0xfe94);
          return;
        }

        EVA::tft.fillRect(boxDecompose(sizeBox), TFT_WHITE);
        EVA::tft.setTextColor(TFT_BLACK);

        switch (size) {
          case 0: EVA::tft.drawCentreString("S", sizeBox.x + sizeBox.w/2, sizeBox.y + sizeBox.h/2 - 7, 2); return;
          case 1: EVA::tft.drawCentreString("M", sizeBox.x + sizeBox.w/2, sizeBox.y + sizeBox.h/2 - 7, 2); return;
          case 2: EVA::tft.drawCentreString("L", sizeBox.x + sizeBox.w/2, sizeBox.y + sizeBox.h/2 - 7, 2); return;
          default:;
        }
      }

      void pencil() {
        if (touchedLastFrame) {
          EVA::tft.drawLine(lastPoint.x, lastPoint.y, EVA::touchpoint.x, EVA::touchpoint.y, colorMap[color]);
        }
      }

      void brush() {
        static int sizes[3] = {3,6,12};
        EVA::tft.fillCircle(EVA::touchpoint.x, EVA::touchpoint.y, sizes[size], colorMap[color]);
      }

      void loop() override {
        if (EVA::touchInBox(canvasBox)) {
          switch (tool) {
            case 0: pencil(); break;
            case 1: brush(); break;
            default:;
          }
        
          lastPoint = EVA::touchpoint;
          touchedLastFrame = true;
        }
        else {
          touchedLastFrame = false;
        }

        if (EVA::touched) {
          if (EVA::Math::pointInBox(EVA::touchpoint, colorBox) && !colorBoxDebounce) {
            if (++color >= 8) color = 0;
            colorRedraw();

            colorBoxDebounce = true;
          }
        }
        else colorBoxDebounce = false;

        if (EVA::touched) {
          if (EVA::Math::pointInBox(EVA::touchpoint, brushBox) && !brushBoxDebounce) {
            if (++tool >= 2) tool = 0;
            toolRedraw();

            brushBoxDebounce = true;
          }
        }
        else brushBoxDebounce = false;

        if (sizeBoxActive && EVA::touched) {
          if (EVA::Math::pointInBox(EVA::touchpoint, sizeBox) && !sizeBoxDebounce) {
            if (++size >= 3) size = 0;
            sizeRedraw();

            sizeBoxDebounce = true;
          }
        }
        else sizeBoxDebounce = false;

        if (EVA::touchInBox(closeBox)) {
          if (++closeBoxBuildup > 200) { //Hold for a bit
            EVA::switchToApp = "Menu";
          }
        }
        else closeBoxBuildup = 0;
      }
  private:
};

#endif