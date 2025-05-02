#include "Game.h"
#include "Audio.h"
#include "NFC.h"
#include <Arduino.h>
#include "Lighting.h"

// Game state variables
static GameState currentState = SELECTING_ANIMAL;
static const Animal* targetAnimal = nullptr;
static const Animal* previousAnimal = nullptr;
static unsigned long stateTimer = 0;
static const unsigned long RESET_DELAY_MS = 2000; // 2 seconds before changing animal

void setupGame() {
  // Initialize the random number generator with multiple entropy sources
  randomSeed(analogRead(0) + millis());
  
  // Start immediately with a new animal
  selectRandomAnimal();
}

void updateGame() {
  const Animal* detectedAnimal = getCurrentAnimal();
  bool isAnimalPresent = isTagPresent(); // Checks if a tag is present
  unsigned long currentTime = millis();
  
  switch(currentState) {
    case SELECTING_ANIMAL:
      // Select a random animal and play its name
      selectRandomAnimal();
      resetCurrentAnimal(); // Reset NFC detection to avoid immediate failure
      if (targetAnimal != nullptr) {
        addSoundToQueue(SOUND_INTRO); // Start-of-round music
        addSoundToQueue(SOUND_ANIMAL_NAME, targetAnimal);
        updateLighting(targetAnimal); // Trigger lighting ambiance on selection
        currentState = WAITING_FOR_DETECTION;
        Serial.print("🎮 Find the animal: ");
        Serial.println(targetAnimal->name);
      }
      break;
      
    case WAITING_FOR_DETECTION:
      // Wait for the correct animal to be detected
      if (detectedAnimal != nullptr && isAnimalPresent) {
        if (detectedAnimal == targetAnimal) {
          // Correct animal detected
          addSoundToQueue(SOUND_VICTORY);
          addSoundToQueue(SOUND_ANIMAL_NAME, targetAnimal);
          addSoundToQueue(SOUND_ANIMAL_CRY, targetAnimal);
          currentState = ANIMAL_DETECTED;
          stateTimer = currentTime;
          Serial.println("🎯 Well done! Correct animal!");
        } else {
          // Wrong animal detected - only display once per detection
          static const Animal* lastWrongAnimal = nullptr;
          if (detectedAnimal != lastWrongAnimal) {
            Serial.println("❌ Wrong animal, try again...");
            addSoundToQueue(SOUND_FAILURE);
            addSoundToQueue(SOUND_ANIMAL_NAME, targetAnimal); // Replay the animal name to find
            lastWrongAnimal = detectedAnimal;
          }
        }
      } else {
        // Reset lastWrongAnimal when no animal is detected
        static const Animal* lastWrongAnimal = nullptr;
        lastWrongAnimal = nullptr;
      }
      break;
    case ANIMAL_DETECTED:
      // Stay in this state for a while to allow animation/sound
      if (currentTime - stateTimer >= 3000) { // 3 seconds of celebration
        currentState = RESET_DELAY;
        stateTimer = currentTime;
      }
      break;
      
    case RESET_DELAY:
      // Wait RESET_DELAY_MS before choosing a new animal
      if (currentTime - stateTimer >= RESET_DELAY_MS) {
        currentState = SELECTING_ANIMAL;
      }
      break;
  }
}

void selectRandomAnimal() {
  if (animalCount > 0) {
    // Keep the previous animal before choosing a new one
    previousAnimal = targetAnimal;
    
    // Choose a new animal different from the previous one
    int randomIndex;
    const Animal* newAnimal;
    
    // If more than one animal, ensure not to repeat the same
    if (animalCount > 1) {
      do {
        randomIndex = random(animalCount);
        newAnimal = &animals[randomIndex];
      } while (newAnimal == previousAnimal);
    } else {
      // If only one animal, no choice
      randomIndex = 0;
      newAnimal = &animals[randomIndex];
    }
    
    targetAnimal = newAnimal;
  }
}

const Animal* getTargetAnimal() {
  return targetAnimal;
}

GameState getCurrentGameState() {
  return currentState;
}
