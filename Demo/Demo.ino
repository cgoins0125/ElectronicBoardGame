#include <HardwareAPI.h>

void setup() {
  HardwareAPI::begin();
}

void loop() {
  HardwareAPI::PrintLCD("Current Color: Green", "Next Color: Red");
  HardwareAPI::turnOnLED(0x00, 'G');
  delay(50000);
  HardwareAPI::PrintLCD("Current Color: Red", "Next Color: Blue");
  HardwareAPI::changeLEDcolor(0x00, 'R');
  delay(5000);
  HardwareAPI::PrintLCD("Current Color: Blue", "Next Color: Green");
  HardwareAPI::changeLEDcolor(0x00, 'B');
  delay(5000);
  HardwareAPI::PrintLCD("Current Color: Green", "Next Color: Yellow");
  HardwareAPI::changeLEDcolor(0x00, 'G');
  delay(5000);
  HardwareAPI::PrintLCD("Current Color: Yellow", "Next: LEDs Off");
  HardwareAPI::changeLEDcolor(0x00, 'Y');
  delay(5000);
  HardwareAPI::PrintLCD("Leds off", "Next Color: Green");
  HardwareAPI::turnOffLED(0x00);
  delay(5000);
}
