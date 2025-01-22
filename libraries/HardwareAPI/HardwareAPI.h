/*
HardwareAPI.h - Library for using the electronic board game
Created by Casey Goins, Danae Wnuk, Chris Kmetz, and Jon Womble, January 2025
Released into the public domain
*/

#ifndef HardwareAPI_h
#define HardwareAPI_h

#include "Arduino.h"
#include "Adafruit_LiquidCrystal.h"

class HardwareAPI {
  public:
    HardwareAPI();
    void begin();
    void turnOnLED(char hexTile, char color);
    void turnOffLED(char hexTile);
    void changeLEDcolor(char hexTile, char color);
    void PrintLCD(const char c1[], const char c2[]);
    void PrintLCDL1(const char str[]);
    void PrintLCDL2(const char str[]);
    void ClearLCD();
    void ClearLCDL1();
    void ClearLCDL2();
    
  private:
    int _00sb0; 
    int _00sb1;
    int _00eb;
    Adafruit_LiquidCrystal lcd{0};
};

#endif