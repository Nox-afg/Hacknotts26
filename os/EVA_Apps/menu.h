#ifndef _menu
#define _menu

#include <EVA_App.h>
#include <EVA_math.h>

using namespace EVA;

class MenuApp : public EVA::App {
  public:
      MenuApp() : EVA::App("Menu") {
        Serial.println("Menu have been constructed");
        EVA::tfte.drawStringWithBar("Menu", 0, 4, 1);

        EVA::tft.drawRect(SCREEN_CENTER_X-20, SCREEN_CENTER_Y-20, 40, 40, TFT_BLUE);
      }

      ~MenuApp() override {
        Serial.println("Menu have been destructed");
      }

      void loop() override {
        Vec3i touch;

        if (EVA::isTouchscreenTouched(touch)) {
          if (EVA::Math::pointInBox(touch, SCREEN_CENTER_X-20, SCREEN_CENTER_Y-20, 40, 40)) {
            Serial.printf("%d %d %d\n", touch.x, touch.y, touch.z);
          }
        }
      }
  private:
};

#endif