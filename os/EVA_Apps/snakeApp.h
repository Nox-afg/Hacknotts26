#ifndef _SnakeApp
#define _SnakeApp

#include <EVA.h>
#include <EVA_app.h>

#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

class SnakeApp : public EVA::App {
  public:
    enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

    // Game state
    int fruitCordX, fruitCordY;
    int x, y;                 // snake head position
    int playerScore;
    bool isGameOver;
    int snakeTailX[100], snakeTailY[100];
    snakesDirection sDir;

    SnakeApp() : EVA::App("Snake App") {
      GameInit();
    }

    ~SnakeApp() override {}

    void loop() override {
      if (EVA::touched) {
        int tx = EVA::touchpoint.x;
        int ty = EVA::touchpoint.y;

        // Top band = UP, bottom band = DOWN, middle band = LEFT/RIGHT
        if (ty < 80) {
          sDir = UP;
        }
        else if (ty > 240) {
          sDir = DOWN;
        }
        else if (tx < 120) {
          sDir = LEFT;
        }
        else {
          sDir = RIGHT;
        }
      }

      // Move on a timer so the snake isn't tied to loop() speed
      static unsigned long lastMove = 0;
      if (millis() - lastMove >= 150) {
        lastMove = millis();
        move();
      }
    }

  private:
    void move() {
      if (sDir == STOP) return;

      // Erase old head
      EVA::tft.fillRect(x, y, 20, 26, TFT_BLACK);

      if (sDir == UP)         y -= 26;
      else if (sDir == DOWN)  y += 26;
      else if (sDir == LEFT)  x -= 20;
      else if (sDir == RIGHT) x += 20;

      // Wall collision
      if (x < 0 || y < 0 || x + 20 > 240 || y + 26 > 320) {
        GameInit();
        return;
      }

      EVA::tft.fillRect(x, y, 20, 26, TFT_RED);
    }

    void GameInit() {
      isGameOver = false;
      sDir = STOP;
      x = 240 / 2;
      y = 320 / 2;
      fruitCordX = rand() % 240;
      fruitCordY = rand() % 320;
      playerScore = 0;

      EVA::tft.fillScreen(TFT_BLACK);
      EVA::tft.fillRect(x, y, 20, 26, TFT_RED);
      EVA::tft.fillCircle(fruitCordX, fruitCordY, 10, TFT_PINK);
    }
};

#endif