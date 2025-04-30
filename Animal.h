#ifndef ANIMAL_H
#define ANIMAL_H

#include <Arduino.h>

struct ColorRGB {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};


struct Animal {
  byte uid[7];
  byte uidLength;
  const char* name;
  ColorRGB palette[3];  // Up to 3 colors
  const char* soundFileName;
  const char* soundFileCry;
  const char* imageFile;
};

extern const Animal animals[];
extern const int animalCount;

bool compareUID(byte* a, byte* b, byte length);
const Animal* findAnimalByUID(byte* uid, byte length);

#endif