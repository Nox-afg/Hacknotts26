#ifndef _menu
#define _menu

#include <EVA.h>
#include <EVA_time.h>
#include <EVA_app.h>
#include <EVA_math.h>

using namespace EVA;

class MenuApp : public EVA::App {
public:
  #define AIS 60 //App icon size
  #define AIB 15 //App icon border radius
  Box snakeAppTileBox = Box(80 - AIS/2, 16+82 - AIS/2, AIS, AIS);
  Box sketchAppTileBox = Box(160 - AIS/2, 16+82 - AIS/2, AIS, AIS);
  Box musicAppTileBox = Box(80 - AIS/2, 16+82*2 - AIS/2, AIS, AIS);

  // EVA::tft.drawRoundRect(160 - ais/2, 16+82 - ais/2, ais, ais, aib, TFT_MAGENTA);
  //   EVA::tft.drawRoundRect(80 - ais/2, 16+82*2 - ais/2, ais, ais, aib, TFT_MAGENTA);
  //   EVA::tft.drawRoundRect(160 - ais/2, 16+82*2 - ais/2, ais, ais, aib, TFT_MAGENTA);
  //   EVA::tft.drawRoundRect(80 - ais/2, 16+82*3 - ais/2, ais, ais, aib, TFT_MAGENTA);
  //   EVA::tft.drawRoundRect(160 - ais/2, 16+82*3 - ais/2, ais, ais, aib, TFT_MAGENTA);

  MenuApp() : EVA::App("Menu", false) {
    EVA::tfte.fillRectGradient(Box(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT), 0xfe1b, 0xfbf7, 0, 0);

    Box topBar = Box(0, 0, SCREEN_WIDTH, 32);

    EVA::tft.fillRect(boxDecompose(topBar), TFT_LIGHTGREY);
    EVA::tft.drawRect(boxDecompose(topBar), TFT_DARKGREY);

    EVA::tft.fillRoundRect(boxDecompose(snakeAppTileBox), AIB, 0xe190);
    EVA::tft.setTextColor(TFT_WHITE);
    EVA::tft.drawCentreString("Snake", snakeAppTileBox.centerX(), snakeAppTileBox.centerY() - 7, 2);

    EVA::tft.fillRoundRect(boxDecompose(sketchAppTileBox), AIB, 0xe190);
    EVA::tft.setTextColor(TFT_WHITE);
    EVA::tft.drawCentreString("Sketch", sketchAppTileBox.centerX(), sketchAppTileBox.centerY() - 7, 2);

    EVA::tft.fillRoundRect(boxDecompose(musicAppTileBox), AIB, 0xe190);
    EVA::tft.setTextColor(TFT_WHITE);
    EVA::tft.drawCentreString("Music", musicAppTileBox.centerX(), musicAppTileBox.centerY() - 7, 2);

    // EVA::Time::setVSync(true, 1);
    // Box menuBox = EVA::tfte.drawStringWithBar("Menu", 0, 4, 10);

    // int yOffset = menuBox.h+10;

    // for (int i = 0; i < EVA::App::appNames.size(); i++) {
    //   appBoxes.push_back(EVA::tfte.drawStringWithBar(EVA::App::appNames[i], yOffset, 4, 0));

    //   yOffset += appBoxes.back().h+10;
    // }
  }

  ~MenuApp() override {
    EVA::Time::setVSync(true, 60);
  }

  void loop() override {
    auto now = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
    const char* clock = std::format("{:%H:%M:%S}", now).c_str();

    EVA::tft.setTextColor(TFT_BLACK, TFT_LIGHTGREY);
    EVA::tft.drawCentreString(clock, SCREEN_CENTER_X, 4, 4);

    if (EVA::touchInBox(snakeAppTileBox)) switchToApp = "Snake App";
    else if (EVA::touchInBox(sketchAppTileBox)) switchToApp = "Sketch";
    else if (EVA::touchInBox(musicAppTileBox)) switchToApp = "Music";
  }
private:
  std::vector<Box> appBoxes;
};

#endif