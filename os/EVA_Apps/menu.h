#ifndef _menu
#define _menu

#include <EVA_App.h>

class MenuApp : public EVA::App {
  public:
      void setup() override {
        EVA::tfte.drawStringWithBar("Menu", 0, 4, 1);

        EVA::tft.drawRect(SCREEN_CENTER_X-20, SCREEN_CENTER_Y-20, 40, 40, TFT_BLUE);
      }

      void loop() override {

      }
  private:
};

#endif