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

    inline static std::vector<String> appNames = {
      "Test App",
      "Sketch",
      "Snake App"
    };
    static EVA::App* getByName(const String& appName);
  private:
  };
};

#endif