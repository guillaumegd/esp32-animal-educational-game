// Lighting.h
#ifndef LIGHTING_H
#define LIGHTING_H

#include <Adafruit_NeoPixel.h>
#include "Animal.h"

// Declare here, but not constructed yet
extern Adafruit_NeoPixel leds;

void setupLighting();
void updateLighting(const Animal* animal);
void resetLighting();

#endif
