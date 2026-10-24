#ifndef _menu
#define _menu

#include <EVA.h>
#include <EVA_time.h>
#include <EVA_app.h>
#include <EVA_math.h>

using namespace EVA;

class MenuApp : public EVA::App {
public:
  MenuApp() : EVA::App("Menu") {
    int p = EVA::tfte.drawStringWithBar("Menu", 0, 4, 0);

    int p2 = EVA::tfte.drawStringWithBar("Test App", p+10, 4, 10);
    testappbox = Box(0, p+10, SCREEN_WIDTH - 20, p2);
  }

  ~MenuApp() override {}

  void loop() override {
    EVA::tft.drawCentreString(String(EVA::Time::seconds), SCREEN_CENTER_X, SCREEN_CENTER_Y, 2);

    if (EVA::touched) {
      if (Math::pointInBox(EVA::touchpoint, testappbox)) { EVA::switchToApp = "Test App"; Serial.println("Switching");}
    }
  }
private:
  Box testappbox;
};

#endif