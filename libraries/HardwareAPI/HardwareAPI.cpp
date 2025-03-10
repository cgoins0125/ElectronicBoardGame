#include "Arduino.h"
#include "HardwareAPI.h"
#include "Adafruit_LiquidCrystal.h"
#include "Wire.h"
#include "Adafruit_MCP23X17.h"

HardwareAPI::HardwareAPI()
{
    _00sb0 = 9; //port 13 on demux
    _00sb1 = 10; //port 14 on demux
    _00eb = 8; //port 15 on demux
}

void HardwareAPI::initializeI2C() 
{
  Wire.begin();  // Use Wire for I2C bus 0
  Wire1.begin();  // Use Wire1 for I2C bus 1
}

void HardwareAPI::initializeMCP() 
{
  r0_sb_mcp.begin_I2C(0x20, (TwoWire*)&Wire1);
}

void HardwareAPI::initializeLCD() 
{
  lcd.begin(16, 2);
}

void HardwareAPI::initializePorts() 
{
  
}
  
void HardwareAPI::setMCPPortDir() {
  // Row 0 (0x00 - 0x07) - Using r0_sb_mcp for sb
  r0_sb_mcp.pinMode(_00sb0, OUTPUT);
  r0_sb_mcp.pinMode(_00sb1, OUTPUT);
  r0_sb_mcp.pinMode(_00eb, OUTPUT);
}

void HardwareAPI::begin() 
{  
    // Connect via i2c, default address #0 (A0-A2 not jumpered)
    initializeI2C();
    initializeLCD();
    initializeMCP();
    initializePorts();
    setMCPPortDir();
}

void HardwareAPI::turnOnLED(char hexTile, char color) 
{
  changeLEDcolor(hexTile, color);
  switch (hexTile) {
  case 0x00:
    r0_sb_mcp.digitalWrite(_00eb, LOW); //active-low enable bit
    break;
  }
}

void HardwareAPI::turnOffLED(char hexTile) 
{
  switch (hexTile) {
  case 0x00:
    r0_sb_mcp.digitalWrite(_00eb, HIGH); //active-low enable bit
    break;
  }
}

/*
method: changeLEDcolor
function: changes LED color for specified tile to specified color
params:
  hexTile:
    board is represented using the "0x88" system. 
    Pass a char between 0x00 and 0x88.
      examples:
        "a1" would be 0x00 (rank 8 = 0x0, file a = 0x0)
        "h8" would be 0x77 (rank 1 = 0x7, file h = 0x7)
  color: enum: ['R','G','B','Y']
    'R' - Red
    'G' - Green
    'B' - Blue
    'Y' - Yellow
*/

void HardwareAPI::changeLEDcolor(char hexTile, char color) 
{
  switch (hexTile) {
  case 0x00:
    switch (color) {
      case 'R':
        r0_sb_mcp.digitalWrite(_00sb0, LOW);
        r0_sb_mcp.digitalWrite(_00sb1, LOW);
        break;
      case 'B':
        r0_sb_mcp.digitalWrite(_00sb0, LOW);
        r0_sb_mcp.digitalWrite(_00sb1, HIGH);
        break;
      case 'Y':
        r0_sb_mcp.digitalWrite(_00sb0, HIGH);
        r0_sb_mcp.digitalWrite(_00sb1, LOW);
        break;
      case 'G':
        r0_sb_mcp.digitalWrite(_00sb0, HIGH);
        r0_sb_mcp.digitalWrite(_00sb1, HIGH);
        break;
      default:
        //Do nothing, color is invalid
        break;
    }
    break;
  default:
    //Do nothing, invalid tile 
    break;
  }
}
    

void HardwareAPI::PrintLCD(const char c1[], const char c2[]) 
{
  ClearLCD();
  lcd.setCursor(0, 0);
  lcd.print(c1);
  lcd.setCursor(0, 1);
  lcd.print(c2);
}

    
void HardwareAPI::PrintLCDL1(const char str[]) 
{
  ClearLCDL1();
  lcd.setCursor(0, 0);
  lcd.print(str);
}

    
void HardwareAPI::PrintLCDL2(const char str[]) 
{
  ClearLCDL2();
  lcd.setCursor(0, 1);
  lcd.print(str);
}    

    
void HardwareAPI::ClearLCD() 
{
  ClearLCDL1();
  ClearLCDL2();
}

    
void HardwareAPI::ClearLCDL1() 
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
}

    
void HardwareAPI::ClearLCDL2() 
{
  lcd.setCursor(0, 1);
  lcd.print("                ");
}