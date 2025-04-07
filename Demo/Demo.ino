#include <HardwareAPI.h>

HardwareAPI api;

void setup() {
  api.begin();
}

void loop() {
  api.printLCD("Spiral", "Pattern");
  api.runSpiralPattern();
  api.printLCD("Spiral", "Pattern");
  api.runSpiralPattern('R');
  api.printLCD("Diagonal Pattern");
  api.runDiagonalPattern();
  api.printLCD("Row Sweep", "Pattern");
  api.runRowSweepPattern();
  api.printLCD("FIREWORKS", "SHOW");
  api.fireworksShow();
  delay(500);
  api.printLCD("I LOVE YOU");
  api.displayHeart('B');
  delay(5000);
  api.printLCD("Smile");
  api.displaySmiley('R');
  delay(5000);
}
