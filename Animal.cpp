#include "Animal.h"

const Animal animals[] = {
  { { 0x04, 0x00, 0x94, 0xDB, 0x04, 0x00, 0x01 }, 7, "Whale", { { 0, 20, 200 }, { 10, 60, 255 }, { 0, 100, 180 } }, 1, "whale.bmp" },
  { { 0x04, 0x00, 0xDC, 0xDB, 0x04, 0x00, 0x01 }, 7, "Horse", { { 100, 180, 80 }, { 160, 220, 120 }, { 70, 130, 60 } }, 2, "horse.bmp" },
  { { 0x04, 0x00, 0x4B, 0xDB, 0x04, 0x00, 0x01 }, 7, "Lion", { { 255, 160, 0 }, { 255, 220, 100 }, { 200, 100, 0 } }, 3, "lion.bmp" },
  { { 0xFF, 0x0F, 0xE9, 0xB8, 0x36, 0x00, 0x00 }, 7, "Dog", { { 240, 210, 170 }, { 200, 180, 130 }, { 150, 130, 100 } }, 4, "dog.bmp" },
};

const int animalCount = sizeof(animals) / sizeof(Animal);

bool compareUID(const byte* a, const byte* b, byte length) {
  for (byte i = 0; i < length; i++) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

const Animal* findAnimalByUID(byte* uid, byte length) {
  for (int i = 0; i < animalCount; i++) {
    if (animals[i].uidLength == length && compareUID(uid, animals[i].uid, length)) {
      return &animals[i];
    }
  }
  return nullptr;
}
