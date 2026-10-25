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
    static const int cols = 12, rows = 12;
    static const int CELL_WIDTH = 20, CELL_HEIGHT = 26;
    static const int MAX_LEN = cols * rows;
    int fruitCordX, fruitCordY;
    int x, y, length, head, tail;            // snake head position and tail length
    int playerScore, textWidth;
    bool fruitEaten;
    unsigned long lastFruit = 0;
    int snakeTailX[MAX_LEN], snakeTailY[MAX_LEN];
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
          if(sDir != DOWN) sDir = UP;
        }
        else if (ty > 240) {
          if(sDir != UP) sDir = DOWN;
        }
        else if (tx < 120) {
          if(sDir != RIGHT) sDir = LEFT;
        }
        else {
          if(sDir != LEFT) sDir = RIGHT;
        }
      }

      // Move on a timer so the snake moves at a slower speed
      static unsigned long lastMove = 0;
      if (millis() - lastMove >= 195) {
        lastMove = millis();
        Move();
      }
      if(fruitEaten){
        CreateFruit();
        fruitEaten = false;
      }
    }

  private:
    void Move() {
      if (sDir == STOP) return;
      // Change direction
      if      (sDir == UP)    y -= CELL_HEIGHT;
      else if (sDir == DOWN)  y += CELL_HEIGHT;
      else if (sDir == LEFT)  x -= CELL_WIDTH;
      else if (sDir == RIGHT) x += CELL_WIDTH;

      // Wall Collision
      if (x < 0 || y < 0 || x + CELL_WIDTH > 240 || y + CELL_HEIGHT > 320) {
        GameInit();
        return;
      }

      // Fruit Collision
      if (x == fruitCordX && y == fruitCordY) EatFruit(); //!! might change to x = fruitX
      else { // If not eating erase tail
        EVA::tft.fillRect(snakeTailX[tail], snakeTailY[tail], 20, 26, TFT_BLACK);
        snakeTailX[tail] = 0;
        snakeTailY[tail] = 0;
        if(tail == MAX_LEN-1) tail = 0;
        else tail++;
      }

      EVA::tft.fillRect(x, y, 20, 26, TFT_RED); // new head
      if(head == MAX_LEN-1) head = 0;
      else head++;
      snakeTailX[head] = x;
      snakeTailY[head] = y;
    }

    void GameInit() {
      sDir = STOP;
      x = 6 * CELL_WIDTH;
      y = 6 * CELL_HEIGHT;
      fruitCordX = (rand() % 11 + 1) * CELL_WIDTH;
      fruitCordY = (rand() % 11 + 1) * CELL_HEIGHT;
      playerScore = 0;
      fruitEaten = false;
      head = 0;
      tail = 0;
      length = 1;
    
      snakeTailX[head] = x;
      snakeTailY[head] = y;
      textWidth = EVA::tft.textWidth("Score: ", 3);
      EVA::tft.fillScreen(TFT_BLACK);
      EVA::tft.fillRect(x, y, 20, 26, TFT_RED);
      EVA::tft.drawString("Score : " + (String)playerScore, SCREEN_CENTER_X - textWidth/2, y, 3);

      DrawFruit();
    }

    void EatFruit(){
      // Eat Fruit
      EVA::tft.fillCircle(fruitCordX + CELL_WIDTH / 2,
                      fruitCordY + CELL_HEIGHT / 2,
                      CELL_WIDTH / 2, TFT_BLACK);
      fruitEaten = true;
      // Increase Length
      length++;
      // Increase Score
      playerScore++;
      EVA::tft.drawString("Score : " + (String)playerScore, SCREEN_CENTER_X - textWidth/2, y, 3);
      // We don't draw a new tail on because it will move 1 space anyway, adding on a new head
    }

    void CreateFruit(){
      fruitCordX = (rand() % 11 + 1) * CELL_WIDTH;
      fruitCordY = (rand() % 11 + 1) * CELL_HEIGHT;
      DrawFruit();
    }

    void DrawFruit(){
      EVA::tft.fillCircle(fruitCordX + CELL_WIDTH / 2,
                fruitCordY + CELL_HEIGHT / 2,
                CELL_WIDTH / 2, TFT_PINK);
    }
};

#endif