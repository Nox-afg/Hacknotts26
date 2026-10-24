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

        #define SCREEN_WIDTH 320
        #define SCREEN_HEIGHT 240

        TFT_eSPI tft = TFT_eSPI(); // create tft instance

        SPIClass touchscreenSPI = SPIClass(VSPI);  // Set up touch screen
        XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

        // Game details
        int fruitCordX, fruitCordY;
        int snakeTailX[100], snakeTailY[100];
        enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

        GameInit();

      }

      // ~snakeApp() override {}

      void loop() override {
        if (touchscreen.tirqTouched() && touchscreen.touched()) {
          TF_Point p = touchscreen.getPoint();
          x = map(p.x, 200, 3700, 1, SCREEN_WIDTH)  
          y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT)  

          // Calculate where in the screen

          if(y > 240 || y < 80){
            if(x < 120){
              moveLeft();
            }
            else{
              moveRight();
            }
          }
          else if(y < 80){
            moveDown();
          }
          else{
            moveUp();
          }

        }
      
      }
  private:
      void moveLeft(){}
      void moveRight(){}
      void moveUp(){}
      void moveDown(){}

      void GameInit()
      {
          Serial.begin(9600)
          tft.reset()
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