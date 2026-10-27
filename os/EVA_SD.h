#ifndef _eva_sd
#define _eva_sd


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

void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.path(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

File returnFile(fs::FS &fs, const char *path) {
  Serial.printf("Reading file: %s\n", path);
  // if (!SD.begin(PIN_SPI_CS)) {
  //    Serial.println("SD mount failed");
  //  }

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
  }

  return file;
}

#endif