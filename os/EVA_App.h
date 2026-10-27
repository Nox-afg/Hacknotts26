#ifndef _EVA_app
#define _EVA_app

#include <Arduino.h>

namespace EVA {
  class App {
  public:
    String name;
    bool defaultClose;

    App(String nameIn, bool useDefaultClose = true) : name(nameIn), defaultClose(useDefaultClose) {}
    virtual ~App() {}
    virtual void loop() {}

    inline static std::vector<String> appNames = {
      "Test App",
      "Sketch",
      "Snake App",
      "ChatGPT",
      "Music"
    };
    static EVA::App* getByName(const String& appName);
  private:
  };
};

#endif