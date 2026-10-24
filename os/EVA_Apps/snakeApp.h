#ifndef _snakeApp
#define _snakeApp

#include <EVA.h>
#include <EVA_app.h>

#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

class snakeApp : public EVA::App {
  public:
      snakeApp() : EVA::App("Test App") {
        EVA::tft.drawCentreString("I am a snake app", SCREEN_CENTER_X, SCREEN_CENTER_Y, 2);


        // Game details
        int fruitCordX, fruitCordY;
        int snakeTailX[100], snakeTailY[100];
        enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

        GameInit();

      }

      ~snakeApp() override {}

      void loop() override {
        if (EVA::touched) {
          x = EVA::touchpoint.x
          y = EVA::touchpoint.y 

          // Calculate where in the screen

          if(y > 240 || y < 80){
            if(x < 120){
              sDir = LEFT;
            }
            else{
              sDir = RIGHT;
            }
          }
          else if(y < 80){
            sDir = DOWN;
          }
          else{
            sDir = UP;
          }

        }
      
      }
  private:
      void move(){
         if(sDir == UP && y <= 294){
            y = y + 26;
         }
         else if(sDir == DOWN && y >= 26){
            y = y - 26;
         }
         else if(sDir == LEFT && x >= 20){
            x = x - 20;
         }
         else if(sDir == RIGHT && x <= 220){
            x = x + 20;
         }
         // redraw shape
      }

      void GameInit()
      {
          isGameOver = false;
          sDir = STOP;
          x = SCREEN_WIDTH / 2;
          y = SCREEN_HEIGHT / 2;
          fruitCordX = rand() % SCREEN_WIDTH;
          fruitCordY = rand() % SCREEN_HEIGHT;
          playerScore = 0;

          tft.fillRect(x,y,20,26, TFT_RED)
      }
};

#endif