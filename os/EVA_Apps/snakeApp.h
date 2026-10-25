// #ifndef _SnakeApp
// #define _SnakeApp

// #include <EVA.h>
// #include <EVA_app.h>
// #include <EVA_SD.h>
// #include <SPI.h>
// #include <TFT_eSPI.h>
// #include <XPT2046_Touchscreen.h>

// class SnakeApp : public EVA::App {
//   public:
//     enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };


//     // Game state
//     static const int cols = 12, rows = 12;
//     static const int CELL_WIDTH = 20, CELL_HEIGHT = 26;
//     static const int MAX_LEN = cols * rows;
//     int fruitCordX, fruitCordY;
//     int x, y, length, head, tail;            // snake head position and tail length
//     int playerScore, textWidth;
//     bool fruitEaten;
//     File bgFile = returnFile(SD, "/bgMap.bin");
//     uint16_t rowBuf[240];
//     unsigned long lastFruit = 0;
//     int snakeTailX[MAX_LEN], snakeTailY[MAX_LEN];
//     snakesDirection sDir;

//     SnakeApp() : EVA::App("Snake App") {
//       GameInit();
//     }

//     ~SnakeApp() override {}

//     void loop() override {
//       if (EVA::touched) {
//         int tx = EVA::touchpoint.x;
//         int ty = EVA::touchpoint.y;

//         // Top band = UP, bottom band = DOWN, middle band = LEFT/RIGHT
//         if (ty < 80) {
//           if(sDir != DOWN) sDir = UP;
//         }
//         else if (ty > 240) {
//           if(sDir != UP) sDir = DOWN;
//         }
//         else if (tx < 120) {
//           if(sDir != RIGHT) sDir = LEFT;
//         }
//         else {
//           if(sDir != LEFT) sDir = RIGHT;
//         }
//       }

//       // Move on a timer so the snake moves at a slower speed
//       static unsigned long lastMove = 0;
//       if (millis() - lastMove >= 180) {
//         lastMove = millis();
//         Move();
//       }
//       if(fruitEaten){
//         CreateFruit();
//         fruitEaten = false;
//       }
//     }

//   private:
//     void Move() {
//       if (sDir == STOP) return;
//       // Change direction
//       if      (sDir == UP)    y -= CELL_HEIGHT;
//       else if (sDir == DOWN)  y += CELL_HEIGHT;
//       else if (sDir == LEFT)  x -= CELL_WIDTH;
//       else if (sDir == RIGHT) x += CELL_WIDTH;

//       // Wall Collision
//       if (x < 0 || y < 0 || x + CELL_WIDTH > 240 || y + CELL_HEIGHT > 320) {
//         GameInit();
//         return;
//       }

//       // Fruit Collision
//       if (x == fruitCordX && y == fruitCordY) EatFruit(); //!! might change to x = fruitX
//       else { // If not eating erase tail
//         // EVA::tft.fillRect(snakeTailX[tail], snakeTailY[tail], 20, 26, TFT_BLACK);
//         RestoreBackground(snakeTailX[tail], snakeTailY[tail], CELL_WIDTH, CELL_HEIGHT);
//         snakeTailX[tail] = 0;
//         snakeTailY[tail] = 0;
//         if(tail == MAX_LEN-1) tail = 0;
//         else tail++;
//       }

//       EVA::tft.fillRect(x, y, 20, 26, TFT_RED); // new head
//       if(head == MAX_LEN-1) head = 0;
//       else head++;
//       snakeTailX[head] = x;
//       snakeTailY[head] = y;
//     }

//     void GameInit() {
//       sDir = STOP;
//       x = 6 * CELL_WIDTH;
//       y = 6 * CELL_HEIGHT;
//       fruitCordX = (rand() % 11 + 1) * CELL_WIDTH;
//       fruitCordY = (rand() % 11 + 1) * CELL_HEIGHT;
//       playerScore = 0;
//       fruitEaten = false;
//       head = 0;
//       tail = 0;
//       length = 1;
    
//       DrawBackground();

//       snakeTailX[head] = x;
//       snakeTailY[head] = y;
//       textWidth = EVA::tft.textWidth("Score: ", 3);
//       // EVA::tft.fillScreen(TFT_BLACK);
//       EVA::tft.fillRect(x, y, 20, 26, TFT_RED);
//       EVA::tft.drawString("Score : " + (String)playerScore, SCREEN_CENTER_X - textWidth/2, y, 3);

//       DrawFruit();
//     }

//     void EatFruit(){
//       // Eat Fruit
//       // EVA::tft.fillCircle(fruitCordX + CELL_WIDTH / 2,
//       //                 fruitCordY + CELL_HEIGHT / 2,
//       //                 CELL_WIDTH / 2, TFT_BLACK);
//       RestoreBackground(fruitCordX, fruitCordY, CELL_WIDTH, CELL_HEIGHT);
//       fruitEaten = true;
//       // Increase Length
//       length++;
//       // Increase Score
//       playerScore++;
//       EVA::tft.drawString("Score : " + (String)playerScore, SCREEN_CENTER_X - textWidth/2, y, 3);
//       // We don't draw a new tail on because it will move 1 space anyway, adding on a new head
//     }

//     void CreateFruit(){
//       fruitCordX = (rand() % 11 + 1) * CELL_WIDTH;
//       fruitCordY = (rand() % 11 + 1) * CELL_HEIGHT;
//       DrawFruit();
//     }

//     void DrawFruit(){
//       EVA::tft.fillCircle(fruitCordX + CELL_WIDTH / 2,
//                 fruitCordY + CELL_HEIGHT / 2,
//                 CELL_WIDTH / 2, TFT_PINK);
//     }

//     void DrawBackground() {
//       RestoreBackground(0, 0, 240, 320);   
//     }

//     void RestoreBackground(int cx, int cy, int w, int h) {
//     for (int row = 0; row < h; row++) {
//       bgFile.seek(((uint32_t)(cy + row) * 240 + cx) * 2);
//       bgFile.read((uint8_t*)rowBuf, w * 2);
//       EVA::tft.pushImage(cx, cy + row, w, 1, rowBuf);
//     }
// }
// };

// #endif

#ifndef _SnakeApp
#define _SnakeApp

#include <EVA.h>
#include <EVA_app.h>
#include <EVA_SD.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

class SnakeApp : public EVA::App {
  public:
    enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

    static const int cols = 12, rows = 12;
    static const int CELL_WIDTH = 20, CELL_HEIGHT = 26;
    static const int MAX_LEN = cols * rows;
    int fruitCordX, fruitCordY;
    int x, y, length, head, tail;
    int playerScore, textWidth;
    bool fruitEaten;
    File bgFile;                                  // CHANGED: no initializer
    uint16_t rowBuf[240];
    uint16_t cellBuf[CELL_WIDTH * CELL_HEIGHT];   // NEW
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
        Serial.printf("tx=%d ty=%d\n", tx, ty);   // NEW: temporary debug

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

      static unsigned long lastMove = 0;
      if (millis() - lastMove >= 180) {
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
      if      (sDir == UP)    y -= CELL_HEIGHT;
      else if (sDir == DOWN)  y += CELL_HEIGHT;
      else if (sDir == LEFT)  x -= CELL_WIDTH;
      else if (sDir == RIGHT) x += CELL_WIDTH;

      if (x < 0 || y < 0 || x + CELL_WIDTH > 240 || y + CELL_HEIGHT > 320) {
        GameInit();
        return;
      }

      if (x == fruitCordX && y == fruitCordY) EatFruit();
      else {
        RestoreCell(snakeTailX[tail], snakeTailY[tail]);   // CHANGED
        snakeTailX[tail] = 0;
        snakeTailY[tail] = 0;
        if(tail == MAX_LEN-1) tail = 0;
        else tail++;
      }

      EVA::tft.fillRect(x, y, 20, 26, TFT_RED);
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

      DrawBackground();

      snakeTailX[head] = x;
      snakeTailY[head] = y;
      textWidth = EVA::tft.textWidth("Score: ", 3);
      EVA::tft.fillRect(x, y, 20, 26, TFT_RED);
      EVA::tft.drawString("Score : " + (String)playerScore, SCREEN_CENTER_X - textWidth/2, y, 3);

      DrawFruit();
    }

    void EatFruit(){
      RestoreCell(fruitCordX, fruitCordY);                 // CHANGED
      fruitEaten = true;
      length++;
      playerScore++;
      EVA::tft.drawString("Score : " + (String)playerScore, SCREEN_CENTER_X - textWidth/2, y, 3);
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

    // NEW: opens the file the first time it's needed
    bool OpenBg() {
      if (!bgFile) bgFile = returnFile(SD, "/bgMap.bin");
      return (bool)bgFile;
    }

    // CHANGED: full screen, row by row, releasing the TFT before each SD read
    void DrawBackground() {
      if (!OpenBg()) { EVA::tft.fillScreen(TFT_BLACK); return; }
      EVA::tft.setSwapBytes(true);
      for (int row = 0; row < 320; row++) {
        EVA::tft.endWrite();
        bgFile.seek((uint32_t)row * 240 * 2);
        bgFile.read((uint8_t*)rowBuf, 240 * 2);
        EVA::tft.pushImage(0, row, 240, 1, rowBuf);
      }
    }

    // NEW: replaces RestoreBackground() for single cells
    void RestoreCell(int cx, int cy) {
      if (!OpenBg()) { EVA::tft.fillRect(cx, cy, CELL_WIDTH, CELL_HEIGHT, TFT_BLACK); return; }
      EVA::tft.endWrite();                       // release TFT bus
      for (int row = 0; row < CELL_HEIGHT; row++) {
        bgFile.seek(((uint32_t)(cy + row) * 240 + cx) * 2);
        bgFile.read((uint8_t*)&cellBuf[row * CELL_WIDTH], CELL_WIDTH * 2);
      }
      EVA::tft.setSwapBytes(true);
      EVA::tft.pushImage(cx, cy, CELL_WIDTH, CELL_HEIGHT, cellBuf);
    }
};

#endif