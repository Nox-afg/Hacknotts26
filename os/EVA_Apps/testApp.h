#ifndef _testApp
#define _testApp

#include <EVA_App.h>

class TestApp : public EVA::App {
  public:
      TestApp() : EVA::App("Test App") {
        Serial.println("Testapp have been constructed");
        EVA::tft.drawCentreString("I am a test app", SCREEN_CENTER_X, SCREEN_CENTER_Y, 2);
      }

      ~TestApp() override {
        Serial.println("Testapp have been destructed");
      }

      void loop() override {

      }
  private:
};

#endif