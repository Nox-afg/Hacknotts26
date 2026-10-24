#include <EVA.h>
#include <EVA_TFT_eSPI_ext.h>

#include <EVA_App.h>
#include <EVA_Apps/menu.h>
#include <EVA_Apps/testApp.h>

EVA::App* currentApp;

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 CYD Starting...");

  //Init Touchscreen
  EVA::touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  EVA::touchscreen.begin(EVA::touchscreenSPI);
  EVA::touchscreen.setRotation(0);

  //Init Display
  EVA::tft.init();
  EVA::tft.invertDisplay(true);
  EVA::tft.setRotation(0);
  EVA::tft.fillScreen(TFT_BLACK);

  //Init File System
  //

  //Load App
  currentApp = new MenuApp();
  currentApp->setup();
}

void loop() {
  if (EVA::Time::pumpVSynced()) {
    currentApp->loop();
  }
}
