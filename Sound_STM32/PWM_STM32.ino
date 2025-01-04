#include <TMRpcm.h>
#include "stm32h7xx.h"

TMRpcm tmrpcm;

//#define PWM_Pin 2 // Set the pin for PWM output - 2/D2/PA3

void setup() {
    // Enable clock for TIM2 (example)
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;  // Enable TIM2 clock

    // Configure TIM2 for PWM at 20 kHz
    TIM2->PSC = (SystemCoreClock / 20000) - 1;  // Set prescaler for 20 kHz - What is the SystemCoreClock frequency? 480 MHz for the M7 core.
    TIM2->ARR = 0;                           // Set auto-reload value for 20 kHz (depends on SystemCoreClock frequency) - I don't think this is correct
    TIM2->CCMR2 |= TIM_CCMR2_OC4M_PWM1;       // Set PWM mode for channel 4
    TIM2->CCER |= TIM_CCER_CC4E;              // Enable channel 4 output
    TIM2->CR1 |= TIM_CR1_CEN;                 // Start the timer

    //pinMode(PWM_Pin, OUTPUT);  // Configure pin for output

    // Set PWM frequency
    // AnalogWriteFrequency not compatible with GIGA R1
    //--analogWriteFrequency(PWM_Pin, 20000);  // Set to 20 kHz

    // Set duty cycle (0–255 range)
    //analogWrite(PWM_Pin, 64);  // 25% duty cycle
}

void loop() {
    /*for (int duty = 64; duty <= 255; duty += 64){
      analogWrite(PWM_Pin, duty); //adjust duty cycle
      delay(100); //delay 100ms
    }*/
}
