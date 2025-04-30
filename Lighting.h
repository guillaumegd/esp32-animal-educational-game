// Lighting.h
#ifndef LIGHTING_H
#define LIGHTING_H

#include <Adafruit_NeoPixel.h>
#include "Animal.h"

// On déclare ici, sans construire encore
extern Adafruit_NeoPixel leds;

void setupLighting();
void updateLighting(const Animal* animal);
void resetLighting();

#endif
