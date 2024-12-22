#define PWM_Pin PA8  // Set the pin for PWM output

void setup() {
    pinMode(PWM_Pin, PWM);  // Configure pin for PWM

    // Set PWM frequency
    analogWriteFrequency(PWM_Pin, 20000);  // Set to 20 kHz

    // Set duty cycle (0–255 range)
    analogWrite(PWM_Pin, 64);  // 25% duty cycle
}

void loop() {
    for (int duty = 64; duty <= 255; duty += 64){
      analogWrite(PWM_Pin, duty); //adjust duty cycle
      delay(100); //delay 100ms
    }
}
