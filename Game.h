#ifndef GAME_H
#define GAME_H

#include "Animal.h"

// États du jeu
enum GameState {
  SELECTING_ANIMAL,
  WAITING_FOR_DETECTION,
  ANIMAL_DETECTED,
  RESET_DELAY
};

// Fonctions de gestion du jeu
void setupGame();
void updateGame();
void selectRandomAnimal();
const Animal* getTargetAnimal();
GameState getCurrentGameState();

#endif // GAME_H
