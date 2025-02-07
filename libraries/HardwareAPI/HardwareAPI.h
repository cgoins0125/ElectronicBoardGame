/*
HardwareAPI.h - Library for using the electronic board game
Created by Casey Goins, Danae Wnuk, Chris Kmetz, and Jon Womble, January 2025
Released into the public domain
*/

#ifndef HardwareAPI_h
#define HardwareAPI_h

#include "Arduino.h"
#include "Adafruit_LiquidCrystal.h"
#include "Wire.h"
#include "Adafruit_MCP23X17.h"

/*
  Hexadecimal board layout (rank 8 at the top, rank 1 at the bottom):
  
  0x70  0x71  0x72  0x73  0x74  0x75  0x76  0x77
  0x60  0x61  0x62  0x63  0x64  0x65  0x66  0x67
  0x50  0x51  0x52  0x53  0x54  0x55  0x56  0x57
  0x40  0x41  0x42  0x43  0x44  0x45  0x46  0x47
  0x30  0x31  0x32  0x33  0x34  0x35  0x36  0x37
  0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27
  0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17
  0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07
*/
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
    //private methods
    void initializeI2C();
    void initializeMCP();
    void initializePorts();
    void initializeLCD();
    void setMCPPortDir();

    //declare mcp objects
    //A2, A1, A0 = 000 → Address 0x20 (default) - for some reason mcp was set to 0x27????
    //A2, A1, A0 = 001 → Address 0x21
    //A2, A1, A0 = 010 → Address 0x22
    //A2, A1, A0 = 011 → Address 0x23
    //A2, A1, A0 = 100 → Address 0x24
    //A2, A1, A0 = 101 → Address 0x25
    //A2, A1, A0 = 110 → Address 0x26
    //A2, A1, A0 = 111 → Address 0x27
    //I2C bus 0
    Adafruit_MCP23X17 r0r1_eb_mcp; //0x20
    Adafruit_MCP23X17 r2r3_eb_mcp; //0x21
    Adafruit_MCP23X17 r4r5_eb_mcp; //0x22
    Adafruit_MCP23X17 r6r7_eb_mcp; //0x23
    //I2C bus 1
    Adafruit_MCP23X17 r0_sb_mcp; //0x20
    Adafruit_MCP23X17 r1_sb_mcp; //0x21
    Adafruit_MCP23X17 r2_sb_mcp; //0x22
    Adafruit_MCP23X17 r3_sb_mcp; //0x23
    Adafruit_MCP23X17 r4_sb_mcp; //0x24
    Adafruit_MCP23X17 r5_sb_mcp; //0x25
    Adafruit_MCP23X17 r6_sb_mcp; //0x26
    Adafruit_MCP23X17 r7_sb_mcp; //0x27

  	//declare lcd object for controlling the lcd
  	Adafruit_LiquidCrystal lcd{0};
  
	// For each tile, the two sb are select bits on the demux and eb is the enable bit
    int _00sb0, _00sb1, _00eb;
    int _01sb0, _01sb1, _01eb;
    int _02sb0, _02sb1, _02eb;
    int _03sb0, _03sb1, _03eb;
    int _04sb0, _04sb1, _04eb;
    int _05sb0, _05sb1, _05eb;
    int _06sb0, _06sb1, _06eb;
    int _07sb0, _07sb1, _07eb;

    int _10sb0, _10sb1, _10eb;
    int _11sb0, _11sb1, _11eb;
    int _12sb0, _12sb1, _12eb;
    int _13sb0, _13sb1, _13eb;
    int _14sb0, _14sb1, _14eb;
    int _15sb0, _15sb1, _15eb;
    int _16sb0, _16sb1, _16eb;
    int _17sb0, _17sb1, _17eb;

    int _20sb0, _20sb1, _20eb;
    int _21sb0, _21sb1, _21eb;
    int _22sb0, _22sb1, _22eb;
    int _23sb0, _23sb1, _23eb;
    int _24sb0, _24sb1, _24eb;
    int _25sb0, _25sb1, _25eb;
    int _26sb0, _26sb1, _26eb;
    int _27sb0, _27sb1, _27eb;

    int _30sb0, _30sb1, _30eb;
    int _31sb0, _31sb1, _31eb;
    int _32sb0, _32sb1, _32eb;
    int _33sb0, _33sb1, _33eb;
    int _34sb0, _34sb1, _34eb;
    int _35sb0, _35sb1, _35eb;
    int _36sb0, _36sb1, _36eb;
    int _37sb0, _37sb1, _37eb;

    int _40sb0, _40sb1, _40eb;
    int _41sb0, _41sb1, _41eb;
    int _42sb0, _42sb1, _42eb;
    int _43sb0, _43sb1, _43eb;
    int _44sb0, _44sb1, _44eb;
    int _45sb0, _45sb1, _45eb;
    int _46sb0, _46sb1, _46eb;
    int _47sb0, _47sb1, _47eb;

    int _50sb0, _50sb1, _50eb;
    int _51sb0, _51sb1, _51eb;
    int _52sb0, _52sb1, _52eb;
    int _53sb0, _53sb1, _53eb;
    int _54sb0, _54sb1, _54eb;
    int _55sb0, _55sb1, _55eb;
    int _56sb0, _56sb1, _56eb;
    int _57sb0, _57sb1, _57eb;

    int _60sb0, _60sb1, _60eb;
    int _61sb0, _61sb1, _61eb;
    int _62sb0, _62sb1, _62eb;
    int _63sb0, _63sb1, _63eb;
    int _64sb0, _64sb1, _64eb;
    int _65sb0, _65sb1, _65eb;
    int _66sb0, _66sb1, _66eb;
    int _67sb0, _67sb1, _67eb;

    int _70sb0, _70sb1, _70eb;
    int _71sb0, _71sb1, _71eb;
    int _72sb0, _72sb1, _72eb;
    int _73sb0, _73sb1, _73eb;
    int _74sb0, _74sb1, _74eb;
    int _75sb0, _75sb1, _75eb;
    int _76sb0, _76sb1, _76eb;
    int _77sb0, _77sb1, _77eb;
};

#endif