/*
HardwareAPI.h - Library for using the electronic board game
Created by Casey Goins, Danae Wnuk, Chris Kmetz, and Jon Womble, January 2025
Released into the public domain
*/

#ifndef HardwareAPI_h
#define HardwareAPI_h

#include "Arduino.h"

class HardwareAPI {
  public:
    HardwareAPI();
    static void begin();
    static void turnOnLED(char hexTile, char color);
    static void turnOffLED(char hexTile);
    static void changeLEDcolor(char hexTile, char color);
    static void PrintLCD(const char c1[], const char c2[]);
    static void PrintLCDL1(const char str[]);
    static void PrintLCDL2(const char str[]);
    static void ClearLCD();
    static void ClearLCDL1();
    static void ClearLCDL2()
    
  private:
    int _00sb0 = 26 
    int _00sb1 = 28
    int _00eb = 24
};

#endif