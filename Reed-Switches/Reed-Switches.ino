// Define the pin for the reed switch
const int reedSwitchPin = 53;  // Using digital pin 53 (this is interrupt-capable on most Arduino boards)

// Variable to store the state of the reed switch
volatile bool reedSwitchState = false;  // Volatile because it's modified in an interrupt

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);

  // Set the reed switch pin as input
  pinMode(reedSwitchPin, INPUT_PULLUP);

  // Attach interrupt to reed switch pin
  // Trigger on both RISING and FALLING edge (change from HIGH to LOW or LOW to HIGH)
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin), reedSwitchInterrupt, CHANGE);
}

void loop() {
  if (reedSwitchState) {
    reedSwitchState = false;
    Serial.println("Reed switch triggered!");
    }
  }

// Interrupt service routine for reed switch
void reedSwitchInterrupt() {
  reedSwitchState = true;
}
