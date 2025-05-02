#include <SPI.h>
#include "Animal.h"
#include "Lighting.h"
#include "Audio.h"
#include "Screen.h"
#include "NFC.h"
#include "Game.h"

void setup() {
  Serial.begin(115200);
  setupNFC();
  setupLighting();
  setupAudio();
  setupScreen();
  setupGame();
  Serial.println("🎮 Game System ready!");
}

void loop() {
  // NFC detection update
  checkNFC();
  
  // Game logic update
  updateGame();

  // Audio queue update
  updateAudio();

  // Continuous lighting animation on the current animal
  const Animal* currentTarget = getTargetAnimal();
  if (currentTarget != nullptr) {
    updateLighting(currentTarget);
  }
  
  delay(50);
}
