#ifndef _EVA_App
#define _EVA_App

namespace EVA {
  class App {
  public:
    virtual void setup();
    virtual void loop();
  private:
  };
};

#endif