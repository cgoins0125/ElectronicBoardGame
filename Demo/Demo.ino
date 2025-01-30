#include <HardwareAPI.h>

const int pin = 53;
/* Variables for debouncing */
//unsigned long lastDebounceTime = 0;
//volatile bool switchState = false;
//const unsigned long debounceDelay = 10; //milliseconds
HardwareAPI api;

void setup() {
  api.begin();
  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin), ISR_00, CHANGE);
}

void loop() {
  interrupts();
  delay(5000);
  api.ClearLCD();
}

void ISR_00(){
  api.PrintLCDL1("Change detected.");
}

