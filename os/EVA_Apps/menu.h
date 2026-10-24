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
    Box menuBox = EVA::tfte.drawStringWithBar("Menu", 0, 4, 10);

    int yOffset = menuBox.h+10;

    for (int i = 0; i < EVA::App::appNames.size(); i++) {
      appBoxes.push_back(EVA::tfte.drawStringWithBar(EVA::App::appNames[i], yOffset, 4, 0));

      yOffset += appBoxes.back().h+10;
    }
  }

  ~MenuApp() override {}

  void loop() override {
    if (EVA::touched) {
      for (int i = 0; i < appBoxes.size(); i++)
        if (Math::pointInBox(EVA::touchpoint, appBoxes[i])) { EVA::switchToApp = EVA::App::appNames[i]; Serial.println("Switching");}
    }
  }
private:
  std::vector<Box> appBoxes;
};

#endif