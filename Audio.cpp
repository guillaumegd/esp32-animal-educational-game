#include "Audio.h"
#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define CRY_INDEX 1
#define NAME_PT_INDEX 2

HardwareSerial dfSerial(1); // UART1 (Serial1)
DFRobotDFPlayerMini dfPlayer;

void setupAudio() {
  dfSerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
  if (!dfPlayer.begin(dfSerial)) {
    Serial.println("❌ DFPlayer not detected");
    return;
  }
  dfPlayer.volume(25); // Volume 0–30
  Serial.println("🔊 DFPlayer ready");
}

void playSoundForAnimal(const Animal* animal, const int soundType) {
  if (animal && animal->soundDirNumber) {
    int directory = animal->soundDirNumber;
    if (directory > 0) {
      dfPlayer.playFolder(directory, soundType);
      Serial.print("🔈 Playing sound: ");
      Serial.println("" + String(directory) + "/" + String(soundType));
    }
  }
}

void playAnimalCry(const Animal* animal) {
  playSoundForAnimal(animal, CRY_INDEX);
}

void playAnimalName(const Animal* animal) {
  playSoundForAnimal(animal, NAME_PT_INDEX);
}

void playVictorySound() {
  // Plays file 001.mp3 at the root of the SD card
  dfPlayer.play(1); // 1 = 001.mp3 at root
  Serial.println("🔈 Playing victory sound: 001.mp3");
}

void playFailureSound() {
  // Plays file 002.mp3 at the root of the SD card
  dfPlayer.play(2); // 2 = 002.mp3 at root
  Serial.println("🔈 Playing failure sound: 002.mp3");
}

// === Sequential sound management ===
#define SOUND_QUEUE_SIZE 8
static QueuedSound soundQueue[SOUND_QUEUE_SIZE];
static int queueHead = 0;
static int queueTail = 0;
static bool isPlaying = false;
static unsigned long lastPlayTime = 0;
static unsigned long estimatedDuration = 0;

void addSoundToQueue(QueuedSoundType type, const Animal* animal) {
  int nextTail = (queueTail + 1) % SOUND_QUEUE_SIZE;
  if (nextTail != queueHead) { // Queue not full
    soundQueue[queueTail].type = type;
    soundQueue[queueTail].animal = animal;
    queueTail = nextTail;
  }
}

static void startQueuedSound(const QueuedSound& s) {
  switch (s.type) {
    case SOUND_VICTORY:
      playVictorySound();
      estimatedDuration = 2000; // ms, adjust to real duration
      break;
    case SOUND_FAILURE:
      playFailureSound();
      estimatedDuration = 3000;
      break;
    case SOUND_ANIMAL_NAME:
      playAnimalName(s.animal);
      estimatedDuration = 1500;
      break;
    case SOUND_ANIMAL_CRY:
      playAnimalCry(s.animal);
      estimatedDuration = 3000;
      break;
    case SOUND_INTRO:
      dfPlayer.play(3); // 3 = 003.mp3 at root
      Serial.println("🎵 Playing intro music: 003.mp3");
      estimatedDuration = 3500; // Adjust to real duration
      break;
  }
  lastPlayTime = millis();
  isPlaying = true;
}

void updateAudio() {
  if (isPlaying) {
    if (millis() - lastPlayTime > estimatedDuration) {
      isPlaying = false;
    }
  }
  if (!isPlaying && queueHead != queueTail) {
    startQueuedSound(soundQueue[queueHead]);
    queueHead = (queueHead + 1) % SOUND_QUEUE_SIZE;
  }
}


