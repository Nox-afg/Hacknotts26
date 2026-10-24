#include <EVA.h>
#include <EVA_Time.h>
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
  currentApp = new TestApp();
}

void loop() {
  Vec3i touch; 

  if (currentApp->name != "Menu") {
    tft.drawRect(SCREEN_CENTER_X - 10, SCREEN_HEIGHT - 40, 20, 40, TFT_RED);
    if (EVA::isTouchscreenTouched(touch) && EVA::Math::pointInBox(touch, SCREEN_CENTER_X - 10, SCREEN_HEIGHT - 40, 20, 40)) {
      //Quit App
      delete currentApp;
      tft.fillScreen(TFT_BLACK);
      currentApp = new MenuApp();
    }
  }
  
  if (EVA::Time::pumpVSynced()) {
    currentApp->loop();
  }
}
