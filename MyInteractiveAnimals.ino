#include <SPI.h>
#include <MFRC522.h>
#include "Animal.h"
#include "Lighting.h"
#include "Audio.h"
#include "Screen.h"

#define SS_PIN 5
#define RST_PIN 22

MFRC522 rfid(SS_PIN, RST_PIN);
const Animal* currentAnimal = nullptr;
bool tagPresent = false;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();
  setupLighting();
  setupAudio();
  setupScreen();
  Serial.println("System ready!");
}

void loop() {
  if (currentAnimal != nullptr) {
    updateLighting(currentAnimal);
  }

  if (rfid.PICC_ReadCardSerial()) {
    tagPresent = true;
    Serial.print("UID : ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();
    const Animal* a = findAnimalByUID(rfid.uid.uidByte, rfid.uid.size);
    if (a != nullptr && a != currentAnimal) {
      currentAnimal = a;
      Serial.print("🎯 Detected: ");
      Serial.println(a->name);
      playSoundForAnimal(a);
      showAnimalImage(a->imageFile);
    }
    rfid.PICC_HaltA();
  }

  if (!rfid.PICC_IsNewCardPresent() && tagPresent) {
    /* tagPresent = false;
    currentAnimal = nullptr;
    resetLighting();
    Serial.println("🔕 Tag removed"); */
  }

  delay(50);
}
