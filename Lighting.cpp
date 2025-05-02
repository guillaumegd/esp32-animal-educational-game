#include "Lighting.h"

#define LED_PIN 4
#define LED_COUNT 64
Adafruit_NeoPixel leds(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int brightness = 5;
int direction = 1;
unsigned long lastColorUpdate = 0;
unsigned long lastBrightnessUpdate = 0;

void setupLighting() {
  leds.begin();
  leds.setBrightness(20);
  leds.clear();
  leds.show();
}

void updateLighting(const Animal* animal) {
  unsigned long now = millis();

  if (now - lastColorUpdate >= 200) {
    for (int i = 0; i < LED_COUNT; i++) {
      int index = random(0, 3);
      ColorRGB c = animal->palette[index];
      leds.setPixelColor(i, leds.Color(c.r, c.g, c.b));
    }
    leds.show();
    lastColorUpdate = now;
  }

  if (now - lastBrightnessUpdate >= 100) {
    brightness += direction;
    if (brightness >= 50) {
      brightness = 50;
      direction = -1;
    } else if (brightness <= 5) {
      brightness = 5;
      direction = 1;
    }
    leds.setBrightness(brightness);
    leds.show();
    lastBrightnessUpdate = now;
  }
}

void resetLighting() {
  leds.clear();
  leds.show();
}
