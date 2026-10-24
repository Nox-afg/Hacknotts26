#ifndef _EVA_time
#define _EVA_time

#include <chrono>
using namespace std;
using namespace chrono;

namespace EVA {
  class Time {
  public:
    inline static double seconds = 0;

    static void setVSync(bool onOff, float frameCap = 60.) { vSyncTime = (onOff?1.:0.)/frameCap; }

    static int getFPS() { return fps; }
    static double getDT() { return deltaTime; }

    static bool pumpVSynced();
  private:
    inline static int frameCount = 0;
    inline static int fps = 0;

    inline static double deltaTime = 0;
    inline static double vSyncTime = 0;

    inline static time_point<system_clock> lastFrameTime;
    inline static double timeSinceLastFrame = 0;

    inline static time_point<system_clock> lastSecondTime;
    inline static double timeSinceLastSecond = 0;
  };
};

#endif