#ifndef _EVA_math
#define _EVA_math

#include <cstdint>
#include <algorithm>

namespace EVA {
  struct Vec3i {
    int32_t x,y,z;

    void printToSerial() { Serial.printf("%d %d %d\n", x,y,z); }
  };

  struct Box {
    int32_t x,y,w,h;

    Box(int32_t x, int32_t y, int32_t w, int32_t h) : x(x), y(y), w(w), h(h) {}
    Box() : x(0), y(0), w(0), h(0) {}
  };

  class Math {
  public:
    static bool pointInBox(const Vec3i point, int32_t x, int32_t y, int32_t w, int32_t h) {
      return (
        (point.x >= x && point.x <= (x+w))
        &&
        (point.y >= y && point.y <= (y+h))
      );
    }

    static bool pointInBox(const Vec3i point, const Box box) {
      return pointInBox(point, box.x, box.y, box.w, box.h);
    }
  private:
  };
};

#endif