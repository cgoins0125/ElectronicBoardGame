// Define the pin for the reed switch
const int reedSwitchPin1 = 53;  // Using digital pin 53 (this is interrupt-capable on most Arduino boards)
const int reedSwitchPin2 = 52;
const int reedSwitchPin3 = 51;
const int reedSwitchPin4 = 50;
const int reedSwitchPin5 = 49;
const int reedSwitchPin6= 48;
const int reedSwitchPin7 = 47;
const int reedSwitchPin8 = 46;
const int reedSwitchPin9 = 45;
const int reedSwitchPin10 = 44;
const int reedSwitchPin11 = 43;
const int reedSwitchPin12 = 42;
const int reedSwitchPin13 = 41;
const int reedSwitchPin14 = 40;
const int reedSwitchPin15 = 39;
const int reedSwitchPin16 = 38;

// Variable to store the state of the reed switch
volatile bool reedSwitchState0x00 = false;  // Volatile because it's modified in an interrupt
volatile bool reedSwitchState0x01 = false;
volatile bool reedSwitchState0x02 = false;
volatile bool reedSwitchState0x03 = false;
volatile bool reedSwitchState0x04 = false;
volatile bool reedSwitchState0x05 = false;
volatile bool reedSwitchState0x06 = false;
volatile bool reedSwitchState0x07 = false;
volatile bool reedSwitchState0x08 = false;
volatile bool reedSwitchState0x09 = false;
volatile bool reedSwitchState0x10 = false;
volatile bool reedSwitchState0x11 = false;
volatile bool reedSwitchState0x12 = false;
volatile bool reedSwitchState0x13 = false;
volatile bool reedSwitchState0x14 = false;
volatile bool reedSwitchState0x15 = false;
volatile bool reedSwitchState0x16 = false;


void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);

  // Set the reed switch pin as input
  pinMode(reedSwitchPin1, INPUT_PULLUP);
  pinMode(reedSwitchPin2, INPUT_PULLUP);
  pinMode(reedSwitchPin3, INPUT_PULLUP);
  pinMode(reedSwitchPin4, INPUT_PULLUP);
  pinMode(reedSwitchPin5, INPUT_PULLUP);
  pinMode(reedSwitchPin6, INPUT_PULLUP);
  pinMode(reedSwitchPin7, INPUT_PULLUP);
  pinMode(reedSwitchPin8, INPUT_PULLUP);
  pinMode(reedSwitchPin9, INPUT_PULLUP);
  pinMode(reedSwitchPin10, INPUT_PULLUP);
  pinMode(reedSwitchPin11, INPUT_PULLUP);
  pinMode(reedSwitchPin12, INPUT_PULLUP);
  pinMode(reedSwitchPin13, INPUT_PULLUP);
  pinMode(reedSwitchPin14, INPUT_PULLUP);
  pinMode(reedSwitchPin15, INPUT_PULLUP);
  pinMode(reedSwitchPin16, INPUT_PULLUP);

  // Attach interrupt to reed switch pin
  // Trigger on both RISING and FALLING edge (change from HIGH to LOW or LOW to HIGH)
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin1), reedSwitchInterrupt0x00, CHANGE);
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin2), reedSwitchInterrupt0x01, CHANGE);
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin3), reedSwitchInterrupt0x01, CHANGE);
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin4), reedSwitchInterrupt0x01, CHANGE);
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin5), reedSwitchInterrupt0x01, CHANGE);
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin6), reedSwitchInterrupt0x01, CHANGE);
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin7), reedSwitchInterrupt0x01, CHANGE);
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin8), reedSwitchInterrupt0x01, CHANGE);
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin9), reedSwitchInterrupt0x01, CHANGE);
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin10), reedSwitchInterrupt0x01, CHANGE);
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin11), reedSwitchInterrupt0x01, CHANGE);
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin12), reedSwitchInterrupt0x01, CHANGE);
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin13), reedSwitchInterrupt0x01, CHANGE);
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin14), reedSwitchInterrupt0x01, CHANGE);
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin15), reedSwitchInterrupt0x01, CHANGE);
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin16), reedSwitchInterrupt0x01, CHANGE);
}

void loop() {
  if (reedSwitchState0x00) {
    reedSwitchState0x00 = false;
    Serial.println("Reed 0x00 switch triggered!");
    }
  if (reedSwitchState0x01) {
    reedSwitchState0x01 = false;
    Serial.println("Reed 0x01 switch triggered!");
    }
  if (reedSwitchState0x02) {
    reedSwitchState0x02 = false;
    Serial.println("Reed 0x02 switch triggered!");
    }
  if (reedSwitchState0x03) {
    reedSwitchState0x03 = false;
    Serial.println("Reed 0x03 switch triggered!");
    }
  if (reedSwitchState0x04) {
    reedSwitchState0x04 = false;
    Serial.println("Reed 0x04 switch triggered!");
    }
  if (reedSwitchState0x05) {
    reedSwitchState0x05 = false;
    Serial.println("Reed 0x05 switch triggered!");
    }
  if (reedSwitchState0x06) {
    reedSwitchState0x06 = false;
    Serial.println("Reed 0x06 switch triggered!");
    }
  if (reedSwitchState0x07) {
    reedSwitchState0x07 = false;
    Serial.println("Reed 0x07 switch triggered!");
    }
  if (reedSwitchState0x08) {
    reedSwitchState0x08 = false;
    Serial.println("Reed 0x08 switch triggered!");
    }
  if (reedSwitchState0x09) {
    reedSwitchState0x09 = false;
    Serial.println("Reed 0x09 switch triggered!");
    }
  if (reedSwitchState0x10) {
    reedSwitchState0x10 = false;
    Serial.println("Reed 0x10 switch triggered!");
    }
  if (reedSwitchState0x11) {
    reedSwitchState0x11 = false;
    Serial.println("Reed 0x11 switch triggered!");
    }
  if (reedSwitchState0x12) {
    reedSwitchState0x12 = false;
    Serial.println("Reed 0x12 switch triggered!");
    }
  if (reedSwitchState0x13) {
    reedSwitchState0x13 = false;
    Serial.println("Reed 0x13 switch triggered!");
    }
  if (reedSwitchState0x14) {
    reedSwitchState0x14 = false;
    Serial.println("Reed 0x14 switch triggered!");
    }
  if (reedSwitchState0x15) {
    reedSwitchState0x15 = false;
    Serial.println("Reed 0x15 switch triggered!");
    }
}

// Interrupt service routine for reed switch
void reedSwitchInterrupt0x00() {
  reedSwitchState0x00 = true;
}
void reedSwitchInterrupt0x01() {
  reedSwitchState0x01 = true;
}
void reedSwitchInterrupt0x02() {
  reedSwitchState0x02 = true;
}
void reedSwitchInterrupt0x03() {
  reedSwitchState0x03 = true;
}
void reedSwitchInterrupt0x04() {
  reedSwitchState0x04 = true;
}
void reedSwitchInterrupt0x05() {
  reedSwitchState0x05 = true;
}
void reedSwitchInterrupt0x06() {
  reedSwitchState0x06 = true;
}
void reedSwitchInterrupt0x07() {
  reedSwitchState0x07 = true;
}
void reedSwitchInterrupt0x08() {
  reedSwitchState0x08 = true;
}
void reedSwitchInterrupt0x09() {
  reedSwitchState0x09 = true;
}
void reedSwitchInterrupt0x10() {
  reedSwitchState0x10 = true;
}
void reedSwitchInterrupt0x11() {
  reedSwitchState0x11 = true;
}
void reedSwitchInterrupt0x12() {
  reedSwitchState0x12 = true;
}
void reedSwitchInterrupt0x13() {
  reedSwitchState0x13 = true;
}
void reedSwitchInterrupt0x14() {
  reedSwitchState0x14 = true;
}
void reedSwitchInterrupt0x15() {
  reedSwitchState0x15 = true;
}
