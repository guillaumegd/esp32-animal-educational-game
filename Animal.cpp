#include "Animal.h"

const Animal animals[] = {
  { { 0x04, 0x00, 0x94, 0xDB, 0x04, 0x00, 0x01 }, 7, "Whale", { { 0, 20, 200 }, { 10, 60, 255 }, { 0, 100, 180 } }, "001.mp3", "whale.bmp" },
  { { 0x04, 0x00, 0xDC, 0xDB, 0x04, 0x00, 0x01 }, 7, "Elephant", { { 255, 255, 100 }, { 100, 255, 80 }, { 200, 180, 50 } }, "002.mp3", "dog.bmp" },
  { { 0x04, 0x00, 0x4B, 0xDB, 0x04, 0x00, 0x01 }, 7, "Lion", { { 255, 160, 0 }, { 255, 220, 100 }, { 200, 100, 0 } }, "003.mp3", "lion.bmp" }
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
