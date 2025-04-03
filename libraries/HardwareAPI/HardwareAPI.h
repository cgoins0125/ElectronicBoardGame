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
    void turnOnMultipleTiles(char tiles[], int size, char color);
    void turnOffMultipleTiles(char tiles[], int size);
    void changeLEDcolor(char hexTile, char color);
    void printLCD(const char c1[], const char c2[]);
    void printLCD(const char c1[]);
    void printLCDL1(const char str[]);
    void printLCDL2(const char str[]);
    void clearLCD();
    void clearLCDL1();
    void clearLCDL2();
    bool isTileOn(char hexTile);
    char getInterruptTile();
    
  private:
    //private methods
    void initializeI2C();
    void initializeMCP();
    void initializeLCD();
    void setMCPPortDir();

    //declare mcp objects
    //A2, A1, A0 = 000 → Address 0x20 (default)
    //A2, A1, A0 = 001 → Address 0x21
    //A2, A1, A0 = 010 → Address 0x22
    //A2, A1, A0 = 011 → Address 0x23
    //A2, A1, A0 = 100 → Address 0x24
    //A2, A1, A0 = 101 → Address 0x25
    //A2, A1, A0 = 110 → Address 0x26
    //A2, A1, A0 = 111 → Address 0x27
    
    //I2C bus 0
    Adafruit_MCP23X17 r0r1_eb_mcp; //0x21
    Adafruit_MCP23X17 r2r3_eb_mcp; //0x22
    Adafruit_MCP23X17 r4r5_eb_mcp; //0x23
    Adafruit_MCP23X17 r6r7_eb_mcp; //0x24
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
  	
  	int LED_MAX_ON, LED_ON_COUNT;
  
	// For each tile, the two sb are select bits on the demux and eb is the enable bit
	int _x0sb0, _x0sb1, _x1sb0, _x1sb1, _x2sb0, _x2sb1, _x3sb0, _x3sb1;
    int _x4sb0, _x4sb1, _x5sb0, _x5sb1, _x6sb0, _x6sb1, _x7sb0, _x7sb1;
    
    int _00eb, _01eb, _02eb, _03eb, _04eb, _05eb, _06eb, _07eb;
    int _10eb, _11eb, _12eb, _13eb, _14eb, _15eb, _16eb, _17eb;
    int _20eb, _21eb, _22eb, _23eb, _24eb, _25eb, _26eb, _27eb;
    int _30eb, _31eb, _32eb, _33eb, _34eb, _35eb, _36eb, _37eb;
    int _40eb, _41eb, _42eb, _43eb, _44eb, _45eb, _46eb, _47eb;
    int _50eb, _51eb, _52eb, _53eb, _54eb, _55eb, _56eb, _57eb;
    int _60eb, _61eb, _62eb, _63eb, _64eb, _65eb, _66eb, _67eb;
    int _70eb, _71eb, _72eb, _73eb, _74eb, _75eb, _76eb, _77eb;
    
    std::map<int, char> pin_tile_interrupt_map;

};

#endif