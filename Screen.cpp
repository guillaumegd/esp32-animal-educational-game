#include "screen.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ImageReader.h>
#include <SdFat.h>

// === CONFIGURATION DES PINS ===
#define TFT_CS    15
#define TFT_DC    2
#define TFT_RST   27
#define SD_CS     13  // ou autre, selon ton module SD

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
SdFat SD;
Adafruit_ImageReader reader(SD);
Adafruit_Image img;

void setupScreen() {
  tft.initR(INITR_BLACKTAB);  // ou REDTAB selon ton écran
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);

  if (!SD.begin(SD_CS)) {
    Serial.println("❌ SD card init failed");
    return;
  }

  Serial.println("✅ Screen ready");

  showAnimalImage("/lion.bmp");
}

void showAnimalImage(const char* filename) {
  ImageReturnCode stat = reader.drawBMP(filename, tft, 0, 0);
  if (stat != IMAGE_SUCCESS) {
    Serial.print("❌ Error displaying image ");
    Serial.println(filename);
    reader.printStatus(stat);
  } else {
    Serial.print("🖼️ Image displayed: ");
    Serial.println(filename);
  }
}
