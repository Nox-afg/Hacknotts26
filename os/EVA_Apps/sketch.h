#ifndef _sketch
#define _sketch

#include <EVA.h>
#include <EVA_app.h>

class SketchApp : public EVA::App {
  public:
      SketchApp() : EVA::App("Sketch") {}

      ~SketchApp() override {}

      void loop() override {
        if (EVA::touched) {
          EVA::tft.drawPixel(EVA::touchpoint.x, EVA::touchpoint.y, TFT_RED, 255);
        }
      }
  private:
};

#endif