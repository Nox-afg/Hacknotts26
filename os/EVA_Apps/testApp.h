#ifndef _testApp
#define _testApp

#include <EVA.h>
#include <EVA_app.h>

class TestApp : public EVA::App {
  public:
      TestApp() : EVA::App("Test App") {
        EVA::tft.drawCentreString("I am a test app", SCREEN_CENTER_X, SCREEN_CENTER_Y, 2);
      }

      ~TestApp() override {}

      void loop() override {}
  private:
};

#endif