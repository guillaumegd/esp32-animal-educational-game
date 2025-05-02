#ifndef AUDIO_H
#define AUDIO_H

#include "Animal.h"

void setupAudio();
void playSoundForAnimal(const Animal* animal, const int soundType);
void playAnimalCry(const Animal* animal);
void playAnimalName(const Animal* animal);
void playVictorySound();
void playFailureSound();

// Sequential sound management

enum QueuedSoundType {
  SOUND_VICTORY,
  SOUND_FAILURE,
  SOUND_ANIMAL_NAME,
  SOUND_ANIMAL_CRY,
  SOUND_INTRO
};

struct QueuedSound {
  QueuedSoundType type;
  const Animal* animal; // Can be nullptr for victory/failure/intro
};

void addSoundToQueue(QueuedSoundType type, const Animal* animal = nullptr);
void updateAudio();

#endif