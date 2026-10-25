#include <SD.h>
#include <EVA.h>
#include <EVA_app.h>
#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#define PIN_SPI_CS 5 // The ESP32 pin GPIO5

File returnFile(fs::FS &fs, const char *path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
  }
  file.close();

  return file;
}