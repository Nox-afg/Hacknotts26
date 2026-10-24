#ifndef _EVA_App
#define _EVA_App

namespace EVA {
  class App {
  public:
    String name;

    App(String nameIn) : name(nameIn) {}
    virtual ~App() {}
    virtual void loop() {}
  private:
  };
};

#endif