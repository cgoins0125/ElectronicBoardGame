#include <HardwareAPI.h>

HardwareAPI api;

void setup() {
  api.begin();
}

void loop() {
  // Turn on LEDs to Green for row 1 and row 2
  api.PrintLCD("Current: Green", "Next: Red");
  for (uint8_t tile = 0x00; tile <= 0x07; tile++) {
    api.turnOnLED(tile, 'G');
  }
  for (uint8_t tile = 0x10; tile <= 0x17; tile++) {
    api.turnOnLED(tile, 'G');
  }
  delay(5000);

  // Change color to Red for both rows
  api.PrintLCD("Current: Red", "Next: Blue");
  for (uint8_t tile = 0x00; tile <= 0x07; tile++) {
    api.changeLEDcolor(tile, 'R');
  }
  for (uint8_t tile = 0x10; tile <= 0x17; tile++) {
    api.changeLEDcolor(tile, 'R');
  }
  delay(5000);

  // Change color to Blue for both rows
  api.PrintLCD("Current: Blue", "Next: Green");
  for (uint8_t tile = 0x00; tile <= 0x07; tile++) {
    api.changeLEDcolor(tile, 'B');
  }
  for (uint8_t tile = 0x10; tile <= 0x17; tile++) {
    api.changeLEDcolor(tile, 'B');
  }
  delay(5000);

  // Change color to Green for both rows
  api.PrintLCD("Current: Green", "Next: Yellow");
  for (uint8_t tile = 0x00; tile <= 0x07; tile++) {
    api.changeLEDcolor(tile, 'G');
  }
  for (uint8_t tile = 0x10; tile <= 0x17; tile++) {
    api.changeLEDcolor(tile, 'G');
  }
  delay(5000);

  // Change color to Yellow for both rows
  api.PrintLCD("Current: Yellow", "Next: LEDs Off");
  for (uint8_t tile = 0x00; tile <= 0x07; tile++) {
    api.changeLEDcolor(tile, 'Y');
  }
  for (uint8_t tile = 0x10; tile <= 0x17; tile++) {
    api.changeLEDcolor(tile, 'Y');
  }
  delay(5000);

  // Turn off all LEDs for both rows
  api.PrintLCD("Leds off", "Next: Green");
  for (uint8_t tile = 0x00; tile <= 0x07; tile++) {
    api.turnOffLED(tile);
  }
  for (uint8_t tile = 0x10; tile <= 0x17; tile++) {
    api.turnOffLED(tile);
  }
  delay(5000);
}
