#include "NFC.h"
#include "Lighting.h"
#include "Audio.h"
#include "Screen.h"
#include <SPI.h>

#define SS_PIN 5
#define RST_PIN 22

MFRC522 rfid(SS_PIN, RST_PIN);
static const Animal* currentAnimal = nullptr;
static bool tagPresent = false;

void setupNFC() {
  SPI.begin();
  rfid.PCD_Init();
}

void checkNFC() {
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
      playAnimalName(a);
      // showAnimalImage(a->imageFile);
    }
    rfid.PICC_HaltA();
  }

  if (!rfid.PICC_IsNewCardPresent() && tagPresent) {
    /* tagPresent = false;
    currentAnimal = nullptr;
    resetLighting();
    Serial.println("🔕 Tag removed"); */
  }
}

const Animal* getCurrentAnimal() {
  return currentAnimal;
}

bool isTagPresent() {
  return tagPresent;
}

void resetCurrentAnimal() {
  currentAnimal = nullptr;
}
