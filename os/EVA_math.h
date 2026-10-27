#ifndef _EVA_math
#define _EVA_math

#include <cstdint>
#include <algorithm>

namespace EVA {
  struct Vec3i {
    int32_t x,y,z;

    void printToSerial() { Serial.printf("%d %d %d\n", x,y,z); }
  };

  #define boxDecompose(b) b.x, b.y, b.w, b.h
  struct Box {
    int32_t x,y,w,h;

    Box(int32_t x, int32_t y, int32_t w, int32_t h) : x(x), y(y), w(w), h(h) {}
    Box() : x(0), y(0), w(0), h(0) {}

    int32_t centerX() { return x+w/2; }
    int32_t centerY() { return y+h/2; }
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

    static uint32_t lerpColor(uint32_t c1, uint32_t c2, float t) {
      // Extract channels
      uint8_t a1 = (c1 >> 24) & 0xFF, r1 = (c1 >> 16) & 0xFF,
              g1 = (c1 >>  8) & 0xFF, b1 =  c1        & 0xFF;
      uint8_t a2 = (c2 >> 24) & 0xFF, r2 = (c2 >> 16) & 0xFF,
              g2 = (c2 >>  8) & 0xFF, b2 =  c2        & 0xFF;

      auto mix = [t](uint8_t x, uint8_t y) -> uint8_t {
          return static_cast<uint8_t>(x + (y - x) * t + 0.5f);
      };

      return (uint32_t(mix(a1, a2)) << 24)
          | (uint32_t(mix(r1, r2)) << 16)
          | (uint32_t(mix(g1, g2)) <<  8)
          |  uint32_t(mix(b1, b2));
    }

    static uint16_t lerp565(uint16_t c1, uint16_t c2, float t) {
      auto to888 = [](uint16_t c) {
          uint8_t r = (c >> 11) & 0x1F, g = (c >> 5) & 0x3F, b = c & 0x1F;
          return (uint32_t(r * 255 / 31) << 16) |
                (uint32_t(g * 255 / 63) <<  8) |
                  uint32_t(b * 255 / 31);
      };
      uint32_t a = to888(c1), b = to888(c2);
      uint32_t m = lerpColor(0xFF000000 | a, 0xFF000000 | b, t);

      uint8_t r = (m >> 16) & 0xFF, g = (m >> 8) & 0xFF, bl = m & 0xFF;
      return ((r >> 3) << 11) | ((g >> 2) << 5) | (bl >> 3);
    }

    static float distance(int x1, int y1, int x2, int y2) {
      return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    }

    static float fastDistance(int x1, int y1, int x2, int y2) {
      return pow(x2-x1, 2) + pow(y2-y1, 2);
    }
  private:
  };
};

#endif