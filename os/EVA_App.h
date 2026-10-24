#ifndef _EVA_app
#define _EVA_app

#include <Arduino.h>

namespace EVA {
  class App {
  public:
    String name;

    App(String nameIn) : name(nameIn) {}
    virtual ~App() {}
    virtual void loop() {}

    static EVA::App* getByName(const String& appName);
  private:
  };
};

#endif