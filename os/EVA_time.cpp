#include <EVA_time.h>

bool EVA::Time::pumpVSynced() {
  time_point now = high_resolution_clock::now();

  timeSinceLastSecond = duration<double>(now - lastSecondTime).count();
  if (timeSinceLastSecond > 1) {
    fps = frameCount;
    frameCount = 0;
    lastSecondTime = now;
  }

  timeSinceLastFrame = duration<double>(now - lastFrameTime).count();
  if (timeSinceLastFrame > vSyncTime) {
    deltaTime = duration<double>(now - lastFrameTime).count();

    seconds += deltaTime;

    lastFrameTime = now;
    frameCount++;

    return true;
  } 

  return false;
} 