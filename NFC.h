#ifndef NFC_H
#define NFC_H

#include <MFRC522.h>
#include "Animal.h"

void setupNFC();
void checkNFC();
const Animal* getCurrentAnimal();
bool isTagPresent();
void resetCurrentAnimal();

#endif // NFC_H
