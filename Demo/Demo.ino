#include <HardwareAPI.h>

HardwareAPI api;

void setup() {
  api.begin();
}

void loop() {
  api.printLCD("Spiral", "Pattern In Green");
  api.runSpiralPattern('G');
  api.printLCD("Diagonal Pattern", "In Yellow");
  api.runDiagonalPattern('Y');
  api.printLCD("Row Sweep", "Pattern In Blue");
  api.runRowSweepPattern('B');
}
