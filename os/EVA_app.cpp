#include <EVA_app.h>
#include <EVA_apps/menu.h>
#include <EVA_apps/testApp.h>
#include <EVA_apps/sketch.h>
#include <EVA_apps/snakeApp.h>
#include <Arduino.h>

EVA::App* EVA::App::getByName(const String& appName) {
  if (appName == "Test App") return new TestApp();
  if (appName == "Sketch") return new SketchApp();
  if (appName == "Snake App") return new SnakeApp();

  return new MenuApp();
}