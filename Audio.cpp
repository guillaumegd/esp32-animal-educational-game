#include "Audio.h"
#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>

HardwareSerial dfSerial(1); // UART1 (Serial1)
DFRobotDFPlayerMini dfPlayer;

void setupAudio() {
  dfSerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
  if (!dfPlayer.begin(dfSerial)) {
    Serial.println("❌ DFPlayer not detected");
    return;
  }
  dfPlayer.volume(20); // Volume 0–30
  Serial.println("🔊 DFPlayer ready");
}

void playSoundForAnimal(const Animal* animal) {
  if (animal && animal->soundFile) {
    int fileNumber = atoi(animal->soundFile);
    if (fileNumber > 0) {
      dfPlayer.play(fileNumber);
      Serial.print("🔈 Playing sound: ");
      Serial.println(animal->soundFile);
    }
  }
}
