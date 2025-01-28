#include <HardwareAPI.h>

HardwareAPI api;

void setup() {
  api.begin();
}

void loop() {
  api.PrintLCD("Current: Green", "Next: Red");
  api.turnOnLED(0x00, 'G');
  delay(5000);
  api.PrintLCD("Current: Red", "Next: Blue");
  api.changeLEDcolor(0x00, 'R');
  delay(5000);
  api.PrintLCD("Current: Blue", "Next: Green");
  api.changeLEDcolor(0x00, 'B');
  delay(5000);
  api.PrintLCD("Current: Green", "Next: Yellow");
  api.changeLEDcolor(0x00, 'G');
  delay(5000);
  api.PrintLCD("Current: Yellow", "Next: LEDs Off");
  api.changeLEDcolor(0x00, 'Y');
  delay(5000);
  api.PrintLCD("Leds off", "Next: Green");
  api.turnOffLED(0x00);
  delay(5000);
}
