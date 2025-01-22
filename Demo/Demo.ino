#include <HardwareAPI.h>

HardwareAPI api;

void setup() {
  api.begin();
}

void loop() {
  api.PrintLCD("Current Color: Green", "Next Color: Red");
  api.turnOnLED(0x00, 'G');
  delay(5000);
  api.PrintLCD("Current Color: Red", "Next Color: Blue");
  api.changeLEDcolor(0x00, 'R');
  delay(5000);
  api.PrintLCD("Current Color: Blue", "Next Color: Green");
  api.changeLEDcolor(0x00, 'B');
  delay(5000);
  api.PrintLCD("Current Color: Green", "Next Color: Yellow");
  api.changeLEDcolor(0x00, 'G');
  delay(5000);
  api.PrintLCD("Current Color: Yellow", "Next: LEDs Off");
  api.changeLEDcolor(0x00, 'Y');
  delay(5000);
  api.PrintLCD("Leds off", "Next Color: Green");
  api.turnOffLED(0x00);
  delay(5000);
}
