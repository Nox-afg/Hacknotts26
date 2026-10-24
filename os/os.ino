#include <EVA.h>
#include <EVA_Time.h>
#include <EVA_TFT_eSPI_ext.h>

#include <EVA_App.h>
#include <EVA_Apps/menu.h>

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

  //Init Python
  py_initialize();

  bool ok = py_exec("print('Hello world!')", "<string>", EXEC_MODE, NULL);
  if (ok) Serial.println("Python ok?");
  //

  currentApp = new MenuApp();
}

void loop() {  
  EVA::pollTouchscreen();

  if (EVA::Time::pumpVSynced()) {
    currentApp->loop();
  }

  if (switchToApp != "") goto QUITAPP;

  if (currentApp->name != "Menu") {
    tft.drawRect(SCREEN_CENTER_X - 10, SCREEN_HEIGHT - 20, 20, 20, TFT_RED);

    if (EVA::touched && EVA::Math::pointInBox(EVA::touchpoint, SCREEN_CENTER_X - 10, SCREEN_HEIGHT - 20, 20, 20)) {
      QUITAPP:
      delete currentApp;
      tft.fillScreen(TFT_BLACK);
      currentApp = EVA::App::getByName(switchToApp);
      switchToApp = "";
    }
  }
}
