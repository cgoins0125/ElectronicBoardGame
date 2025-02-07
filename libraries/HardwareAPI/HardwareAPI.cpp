#include "Arduino.h"
#include "HardwareAPI.h"
#include "Adafruit_LiquidCrystal.h"


/*
  Hexadecimal board layout (rank 8 at the top, rank 1 at the bottom):
  
 8 |0x70  0x71  0x72  0x73  0x74  0x75  0x76  0x77|
 7 |0x60  0x61  0x62  0x63  0x64  0x65  0x66  0x67|
 6 |0x50  0x51  0x52  0x53  0x54  0x55  0x56  0x57|
 5 |0x40  0x41  0x42  0x43  0x44  0x45  0x46  0x47|
 4 |0x30  0x31  0x32  0x33  0x34  0x35  0x36  0x37|
 3 |0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27|
 2 |0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17|
 1 |0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07|
 	 A	   B     C     D     E     F     G     H
*/

void HardwareAPI::initializeI2C() {
  Wire.begin();  // Use Wire for I2C bus 0
  Wire1.begin();  // Use Wire1 for I2C bus 1
}

void HardwareAPI::initializeMCP() {
  // Initialize mcps for I2C bus 0
  r0r1_eb_mcp.begin_I2C(0x20, (TwoWire*)&Wire);
  r2r3_eb_mcp.begin_I2C(0x21, (TwoWire*)&Wire);
  r4r5_eb_mcp.begin_I2C(0x22, (TwoWire*)&Wire);
  r6r7_eb_mcp.begin_I2C(0x23, (TwoWire*)&Wire);

  // Initialize mcps for I2C bus 1
  r0_sb_mcp.begin_I2C(0x20, (TwoWire*)&Wire1);
  r1_sb_mcp.begin_I2C(0x21, (TwoWire*)&Wire1);
  r2_sb_mcp.begin_I2C(0x22, (TwoWire*)&Wire1);
  r3_sb_mcp.begin_I2C(0x23, (TwoWire*)&Wire1);
  r4_sb_mcp.begin_I2C(0x24, (TwoWire*)&Wire1);
  r5_sb_mcp.begin_I2C(0x25, (TwoWire*)&Wire1);
  r6_sb_mcp.begin_I2C(0x26, (TwoWire*)&Wire1);
  r7_sb_mcp.begin_I2C(0x27, (TwoWire*)&Wire1);
}

void HardwareAPI::initializePorts() {

  _00sb0 = 0; 
  _00sb1 = 1;
  _01sb0 = 2;  
  _01sb1 = 3;
  _02sb0 = 4;  
  _02sb1 = 5;
  _03sb0 = 6;  
  _03sb1 = 7;
  _04sb0 = 8;  
  _04sb1 = 9;
  _05sb0 = 10;
  _05sb1 = 11;
  _06sb0 = 12;  
  _06sb1 = 13;
  _07sb0 = 14;  
  _07sb1 = 15;

  _10sb0 = 0;  
  _10sb1 = 1;
  _11sb0 = 2;  
  _11sb1 = 3;
  _12sb0 = 4;  
  _12sb1 = 5;
  _13sb0 = 6;  
  _13sb1 = 7;
  _14sb0 = 8;  
  _14sb1 = 9;
  _15sb0 = 10;  
  _15sb1 = 11;
  _16sb0 = 12;  
  _16sb1 = 13;
  _17sb0 = 14;  
  _17sb1 = 15;


  _20sb0 = 0;  
  _20sb1 = 1;
  _21sb0 = 2;  
  _21sb1 = 3;
  _22sb0 = 4;  
  _22sb1 = 5;
  _23sb0 = 6;  
  _23sb1 = 7;
  _24sb0 = 8;  
  _24sb1 = 9;
  _25sb0 = 10;  
  _25sb1 = 11;
  _26sb0 = 12;  
  _26sb1 = 13;
  _27sb0 = 14;  
  _27sb1 = 15;

  _30sb0 = 0;  
  _30sb1 = 1;
  _31sb0 = 2;  
  _31sb1 = 3;
  _32sb0 = 4;  
  _32sb1 = 5;
  _33sb0 = 6;  
  _33sb1 = 7;
  _34sb0 = 8;  
  _34sb1 = 9;
  _35sb0 = 10;  
  _35sb1 = 11;
  _36sb0 = 12;  
  _36sb1 = 13;
  _37sb0 = 14;  
  _37sb1 = 15;

  _40sb0 = 0;  
  _40sb1 = 1;
  _41sb0 = 2;  
  _41sb1 = 3;
  _42sb0 = 4;  
  _42sb1 = 5;
  _43sb0 = 6;  
  _43sb1 = 7;
  _44sb0 = 8;  
  _44sb1 = 9;
  _45sb0 = 10;  
  _45sb1 = 11;
  _46sb0 = 12;  
  _46sb1 = 13;
  _47sb0 = 14;  
  _47sb1 = 15;

  _50sb0 = 0;  
  _50sb1 = 1;
  _51sb0 = 2;  
  _51sb1 = 3;
  _52sb0 = 4;  
  _52sb1 = 5;
  _53sb0 = 6;  
  _53sb1 = 7;
  _54sb0 = 8;  
  _54sb1 = 9;
  _55sb0 = 10;  
  _55sb1 = 11;
  _56sb0 = 12;  
  _56sb1 = 13;
  _57sb0 = 14;  
  _57sb1 = 15;

  _60sb0 = 0;  
  _60sb1 = 1;
  _61sb0 = 2;  
  _61sb1 = 3;
  _62sb0 = 4;  
  _62sb1 = 5;
  _63sb0 = 6;  
  _63sb1 = 7;
  _64sb0 = 8;  
  _64sb1 = 9;
  _65sb0 = 10;  
  _65sb1 = 11;
  _66sb0 = 12;  
  _66sb1 = 13;
  _67sb0 = 14;  
  _67sb1 = 15;

  _70sb0 = 0;  
  _70sb1 = 1;
  _71sb0 = 2;  
  _71sb1 = 3;
  _72sb0 = 4;  
  _72sb1 = 5;
  _73sb0 = 6;  
  _73sb1 = 7;
  _74sb0 = 8;  
  _74sb1 = 9;
  _75sb0 = 10;  
  _75sb1 = 11;
  _76sb0 = 12;  
  _76sb1 = 13;
  _77sb0 = 14;  
  _77sb1 = 15;

  _00eb  = 0;
  _01eb  = 1;
  _02eb  = 2;
  _03eb  = 3;
  _04eb  = 4;
  _05eb  = 5;
  _06eb  = 6;
  _07eb  = 7;
  _10eb  = 8;
  _11eb  = 9;
  _12eb  = 10;
  _13eb  = 11;
  _14eb  = 12;
  _15eb  = 13;
  _16eb  = 14;
  _17eb  = 15;

  _20eb  = 0;
  _21eb  = 1;
  _22eb  = 2;
  _23eb  = 3;
  _24eb  = 4;
  _25eb  = 5;
  _26eb  = 6;
  _27eb  = 7;
  _30eb  = 8;
  _31eb  = 9;
  _32eb  = 10;
  _33eb  = 11;
  _34eb  = 12;
  _35eb  = 13;
  _36eb  = 14;
  _37eb  = 15;

  _40eb  = 0;
  _41eb  = 1;
  _42eb  = 2;
  _43eb  = 3;
  _44eb  = 4;
  _45eb  = 5;
  _46eb  = 6;
  _47eb  = 7;
  _50eb  = 8;
  _51eb  = 9;
  _52eb  = 10;
  _53eb  = 11;
  _54eb  = 12;
  _55eb  = 13;
  _56eb  = 14;
  _57eb  = 15;

  _60eb  = 0;
  _61eb  = 1;
  _62eb  = 2;
  _63eb  = 3;
  _64eb  = 4;
  _65eb  = 5;
  _66eb  = 6;
  _67eb  = 7;
  _70eb  = 8;
  _71eb  = 9;
  _72eb  = 10;
  _73eb  = 11;
  _74eb  = 12;
  _75eb  = 13;
  _76eb  = 14;
  _77eb  = 15;

}

void HardwareAPI::setMCPPortDir() {
  // Row 0 (0x00 - 0x07) - Using r0_sb_mcp for sb
  r0_sb_mcp.pinMode(_00sb0, OUTPUT);
  r0_sb_mcp.pinMode(_00sb1, OUTPUT);
  r0_sb_mcp.pinMode(_01sb0, OUTPUT);
  r0_sb_mcp.pinMode(_01sb1, OUTPUT);
  r0_sb_mcp.pinMode(_02sb0, OUTPUT);
  r0_sb_mcp.pinMode(_02sb1, OUTPUT);
  r0_sb_mcp.pinMode(_03sb0, OUTPUT);
  r0_sb_mcp.pinMode(_03sb1, OUTPUT);
  r0_sb_mcp.pinMode(_04sb0, OUTPUT);
  r0_sb_mcp.pinMode(_04sb1, OUTPUT);
  r0_sb_mcp.pinMode(_05sb0, OUTPUT);
  r0_sb_mcp.pinMode(_05sb1, OUTPUT);
  r0_sb_mcp.pinMode(_06sb0, OUTPUT);
  r0_sb_mcp.pinMode(_06sb1, OUTPUT);
  r0_sb_mcp.pinMode(_07sb0, OUTPUT);
  r0_sb_mcp.pinMode(_07sb1, OUTPUT);

  // Row 1 (0x10 - 0x17) - Using r1_sb_mcp for sb
  r1_sb_mcp.pinMode(_10sb0, OUTPUT);
  r1_sb_mcp.pinMode(_10sb1, OUTPUT);
  r1_sb_mcp.pinMode(_11sb0, OUTPUT);
  r1_sb_mcp.pinMode(_11sb1, OUTPUT);
  r1_sb_mcp.pinMode(_12sb0, OUTPUT);
  r1_sb_mcp.pinMode(_12sb1, OUTPUT);
  r1_sb_mcp.pinMode(_13sb0, OUTPUT);
  r1_sb_mcp.pinMode(_13sb1, OUTPUT);
  r1_sb_mcp.pinMode(_14sb0, OUTPUT);
  r1_sb_mcp.pinMode(_14sb1, OUTPUT);
  r1_sb_mcp.pinMode(_15sb0, OUTPUT);
  r1_sb_mcp.pinMode(_15sb1, OUTPUT);
  r1_sb_mcp.pinMode(_16sb0, OUTPUT);
  r1_sb_mcp.pinMode(_16sb1, OUTPUT);
  r1_sb_mcp.pinMode(_17sb0, OUTPUT);
  r1_sb_mcp.pinMode(_17sb1, OUTPUT);

  // Row 2 (0x20 - 0x27) - Using r2_sb_mcp for sb
  r2_sb_mcp.pinMode(_20sb0, OUTPUT);
  r2_sb_mcp.pinMode(_20sb1, OUTPUT);
  r2_sb_mcp.pinMode(_21sb0, OUTPUT);
  r2_sb_mcp.pinMode(_21sb1, OUTPUT);
  r2_sb_mcp.pinMode(_22sb0, OUTPUT);
  r2_sb_mcp.pinMode(_22sb1, OUTPUT);
  r2_sb_mcp.pinMode(_23sb0, OUTPUT);
  r2_sb_mcp.pinMode(_23sb1, OUTPUT);
  r2_sb_mcp.pinMode(_24sb0, OUTPUT);
  r2_sb_mcp.pinMode(_24sb1, OUTPUT);
  r2_sb_mcp.pinMode(_25sb0, OUTPUT);
  r2_sb_mcp.pinMode(_25sb1, OUTPUT);
  r2_sb_mcp.pinMode(_26sb0, OUTPUT);
  r2_sb_mcp.pinMode(_26sb1, OUTPUT);
  r2_sb_mcp.pinMode(_27sb0, OUTPUT);
  r2_sb_mcp.pinMode(_27sb1, OUTPUT);

  // Row 3 (0x30 - 0x37) - Using r3_sb_mcp for sb
  r3_sb_mcp.pinMode(_30sb0, OUTPUT);
  r3_sb_mcp.pinMode(_30sb1, OUTPUT);
  r3_sb_mcp.pinMode(_31sb0, OUTPUT);
  r3_sb_mcp.pinMode(_31sb1, OUTPUT);
  r3_sb_mcp.pinMode(_32sb0, OUTPUT);
  r3_sb_mcp.pinMode(_32sb1, OUTPUT);
  r3_sb_mcp.pinMode(_33sb0, OUTPUT);
  r3_sb_mcp.pinMode(_33sb1, OUTPUT);
  r3_sb_mcp.pinMode(_34sb0, OUTPUT);
  r3_sb_mcp.pinMode(_34sb1, OUTPUT);
  r3_sb_mcp.pinMode(_35sb0, OUTPUT);
  r3_sb_mcp.pinMode(_35sb1, OUTPUT);
  r3_sb_mcp.pinMode(_36sb0, OUTPUT);
  r3_sb_mcp.pinMode(_36sb1, OUTPUT);
  r3_sb_mcp.pinMode(_37sb0, OUTPUT);
  r3_sb_mcp.pinMode(_37sb1, OUTPUT);

  // Row 4 (0x40 - 0x47) - Using r4_sb_mcp for sb
  r4_sb_mcp.pinMode(_40sb0, OUTPUT);
  r4_sb_mcp.pinMode(_40sb1, OUTPUT);
  r4_sb_mcp.pinMode(_41sb0, OUTPUT);
  r4_sb_mcp.pinMode(_41sb1, OUTPUT);
  r4_sb_mcp.pinMode(_42sb0, OUTPUT);
  r4_sb_mcp.pinMode(_42sb1, OUTPUT);
  r4_sb_mcp.pinMode(_43sb0, OUTPUT);
  r4_sb_mcp.pinMode(_43sb1, OUTPUT);
  r4_sb_mcp.pinMode(_44sb0, OUTPUT);
  r4_sb_mcp.pinMode(_44sb1, OUTPUT);
  r4_sb_mcp.pinMode(_45sb0, OUTPUT);
  r4_sb_mcp.pinMode(_45sb1, OUTPUT);
  r4_sb_mcp.pinMode(_46sb0, OUTPUT);
  r4_sb_mcp.pinMode(_46sb1, OUTPUT);
  r4_sb_mcp.pinMode(_47sb0, OUTPUT);
  r4_sb_mcp.pinMode(_47sb1, OUTPUT);

  // Row 5 (0x50 - 0x57) - Using r5_sb_mcp for sb
  r5_sb_mcp.pinMode(_50sb0, OUTPUT);
  r5_sb_mcp.pinMode(_50sb1, OUTPUT);
  r5_sb_mcp.pinMode(_51sb0, OUTPUT);
  r5_sb_mcp.pinMode(_51sb1, OUTPUT);
  r5_sb_mcp.pinMode(_52sb0, OUTPUT);
  r5_sb_mcp.pinMode(_52sb1, OUTPUT);
  r5_sb_mcp.pinMode(_53sb0, OUTPUT);
  r5_sb_mcp.pinMode(_53sb1, OUTPUT);
  r5_sb_mcp.pinMode(_54sb0, OUTPUT);
  r5_sb_mcp.pinMode(_54sb1, OUTPUT);
  r5_sb_mcp.pinMode(_55sb0, OUTPUT);
  r5_sb_mcp.pinMode(_55sb1, OUTPUT);
  r5_sb_mcp.pinMode(_56sb0, OUTPUT);
  r5_sb_mcp.pinMode(_56sb1, OUTPUT);
  r5_sb_mcp.pinMode(_57sb0, OUTPUT);
  r5_sb_mcp.pinMode(_57sb1, OUTPUT);

  // Row 6 (0x60 - 0x67) - Using r6_sb_mcp for sb
  r6_sb_mcp.pinMode(_60sb0, OUTPUT);
  r6_sb_mcp.pinMode(_60sb1, OUTPUT);
  r6_sb_mcp.pinMode(_61sb0, OUTPUT);
  r6_sb_mcp.pinMode(_61sb1, OUTPUT);
  r6_sb_mcp.pinMode(_62sb0, OUTPUT);
  r6_sb_mcp.pinMode(_62sb1, OUTPUT);
  r6_sb_mcp.pinMode(_63sb0, OUTPUT);
  r6_sb_mcp.pinMode(_63sb1, OUTPUT);
  r6_sb_mcp.pinMode(_64sb0, OUTPUT);
  r6_sb_mcp.pinMode(_64sb1, OUTPUT);
  r6_sb_mcp.pinMode(_65sb0, OUTPUT);
  r6_sb_mcp.pinMode(_65sb1, OUTPUT);
  r6_sb_mcp.pinMode(_66sb0, OUTPUT);
  r6_sb_mcp.pinMode(_66sb1, OUTPUT);
  r6_sb_mcp.pinMode(_67sb0, OUTPUT);
  r6_sb_mcp.pinMode(_67sb1, OUTPUT);

  // Row 7 (0x70 - 0x77) - Using r7_sb_mcp for sb
  r7_sb_mcp.pinMode(_70sb0, OUTPUT);
  r7_sb_mcp.pinMode(_70sb1, OUTPUT);
  r7_sb_mcp.pinMode(_71sb0, OUTPUT);
  r7_sb_mcp.pinMode(_71sb1, OUTPUT);
  r7_sb_mcp.pinMode(_72sb0, OUTPUT);
  r7_sb_mcp.pinMode(_72sb1, OUTPUT);
  r7_sb_mcp.pinMode(_73sb0, OUTPUT);
  r7_sb_mcp.pinMode(_73sb1, OUTPUT);
  r7_sb_mcp.pinMode(_74sb0, OUTPUT);
  r7_sb_mcp.pinMode(_74sb1, OUTPUT);
  r7_sb_mcp.pinMode(_75sb0, OUTPUT);
  r7_sb_mcp.pinMode(_75sb1, OUTPUT);
  r7_sb_mcp.pinMode(_76sb0, OUTPUT);
  r7_sb_mcp.pinMode(_76sb1, OUTPUT);
  r7_sb_mcp.pinMode(_77sb0, OUTPUT);
  r7_sb_mcp.pinMode(_77sb1, OUTPUT);

  // Row 0 (0x00 - 0x07) - Using r0r1_eb_mcp for eb
  r0r1_eb_mcp.pinMode(_00eb, OUTPUT);
  r0r1_eb_mcp.pinMode(_01eb, OUTPUT);
  r0r1_eb_mcp.pinMode(_02eb, OUTPUT);
  r0r1_eb_mcp.pinMode(_03eb, OUTPUT);
  r0r1_eb_mcp.pinMode(_04eb, OUTPUT);
  r0r1_eb_mcp.pinMode(_05eb, OUTPUT);
  r0r1_eb_mcp.pinMode(_06eb, OUTPUT);
  r0r1_eb_mcp.pinMode(_07eb, OUTPUT);

  // Row 1 (0x10 - 0x17) - Using r0r1_eb_mcp for eb
  r0r1_eb_mcp.pinMode(_10eb, OUTPUT);
  r0r1_eb_mcp.pinMode(_11eb, OUTPUT);
  r0r1_eb_mcp.pinMode(_12eb, OUTPUT);
  r0r1_eb_mcp.pinMode(_13eb, OUTPUT);
  r0r1_eb_mcp.pinMode(_14eb, OUTPUT);
  r0r1_eb_mcp.pinMode(_15eb, OUTPUT);
  r0r1_eb_mcp.pinMode(_16eb, OUTPUT);
  r0r1_eb_mcp.pinMode(_17eb, OUTPUT);

  // Row 2 (0x20 - 0x27) - Using r2r3_eb_mcp for eb
  r2r3_eb_mcp.pinMode(_20eb, OUTPUT);
  r2r3_eb_mcp.pinMode(_21eb, OUTPUT);
  r2r3_eb_mcp.pinMode(_22eb, OUTPUT);
  r2r3_eb_mcp.pinMode(_23eb, OUTPUT);
  r2r3_eb_mcp.pinMode(_24eb, OUTPUT);
  r2r3_eb_mcp.pinMode(_25eb, OUTPUT);
  r2r3_eb_mcp.pinMode(_26eb, OUTPUT);
  r2r3_eb_mcp.pinMode(_27eb, OUTPUT);

  // Row 3 (0x30 - 0x37) - Using r2r3_eb_mcp for eb
  r2r3_eb_mcp.pinMode(_30eb, OUTPUT);
  r2r3_eb_mcp.pinMode(_31eb, OUTPUT);
  r2r3_eb_mcp.pinMode(_32eb, OUTPUT);
  r2r3_eb_mcp.pinMode(_33eb, OUTPUT);
  r2r3_eb_mcp.pinMode(_34eb, OUTPUT);
  r2r3_eb_mcp.pinMode(_35eb, OUTPUT);
  r2r3_eb_mcp.pinMode(_36eb, OUTPUT);
  r2r3_eb_mcp.pinMode(_37eb, OUTPUT);

  // Row 4 (0x40 - 0x47) - Using r4r5_eb_mcp for eb
  r4r5_eb_mcp.pinMode(_40eb, OUTPUT);
  r4r5_eb_mcp.pinMode(_41eb, OUTPUT);
  r4r5_eb_mcp.pinMode(_42eb, OUTPUT);
  r4r5_eb_mcp.pinMode(_43eb, OUTPUT);
  r4r5_eb_mcp.pinMode(_44eb, OUTPUT);
  r4r5_eb_mcp.pinMode(_45eb, OUTPUT);
  r4r5_eb_mcp.pinMode(_46eb, OUTPUT);
  r4r5_eb_mcp.pinMode(_47eb, OUTPUT);

  // Row 5 (0x50 - 0x57) - Using r4r5_eb_mcp for eb
  r4r5_eb_mcp.pinMode(_50eb, OUTPUT);
  r4r5_eb_mcp.pinMode(_51eb, OUTPUT);
  r4r5_eb_mcp.pinMode(_52eb, OUTPUT);
  r4r5_eb_mcp.pinMode(_53eb, OUTPUT);
  r4r5_eb_mcp.pinMode(_54eb, OUTPUT);
  r4r5_eb_mcp.pinMode(_55eb, OUTPUT);
  r4r5_eb_mcp.pinMode(_56eb, OUTPUT);
  r4r5_eb_mcp.pinMode(_57eb, OUTPUT);

  // Row 6 (0x60 - 0x67) - Using r6r7_eb_mcp for eb
  r6r7_eb_mcp.pinMode(_60eb, OUTPUT);
  r6r7_eb_mcp.pinMode(_61eb, OUTPUT);
  r6r7_eb_mcp.pinMode(_62eb, OUTPUT);
  r6r7_eb_mcp.pinMode(_63eb, OUTPUT);
  r6r7_eb_mcp.pinMode(_64eb, OUTPUT);
  r6r7_eb_mcp.pinMode(_65eb, OUTPUT);
  r6r7_eb_mcp.pinMode(_66eb, OUTPUT);
  r6r7_eb_mcp.pinMode(_67eb, OUTPUT);

  // Row 7 (0x70 - 0x77) - Using r6r7_eb_mcp for eb
  r6r7_eb_mcp.pinMode(_70eb, OUTPUT);
  r6r7_eb_mcp.pinMode(_71eb, OUTPUT);
  r6r7_eb_mcp.pinMode(_72eb, OUTPUT);
  r6r7_eb_mcp.pinMode(_73eb, OUTPUT);
  r6r7_eb_mcp.pinMode(_74eb, OUTPUT);
  r6r7_eb_mcp.pinMode(_75eb, OUTPUT);
  r6r7_eb_mcp.pinMode(_76eb, OUTPUT);
  r6r7_eb_mcp.pinMode(_77eb, OUTPUT);
}

void HardwareAPI::initializeLCD() {
  lcd.begin(16, 2);
}

HardwareAPI::HardwareAPI()
{
    initializeI2C();
    initializeLCD();
    initializeMCP();
    initializePorts();
}

/* method: begin
function: Constructor
*/
void HardwareAPI::begin() 
{  
  setMCPPortDir();
}

/* method: turnOnLED
function: Turns on the LED for a specified tile using the provided color.
details:
	- Calls changeLEDcolor() to set the LED to the desired color.
  	- Enables the LED by setting the specified tile's active-low enable bit to LOW.
params:
  	- hexTile:
		* Board is represented using the "0x88" system.
      	* Pass a char representing the tile, with valid values between 0x00 and 0x77.
      	* Examples:
        	- "a1" corresponds to 0x00 (file a = 0x0, rank 1 = 0x0)
        	- "h8" corresponds to 0x77 (file h = 0x7, rank 8 = 0x7)
  - color:
      	* Enumeration: ['R', 'G', 'B', 'Y']
        	- 'R' - Red
        	- 'G' - Green
        	- 'B' - Blue
        	- 'Y' - Yellow
*/
void HardwareAPI::turnOnLED(char hexTile, char color) 
{
  // Set the LED color first.
  changeLEDcolor(hexTile, color);

  // Then enable the LED using the active-low enable bit.
  switch (hexTile) {
    // Row 0 (0x00 - 0x07)
    case 0x00: r0r1_eb_mcp.digitalWrite(_00eb, LOW); break;
    case 0x01: r0r1_eb_mcp.digitalWrite(_01eb, LOW); break;
    case 0x02: r0r1_eb_mcp.digitalWrite(_02eb, LOW); break;
    case 0x03: r0r1_eb_mcp.digitalWrite(_03eb, LOW); break;
    case 0x04: r0r1_eb_mcp.digitalWrite(_04eb, LOW); break;
    case 0x05: r0r1_eb_mcp.digitalWrite(_05eb, LOW); break;
    case 0x06: r0r1_eb_mcp.digitalWrite(_06eb, LOW); break;
    case 0x07: r0r1_eb_mcp.digitalWrite(_07eb, LOW); break;

    // Row 1 (0x10 - 0x17)
    case 0x10: r0r1_eb_mcp.digitalWrite(_10eb, LOW); break;
    case 0x11: r0r1_eb_mcp.digitalWrite(_11eb, LOW); break;
    case 0x12: r0r1_eb_mcp.digitalWrite(_12eb, LOW); break;
    case 0x13: r0r1_eb_mcp.digitalWrite(_13eb, LOW); break;
    case 0x14: r0r1_eb_mcp.digitalWrite(_14eb, LOW); break;
    case 0x15: r0r1_eb_mcp.digitalWrite(_15eb, LOW); break;
    case 0x16: r0r1_eb_mcp.digitalWrite(_16eb, LOW); break;
    case 0x17: r0r1_eb_mcp.digitalWrite(_17eb, LOW); break;

    // Row 2 (0x20 - 0x27)
    case 0x20: r2r3_eb_mcp.digitalWrite(_20eb, LOW); break;
    case 0x21: r2r3_eb_mcp.digitalWrite(_21eb, LOW); break;
    case 0x22: r2r3_eb_mcp.digitalWrite(_22eb, LOW); break;
    case 0x23: r2r3_eb_mcp.digitalWrite(_23eb, LOW); break;
    case 0x24: r2r3_eb_mcp.digitalWrite(_24eb, LOW); break;
    case 0x25: r2r3_eb_mcp.digitalWrite(_25eb, LOW); break;
    case 0x26: r2r3_eb_mcp.digitalWrite(_26eb, LOW); break;
    case 0x27: r2r3_eb_mcp.digitalWrite(_27eb, LOW); break;

    // Row 3 (0x30 - 0x37)
    case 0x30: r2r3_eb_mcp.digitalWrite(_30eb, LOW); break;
    case 0x31: r2r3_eb_mcp.digitalWrite(_31eb, LOW); break;
    case 0x32: r2r3_eb_mcp.digitalWrite(_32eb, LOW); break;
    case 0x33: r2r3_eb_mcp.digitalWrite(_33eb, LOW); break;
    case 0x34: r2r3_eb_mcp.digitalWrite(_34eb, LOW); break;
    case 0x35: r2r3_eb_mcp.digitalWrite(_35eb, LOW); break;
    case 0x36: r2r3_eb_mcp.digitalWrite(_36eb, LOW); break;
    case 0x37: r2r3_eb_mcp.digitalWrite(_37eb, LOW); break;

    // Row 4 (0x40 - 0x47)
    case 0x40: r4r5_eb_mcp.digitalWrite(_40eb, LOW); break;
    case 0x41: r4r5_eb_mcp.digitalWrite(_41eb, LOW); break;
    case 0x42: r4r5_eb_mcp.digitalWrite(_42eb, LOW); break;
    case 0x43: r4r5_eb_mcp.digitalWrite(_43eb, LOW); break;
    case 0x44: r4r5_eb_mcp.digitalWrite(_44eb, LOW); break;
    case 0x45: r4r5_eb_mcp.digitalWrite(_45eb, LOW); break;
    case 0x46: r4r5_eb_mcp.digitalWrite(_46eb, LOW); break;
    case 0x47: r4r5_eb_mcp.digitalWrite(_47eb, LOW); break;

    // Row 5 (0x50 - 0x57)
    case 0x50: r4r5_eb_mcp.digitalWrite(_50eb, LOW); break;
    case 0x51: r4r5_eb_mcp.digitalWrite(_51eb, LOW); break;
    case 0x52: r4r5_eb_mcp.digitalWrite(_52eb, LOW); break;
    case 0x53: r4r5_eb_mcp.digitalWrite(_53eb, LOW); break;
    case 0x54: r4r5_eb_mcp.digitalWrite(_54eb, LOW); break;
    case 0x55: r4r5_eb_mcp.digitalWrite(_55eb, LOW); break;
    case 0x56: r4r5_eb_mcp.digitalWrite(_56eb, LOW); break;
    case 0x57: r4r5_eb_mcp.digitalWrite(_57eb, LOW); break;

    // Row 6 (0x60 - 0x67)
    case 0x60: r6r7_eb_mcp.digitalWrite(_60eb, LOW); break;
    case 0x61: r6r7_eb_mcp.digitalWrite(_61eb, LOW); break;
    case 0x62: r6r7_eb_mcp.digitalWrite(_62eb, LOW); break;
    case 0x63: r6r7_eb_mcp.digitalWrite(_63eb, LOW); break;
    case 0x64: r6r7_eb_mcp.digitalWrite(_64eb, LOW); break;
    case 0x65: r6r7_eb_mcp.digitalWrite(_65eb, LOW); break;
    case 0x66: r6r7_eb_mcp.digitalWrite(_66eb, LOW); break;
    case 0x67: r6r7_eb_mcp.digitalWrite(_67eb, LOW); break;

    // Row 7 (0x70 - 0x77)
    case 0x70: r6r7_eb_mcp.digitalWrite(_70eb, LOW); break;
    case 0x71: r6r7_eb_mcp.digitalWrite(_71eb, LOW); break;
    case 0x72: r6r7_eb_mcp.digitalWrite(_72eb, LOW); break;
    case 0x73: r6r7_eb_mcp.digitalWrite(_73eb, LOW); break;
    case 0x74: r6r7_eb_mcp.digitalWrite(_74eb, LOW); break;
    case 0x75: r6r7_eb_mcp.digitalWrite(_75eb, LOW); break;
    case 0x76: r6r7_eb_mcp.digitalWrite(_76eb, LOW); break;
    case 0x77: r6r7_eb_mcp.digitalWrite(_77eb, LOW); break;

    default:
        // Optionally handle an invalid tile value.
        break;
  }
}

/* method: turnOffLED
function: Turns off the LED for a specified tile.
details:
  	- Disables the LED by setting its active-low enable bit to HIGH.
params:
  	- hexTile:
		* Board is represented using the "0x88" system.
      	* Pass a char representing the tile, with valid values between 0x00 and 0x77.
      	* Examples:
        	- "a1" corresponds to 0x00 (file a = 0x0, rank 1 = 0x0)
        	- "h8" corresponds to 0x77 (file h = 0x7, rank 8 = 0x7)
*/
void HardwareAPI::turnOffLED(char hexTile) 
{
  // Disable the LED using the active-low enable bit.
  switch (hexTile) {
    // Row 0 (0x00 - 0x07)
    case 0x00: r0r1_eb_mcp.digitalWrite(_00eb, HIGH); break;
    case 0x01: r0r1_eb_mcp.digitalWrite(_01eb, HIGH); break;
    case 0x02: r0r1_eb_mcp.digitalWrite(_02eb, HIGH); break;
    case 0x03: r0r1_eb_mcp.digitalWrite(_03eb, HIGH); break;
    case 0x04: r0r1_eb_mcp.digitalWrite(_04eb, HIGH); break;
    case 0x05: r0r1_eb_mcp.digitalWrite(_05eb, HIGH); break;
    case 0x06: r0r1_eb_mcp.digitalWrite(_06eb, HIGH); break;
    case 0x07: r0r1_eb_mcp.digitalWrite(_07eb, HIGH); break;

    // Row 1 (0x10 - 0x17)
    case 0x10: r0r1_eb_mcp.digitalWrite(_10eb, HIGH); break;
    case 0x11: r0r1_eb_mcp.digitalWrite(_11eb, HIGH); break;
    case 0x12: r0r1_eb_mcp.digitalWrite(_12eb, HIGH); break;
    case 0x13: r0r1_eb_mcp.digitalWrite(_13eb, HIGH); break;
    case 0x14: r0r1_eb_mcp.digitalWrite(_14eb, HIGH); break;
    case 0x15: r0r1_eb_mcp.digitalWrite(_15eb, HIGH); break;
    case 0x16: r0r1_eb_mcp.digitalWrite(_16eb, HIGH); break;
    case 0x17: r0r1_eb_mcp.digitalWrite(_17eb, HIGH); break;

    // Row 2 (0x20 - 0x27)
    case 0x20: r2r3_eb_mcp.digitalWrite(_20eb, HIGH); break;
    case 0x21: r2r3_eb_mcp.digitalWrite(_21eb, HIGH); break;
    case 0x22: r2r3_eb_mcp.digitalWrite(_22eb, HIGH); break;
    case 0x23: r2r3_eb_mcp.digitalWrite(_23eb, HIGH); break;
    case 0x24: r2r3_eb_mcp.digitalWrite(_24eb, HIGH); break;
    case 0x25: r2r3_eb_mcp.digitalWrite(_25eb, HIGH); break;
    case 0x26: r2r3_eb_mcp.digitalWrite(_26eb, HIGH); break;
    case 0x27: r2r3_eb_mcp.digitalWrite(_27eb, HIGH); break;

            // Row 3 (0x30 - 0x37)
    case 0x30: r2r3_eb_mcp.digitalWrite(_30eb, HIGH); break;
    case 0x31: r2r3_eb_mcp.digitalWrite(_31eb, HIGH); break;
    case 0x32: r2r3_eb_mcp.digitalWrite(_32eb, HIGH); break;
    case 0x33: r2r3_eb_mcp.digitalWrite(_33eb, HIGH); break;
    case 0x34: r2r3_eb_mcp.digitalWrite(_34eb, HIGH); break;
    case 0x35: r2r3_eb_mcp.digitalWrite(_35eb, HIGH); break;
    case 0x36: r2r3_eb_mcp.digitalWrite(_36eb, HIGH); break;
    case 0x37: r2r3_eb_mcp.digitalWrite(_37eb, HIGH); break;

    // Row 4 (0x40 - 0x47)
    case 0x40: r4r5_eb_mcp.digitalWrite(_40eb, HIGH); break;
    case 0x41: r4r5_eb_mcp.digitalWrite(_41eb, HIGH); break;
    case 0x42: r4r5_eb_mcp.digitalWrite(_42eb, HIGH); break;
    case 0x43: r4r5_eb_mcp.digitalWrite(_43eb, HIGH); break;
    case 0x44: r4r5_eb_mcp.digitalWrite(_44eb, HIGH); break;
    case 0x45: r4r5_eb_mcp.digitalWrite(_45eb, HIGH); break;
    case 0x46: r4r5_eb_mcp.digitalWrite(_46eb, HIGH); break;
    case 0x47: r4r5_eb_mcp.digitalWrite(_47eb, HIGH); break;

    // Row 5 (0x50 - 0x57)
    case 0x50: r4r5_eb_mcp.digitalWrite(_50eb, HIGH); break;
    case 0x51: r4r5_eb_mcp.digitalWrite(_51eb, HIGH); break;
    case 0x52: r4r5_eb_mcp.digitalWrite(_52eb, HIGH); break;
    case 0x53: r4r5_eb_mcp.digitalWrite(_53eb, HIGH); break;
    case 0x54: r4r5_eb_mcp.digitalWrite(_54eb, HIGH); break;
    case 0x55: r4r5_eb_mcp.digitalWrite(_55eb, HIGH); break;
    case 0x56: r4r5_eb_mcp.digitalWrite(_56eb, HIGH); break;
    case 0x57: r4r5_eb_mcp.digitalWrite(_57eb, HIGH); break;

    // Row 6 (0x60 - 0x67)
    case 0x60: r6r7_eb_mcp.digitalWrite(_60eb, HIGH); break;
    case 0x61: r6r7_eb_mcp.digitalWrite(_61eb, HIGH); break;
    case 0x62: r6r7_eb_mcp.digitalWrite(_62eb, HIGH); break;
    case 0x63: r6r7_eb_mcp.digitalWrite(_63eb, HIGH); break;
    case 0x64: r6r7_eb_mcp.digitalWrite(_64eb, HIGH); break;
    case 0x65: r6r7_eb_mcp.digitalWrite(_65eb, HIGH); break;
    case 0x66: r6r7_eb_mcp.digitalWrite(_66eb, HIGH); break;
    case 0x67: r6r7_eb_mcp.digitalWrite(_67eb, HIGH); break;

    // Row 7 (0x70 - 0x77)
    case 0x70: r6r7_eb_mcp.digitalWrite(_70eb, HIGH); break;
    case 0x71: r6r7_eb_mcp.digitalWrite(_71eb, HIGH); break;
    case 0x72: r6r7_eb_mcp.digitalWrite(_72eb, HIGH); break;
    case 0x73: r6r7_eb_mcp.digitalWrite(_73eb, HIGH); break;
    case 0x74: r6r7_eb_mcp.digitalWrite(_74eb, HIGH); break;
    case 0x75: r6r7_eb_mcp.digitalWrite(_75eb, HIGH); break;
    case 0x76: r6r7_eb_mcp.digitalWrite(_76eb, HIGH); break;
    case 0x77: r6r7_eb_mcp.digitalWrite(_77eb, HIGH); break;

    default:
        // Optionally handle an invalid tile value.
        break;
  }
}

/* method: changeLEDcolor
function: changes LED color for specified tile to specified color
details:
  	- This method uses nested switch statements:
      	* The outer switch identifies the board tile (ranging from 0x00 to 0x77).
      	* The inner switch selects the proper LED control commands based on the specified color.
  	- It writes to two control pins associated with the selected tile to set the LED color.
  	- Ensure that the corresponding pin variables (e.g., _00sb0, _00sb1, etc.) are correctly defined and initialized.
params:
  	- hexTile:
      	* Board is represented using the "0x88" system.
      	* Pass a char representing the tile, with valid values between 0x00 and 0x77.
      	* Examples:
        	- "a1" corresponds to 0x00 (file a = 0x0, rank 1 = 0x0)
        	- "h8" corresponds to 0x77 (file h = 0x7, rank 8 = 0x7)
  	- color:
      	* Enumeration: ['R', 'G', 'B', 'Y']
        	- 'R' - Red
        	- 'G' - Green
        	- 'B' - Blue
        	- 'Y' - Yellow
*/
void HardwareAPI::changeLEDcolor(char hexTile, char color) 
{
  switch (hexTile) {
    // Row: 0 (a1-h1)
    case 0x00:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_00sb0, LOW); r0_sb_mcp.digitalWrite(_00sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_00sb0, LOW); r0_sb_mcp.digitalWrite(_00sb1, HIGH); break;
        case 'Y': r0_sb_mcp.digitalWrite(_00sb0, HIGH); r0_sb_mcp.digitalWrite(_00sb1, LOW); break;
        case 'G': r0_sb_mcp.digitalWrite(_00sb0, HIGH); r0_sb_mcp.digitalWrite(_00sb1, HIGH); break;
      }
      break;
    case 0x01:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_01sb0, LOW); r0_sb_mcp.digitalWrite(_01sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_01sb0, LOW); r0_sb_mcp.digitalWrite(_01sb1, HIGH); break;
        case 'Y': r0_sb_mcp.digitalWrite(_01sb0, HIGH); r0_sb_mcp.digitalWrite(_01sb1, LOW); break;
        case 'G': r0_sb_mcp.digitalWrite(_01sb0, HIGH); r0_sb_mcp.digitalWrite(_01sb1, HIGH); break;
      }
      break;
    case 0x02:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_02sb0, LOW); r0_sb_mcp.digitalWrite(_02sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_02sb0, LOW); r0_sb_mcp.digitalWrite(_02sb1, HIGH); break;
        case 'Y': r0_sb_mcp.digitalWrite(_02sb0, HIGH); r0_sb_mcp.digitalWrite(_02sb1, LOW); break;
        case 'G': r0_sb_mcp.digitalWrite(_02sb0, HIGH); r0_sb_mcp.digitalWrite(_02sb1, HIGH); break;
      }
      break;
    case 0x03:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_03sb0, LOW); r0_sb_mcp.digitalWrite(_03sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_03sb0, LOW); r0_sb_mcp.digitalWrite(_03sb1, HIGH); break;
        case 'Y': r0_sb_mcp.digitalWrite(_03sb0, HIGH); r0_sb_mcp.digitalWrite(_03sb1, LOW); break;
        case 'G': r0_sb_mcp.digitalWrite(_03sb0, HIGH); r0_sb_mcp.digitalWrite(_03sb1, HIGH); break;
      }
      break;
    case 0x04:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_04sb0, LOW); r0_sb_mcp.digitalWrite(_04sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_04sb0, LOW); r0_sb_mcp.digitalWrite(_04sb1, HIGH); break;
        case 'Y': r0_sb_mcp.digitalWrite(_04sb0, HIGH); r0_sb_mcp.digitalWrite(_04sb1, LOW); break;
        case 'G': r0_sb_mcp.digitalWrite(_04sb0, HIGH); r0_sb_mcp.digitalWrite(_04sb1, HIGH); break;
      }
      break;
    case 0x05:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_05sb0, LOW); r0_sb_mcp.digitalWrite(_05sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_05sb0, LOW); r0_sb_mcp.digitalWrite(_05sb1, HIGH); break;
        case 'Y': r0_sb_mcp.digitalWrite(_05sb0, HIGH); r0_sb_mcp.digitalWrite(_05sb1, LOW); break;
        case 'G': r0_sb_mcp.digitalWrite(_05sb0, HIGH); r0_sb_mcp.digitalWrite(_05sb1, HIGH); break;
      }
      break;
    case 0x06:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_06sb0, LOW); r0_sb_mcp.digitalWrite(_06sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_06sb0, LOW); r0_sb_mcp.digitalWrite(_06sb1, HIGH); break;
        case 'Y': r0_sb_mcp.digitalWrite(_06sb0, HIGH); r0_sb_mcp.digitalWrite(_06sb1, LOW); break;
        case 'G': r0_sb_mcp.digitalWrite(_06sb0, HIGH); r0_sb_mcp.digitalWrite(_06sb1, HIGH); break;
      }
      break;
    case 0x07:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_07sb0, LOW); r0_sb_mcp.digitalWrite(_07sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_07sb0, LOW); r0_sb_mcp.digitalWrite(_07sb1, HIGH); break;
        case 'Y': r0_sb_mcp.digitalWrite(_07sb0, HIGH); r0_sb_mcp.digitalWrite(_07sb1, LOW); break;
        case 'G': r0_sb_mcp.digitalWrite(_07sb0, HIGH); r0_sb_mcp.digitalWrite(_07sb1, HIGH); break;
      }
      break;
      
    // Row: 1 (a2-h2)
    case 0x10:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_10sb0, LOW); r1_sb_mcp.digitalWrite(_10sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_10sb0, LOW); r1_sb_mcp.digitalWrite(_10sb1, HIGH); break;
        case 'Y': r1_sb_mcp.digitalWrite(_10sb0, HIGH); r1_sb_mcp.digitalWrite(_10sb1, LOW); break;
        case 'G': r1_sb_mcp.digitalWrite(_10sb0, HIGH); r1_sb_mcp.digitalWrite(_10sb1, HIGH); break;
      }
      break;
    case 0x11:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_11sb0, LOW); r1_sb_mcp.digitalWrite(_11sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_11sb0, LOW); r1_sb_mcp.digitalWrite(_11sb1, HIGH); break;
        case 'Y': r1_sb_mcp.digitalWrite(_11sb0, HIGH); r1_sb_mcp.digitalWrite(_11sb1, LOW); break;
        case 'G': r1_sb_mcp.digitalWrite(_11sb0, HIGH); r1_sb_mcp.digitalWrite(_11sb1, HIGH); break;
      }
      break;
    case 0x12:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_12sb0, LOW); r1_sb_mcp.digitalWrite(_12sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_12sb0, LOW); r1_sb_mcp.digitalWrite(_12sb1, HIGH); break;
        case 'Y': r1_sb_mcp.digitalWrite(_12sb0, HIGH); r1_sb_mcp.digitalWrite(_12sb1, LOW); break;
        case 'G': r1_sb_mcp.digitalWrite(_12sb0, HIGH); r1_sb_mcp.digitalWrite(_12sb1, HIGH); break;
      }
      break;
    case 0x13:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_13sb0, LOW); r1_sb_mcp.digitalWrite(_13sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_13sb0, LOW); r1_sb_mcp.digitalWrite(_13sb1, HIGH); break;
        case 'Y': r1_sb_mcp.digitalWrite(_13sb0, HIGH); r1_sb_mcp.digitalWrite(_13sb1, LOW); break;
        case 'G': r1_sb_mcp.digitalWrite(_13sb0, HIGH); r1_sb_mcp.digitalWrite(_13sb1, HIGH); break;
      }
      break;
    case 0x14:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_14sb0, LOW); r1_sb_mcp.digitalWrite(_14sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_14sb0, LOW); r1_sb_mcp.digitalWrite(_14sb1, HIGH); break;
        case 'Y': r1_sb_mcp.digitalWrite(_14sb0, HIGH); r1_sb_mcp.digitalWrite(_14sb1, LOW); break;
        case 'G': r1_sb_mcp.digitalWrite(_14sb0, HIGH); r1_sb_mcp.digitalWrite(_14sb1, HIGH); break;
      }
      break;
    case 0x15:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_15sb0, LOW); r1_sb_mcp.digitalWrite(_15sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_15sb0, LOW); r1_sb_mcp.digitalWrite(_15sb1, HIGH); break;
        case 'Y': r1_sb_mcp.digitalWrite(_15sb0, HIGH); r1_sb_mcp.digitalWrite(_15sb1, LOW); break;
        case 'G': r1_sb_mcp.digitalWrite(_15sb0, HIGH); r1_sb_mcp.digitalWrite(_15sb1, HIGH); break;
      }
      break;
    case 0x16:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_16sb0, LOW); r1_sb_mcp.digitalWrite(_16sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_16sb0, LOW); r1_sb_mcp.digitalWrite(_16sb1, HIGH); break;
        case 'Y': r1_sb_mcp.digitalWrite(_16sb0, HIGH); r1_sb_mcp.digitalWrite(_16sb1, LOW); break;
        case 'G': r1_sb_mcp.digitalWrite(_16sb0, HIGH); r1_sb_mcp.digitalWrite(_16sb1, HIGH); break;
      }
      break;
    case 0x17:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_17sb0, LOW); r1_sb_mcp.digitalWrite(_17sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_17sb0, LOW); r1_sb_mcp.digitalWrite(_17sb1, HIGH); break;
        case 'Y': r1_sb_mcp.digitalWrite(_17sb0, HIGH); r1_sb_mcp.digitalWrite(_17sb1, LOW); break;
        case 'G': r1_sb_mcp.digitalWrite(_17sb0, HIGH); r1_sb_mcp.digitalWrite(_17sb1, HIGH); break;
      }
      break;
      
    // Row: 2 (a3-h3)
    case 0x20:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_20sb0, LOW); r2_sb_mcp.digitalWrite(_20sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_20sb0, LOW); r2_sb_mcp.digitalWrite(_20sb1, HIGH); break;
        case 'Y': r2_sb_mcp.digitalWrite(_20sb0, HIGH); r2_sb_mcp.digitalWrite(_20sb1, LOW); break;
        case 'G': r2_sb_mcp.digitalWrite(_20sb0, HIGH); r2_sb_mcp.digitalWrite(_20sb1, HIGH); break;
      }
      break;
    case 0x21:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_21sb0, LOW); r2_sb_mcp.digitalWrite(_21sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_21sb0, LOW); r2_sb_mcp.digitalWrite(_21sb1, HIGH); break;
        case 'Y': r2_sb_mcp.digitalWrite(_21sb0, HIGH); r2_sb_mcp.digitalWrite(_21sb1, LOW); break;
        case 'G': r2_sb_mcp.digitalWrite(_21sb0, HIGH); r2_sb_mcp.digitalWrite(_21sb1, HIGH); break;
      }
      break;
    case 0x22:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_22sb0, LOW); r2_sb_mcp.digitalWrite(_22sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_22sb0, LOW); r2_sb_mcp.digitalWrite(_22sb1, HIGH); break;
        case 'Y': r2_sb_mcp.digitalWrite(_22sb0, HIGH); r2_sb_mcp.digitalWrite(_22sb1, LOW); break;
        case 'G': r2_sb_mcp.digitalWrite(_22sb0, HIGH); r2_sb_mcp.digitalWrite(_22sb1, HIGH); break;
      }
      break;
    case 0x23:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_23sb0, LOW); r2_sb_mcp.digitalWrite(_23sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_23sb0, LOW); r2_sb_mcp.digitalWrite(_23sb1, HIGH); break;
        case 'Y': r2_sb_mcp.digitalWrite(_23sb0, HIGH); r2_sb_mcp.digitalWrite(_23sb1, LOW); break;
        case 'G': r2_sb_mcp.digitalWrite(_23sb0, HIGH); r2_sb_mcp.digitalWrite(_23sb1, HIGH); break;
      }
      break;
    case 0x24:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_24sb0, LOW); r2_sb_mcp.digitalWrite(_24sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_24sb0, LOW); r2_sb_mcp.digitalWrite(_24sb1, HIGH); break;
        case 'Y': r2_sb_mcp.digitalWrite(_24sb0, HIGH); r2_sb_mcp.digitalWrite(_24sb1, LOW); break;
        case 'G': r2_sb_mcp.digitalWrite(_24sb0, HIGH); r2_sb_mcp.digitalWrite(_24sb1, HIGH); break;
      }
      break;
    case 0x25:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_25sb0, LOW); r2_sb_mcp.digitalWrite(_25sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_25sb0, LOW); r2_sb_mcp.digitalWrite(_25sb1, HIGH); break;
        case 'Y': r2_sb_mcp.digitalWrite(_25sb0, HIGH); r2_sb_mcp.digitalWrite(_25sb1, LOW); break;
        case 'G': r2_sb_mcp.digitalWrite(_25sb0, HIGH); r2_sb_mcp.digitalWrite(_25sb1, HIGH); break;
      }
      break;
    case 0x26:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_26sb0, LOW); r2_sb_mcp.digitalWrite(_26sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_26sb0, LOW); r2_sb_mcp.digitalWrite(_26sb1, HIGH); break;
        case 'Y': r2_sb_mcp.digitalWrite(_26sb0, HIGH); r2_sb_mcp.digitalWrite(_26sb1, LOW); break;
        case 'G': r2_sb_mcp.digitalWrite(_26sb0, HIGH); r2_sb_mcp.digitalWrite(_26sb1, HIGH); break;
      }
      break;
    case 0x27:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_27sb0, LOW); r2_sb_mcp.digitalWrite(_27sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_27sb0, LOW); r2_sb_mcp.digitalWrite(_27sb1, HIGH); break;
        case 'Y': r2_sb_mcp.digitalWrite(_27sb0, HIGH); r2_sb_mcp.digitalWrite(_27sb1, LOW); break;
        case 'G': r2_sb_mcp.digitalWrite(_27sb0, HIGH); r2_sb_mcp.digitalWrite(_27sb1, HIGH); break;
      }
      break;
      
    // Row: 3 (a4-h4)
    case 0x30:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_30sb0, LOW); r3_sb_mcp.digitalWrite(_30sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_30sb0, LOW); r3_sb_mcp.digitalWrite(_30sb1, HIGH); break;
        case 'Y': r3_sb_mcp.digitalWrite(_30sb0, HIGH); r3_sb_mcp.digitalWrite(_30sb1, LOW); break;
        case 'G': r3_sb_mcp.digitalWrite(_30sb0, HIGH); r3_sb_mcp.digitalWrite(_30sb1, HIGH); break;
      }
      break;
    case 0x31:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_31sb0, LOW); r3_sb_mcp.digitalWrite(_31sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_31sb0, LOW); r3_sb_mcp.digitalWrite(_31sb1, HIGH); break;
        case 'Y': r3_sb_mcp.digitalWrite(_31sb0, HIGH); r3_sb_mcp.digitalWrite(_31sb1, LOW); break;
        case 'G': r3_sb_mcp.digitalWrite(_31sb0, HIGH); r3_sb_mcp.digitalWrite(_31sb1, HIGH); break;
      }
      break;
    case 0x32:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_32sb0, LOW); r3_sb_mcp.digitalWrite(_32sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_32sb0, LOW); r3_sb_mcp.digitalWrite(_32sb1, HIGH); break;
        case 'Y': r3_sb_mcp.digitalWrite(_32sb0, HIGH); r3_sb_mcp.digitalWrite(_32sb1, LOW); break;
        case 'G': r3_sb_mcp.digitalWrite(_32sb0, HIGH); r3_sb_mcp.digitalWrite(_32sb1, HIGH); break;
      }
      break;
    case 0x33:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_33sb0, LOW); r3_sb_mcp.digitalWrite(_33sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_33sb0, LOW); r3_sb_mcp.digitalWrite(_33sb1, HIGH); break;
        case 'Y': r3_sb_mcp.digitalWrite(_33sb0, HIGH); r3_sb_mcp.digitalWrite(_33sb1, LOW); break;
        case 'G': r3_sb_mcp.digitalWrite(_33sb0, HIGH); r3_sb_mcp.digitalWrite(_33sb1, HIGH); break;
      }
      break;
    case 0x34:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_34sb0, LOW); r3_sb_mcp.digitalWrite(_34sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_34sb0, LOW); r3_sb_mcp.digitalWrite(_34sb1, HIGH); break;
        case 'Y': r3_sb_mcp.digitalWrite(_34sb0, HIGH); r3_sb_mcp.digitalWrite(_34sb1, LOW); break;
        case 'G': r3_sb_mcp.digitalWrite(_34sb0, HIGH); r3_sb_mcp.digitalWrite(_34sb1, HIGH); break;
      }
      break;
    case 0x35:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_35sb0, LOW); r3_sb_mcp.digitalWrite(_35sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_35sb0, LOW); r3_sb_mcp.digitalWrite(_35sb1, HIGH); break;
        case 'Y': r3_sb_mcp.digitalWrite(_35sb0, HIGH); r3_sb_mcp.digitalWrite(_35sb1, LOW); break;
        case 'G': r3_sb_mcp.digitalWrite(_35sb0, HIGH); r3_sb_mcp.digitalWrite(_35sb1, HIGH); break;
      }
      break;
    case 0x36:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_36sb0, LOW); r3_sb_mcp.digitalWrite(_36sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_36sb0, LOW); r3_sb_mcp.digitalWrite(_36sb1, HIGH); break;
        case 'Y': r3_sb_mcp.digitalWrite(_36sb0, HIGH); r3_sb_mcp.digitalWrite(_36sb1, LOW); break;
        case 'G': r3_sb_mcp.digitalWrite(_36sb0, HIGH); r3_sb_mcp.digitalWrite(_36sb1, HIGH); break;
      }
      break;
    case 0x37:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_37sb0, LOW); r3_sb_mcp.digitalWrite(_37sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_37sb0, LOW); r3_sb_mcp.digitalWrite(_37sb1, HIGH); break;
        case 'Y': r3_sb_mcp.digitalWrite(_37sb0, HIGH); r3_sb_mcp.digitalWrite(_37sb1, LOW); break;
        case 'G': r3_sb_mcp.digitalWrite(_37sb0, HIGH); r3_sb_mcp.digitalWrite(_37sb1, HIGH); break;
      }
      break;
      
    // Row: 4 (a5-h5)
    case 0x40:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_40sb0, LOW); r4_sb_mcp.digitalWrite(_40sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_40sb0, LOW); r4_sb_mcp.digitalWrite(_40sb1, HIGH); break;
        case 'Y': r4_sb_mcp.digitalWrite(_40sb0, HIGH); r4_sb_mcp.digitalWrite(_40sb1, LOW); break;
        case 'G': r4_sb_mcp.digitalWrite(_40sb0, HIGH); r4_sb_mcp.digitalWrite(_40sb1, HIGH); break;
      }
      break;
    case 0x41:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_41sb0, LOW); r4_sb_mcp.digitalWrite(_41sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_41sb0, LOW); r4_sb_mcp.digitalWrite(_41sb1, HIGH); break;
        case 'Y': r4_sb_mcp.digitalWrite(_41sb0, HIGH); r4_sb_mcp.digitalWrite(_41sb1, LOW); break;
        case 'G': r4_sb_mcp.digitalWrite(_41sb0, HIGH); r4_sb_mcp.digitalWrite(_41sb1, HIGH); break;
      }
      break;
    case 0x42:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_42sb0, LOW); r4_sb_mcp.digitalWrite(_42sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_42sb0, LOW); r4_sb_mcp.digitalWrite(_42sb1, HIGH); break;
        case 'Y': r4_sb_mcp.digitalWrite(_42sb0, HIGH); r4_sb_mcp.digitalWrite(_42sb1, LOW); break;
        case 'G': r4_sb_mcp.digitalWrite(_42sb0, HIGH); r4_sb_mcp.digitalWrite(_42sb1, HIGH); break;
      }
      break;
    case 0x43:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_43sb0, LOW); r4_sb_mcp.digitalWrite(_43sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_43sb0, LOW); r4_sb_mcp.digitalWrite(_43sb1, HIGH); break;
        case 'Y': r4_sb_mcp.digitalWrite(_43sb0, HIGH); r4_sb_mcp.digitalWrite(_43sb1, LOW); break;
        case 'G': r4_sb_mcp.digitalWrite(_43sb0, HIGH); r4_sb_mcp.digitalWrite(_43sb1, HIGH); break;
      }
      break;
    case 0x44:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_44sb0, LOW); r4_sb_mcp.digitalWrite(_44sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_44sb0, LOW); r4_sb_mcp.digitalWrite(_44sb1, HIGH); break;
        case 'Y': r4_sb_mcp.digitalWrite(_44sb0, HIGH); r4_sb_mcp.digitalWrite(_44sb1, LOW); break;
        case 'G': r4_sb_mcp.digitalWrite(_44sb0, HIGH); r4_sb_mcp.digitalWrite(_44sb1, HIGH); break;
      }
      break;
    case 0x45:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_45sb0, LOW); r4_sb_mcp.digitalWrite(_45sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_45sb0, LOW); r4_sb_mcp.digitalWrite(_45sb1, HIGH); break;
        case 'Y': r4_sb_mcp.digitalWrite(_45sb0, HIGH); r4_sb_mcp.digitalWrite(_45sb1, LOW); break;
        case 'G': r4_sb_mcp.digitalWrite(_45sb0, HIGH); r4_sb_mcp.digitalWrite(_45sb1, HIGH); break;
      }
      break;
    case 0x46:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_46sb0, LOW); r4_sb_mcp.digitalWrite(_46sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_46sb0, LOW); r4_sb_mcp.digitalWrite(_46sb1, HIGH); break;
        case 'Y': r4_sb_mcp.digitalWrite(_46sb0, HIGH); r4_sb_mcp.digitalWrite(_46sb1, LOW); break;
        case 'G': r4_sb_mcp.digitalWrite(_46sb0, HIGH); r4_sb_mcp.digitalWrite(_46sb1, HIGH); break;
      }
      break;
    case 0x47:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_47sb0, LOW); r4_sb_mcp.digitalWrite(_47sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_47sb0, LOW); r4_sb_mcp.digitalWrite(_47sb1, HIGH); break;
        case 'Y': r4_sb_mcp.digitalWrite(_47sb0, HIGH); r4_sb_mcp.digitalWrite(_47sb1, LOW); break;
        case 'G': r4_sb_mcp.digitalWrite(_47sb0, HIGH); r4_sb_mcp.digitalWrite(_47sb1, HIGH); break;
      }
      break;
      
    // Row: 5 (a6-h6)
    case 0x50:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_50sb0, LOW); r5_sb_mcp.digitalWrite(_50sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_50sb0, LOW); r5_sb_mcp.digitalWrite(_50sb1, HIGH); break;
        case 'Y': r5_sb_mcp.digitalWrite(_50sb0, HIGH); r5_sb_mcp.digitalWrite(_50sb1, LOW); break;
        case 'G': r5_sb_mcp.digitalWrite(_50sb0, HIGH); r5_sb_mcp.digitalWrite(_50sb1, HIGH); break;
      }
      break;
    case 0x51:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_51sb0, LOW); r5_sb_mcp.digitalWrite(_51sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_51sb0, LOW); r5_sb_mcp.digitalWrite(_51sb1, HIGH); break;
        case 'Y': r5_sb_mcp.digitalWrite(_51sb0, HIGH); r5_sb_mcp.digitalWrite(_51sb1, LOW); break;
        case 'G': r5_sb_mcp.digitalWrite(_51sb0, HIGH); r5_sb_mcp.digitalWrite(_51sb1, HIGH); break;
      }
      break;
    case 0x52:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_52sb0, LOW); r5_sb_mcp.digitalWrite(_52sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_52sb0, LOW); r5_sb_mcp.digitalWrite(_52sb1, HIGH); break;
        case 'Y': r5_sb_mcp.digitalWrite(_52sb0, HIGH); r5_sb_mcp.digitalWrite(_52sb1, LOW); break;
        case 'G': r5_sb_mcp.digitalWrite(_52sb0, HIGH); r5_sb_mcp.digitalWrite(_52sb1, HIGH); break;
      }
      break;
    case 0x53:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_53sb0, LOW); r5_sb_mcp.digitalWrite(_53sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_53sb0, LOW); r5_sb_mcp.digitalWrite(_53sb1, HIGH); break;
        case 'Y': r5_sb_mcp.digitalWrite(_53sb0, HIGH); r5_sb_mcp.digitalWrite(_53sb1, LOW); break;
        case 'G': r5_sb_mcp.digitalWrite(_53sb0, HIGH); r5_sb_mcp.digitalWrite(_53sb1, HIGH); break;
      }
      break;
    case 0x54:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_54sb0, LOW); r5_sb_mcp.digitalWrite(_54sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_54sb0, LOW); r5_sb_mcp.digitalWrite(_54sb1, HIGH); break;
        case 'Y': r5_sb_mcp.digitalWrite(_54sb0, HIGH); r5_sb_mcp.digitalWrite(_54sb1, LOW); break;
        case 'G': r5_sb_mcp.digitalWrite(_54sb0, HIGH); r5_sb_mcp.digitalWrite(_54sb1, HIGH); break;
      }
      break;
    case 0x55:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_55sb0, LOW); r5_sb_mcp.digitalWrite(_55sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_55sb0, LOW); r5_sb_mcp.digitalWrite(_55sb1, HIGH); break;
        case 'Y': r5_sb_mcp.digitalWrite(_55sb0, HIGH); r5_sb_mcp.digitalWrite(_55sb1, LOW); break;
        case 'G': r5_sb_mcp.digitalWrite(_55sb0, HIGH); r5_sb_mcp.digitalWrite(_55sb1, HIGH); break;
      }
      break;
    case 0x56:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_56sb0, LOW); r5_sb_mcp.digitalWrite(_56sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_56sb0, LOW); r5_sb_mcp.digitalWrite(_56sb1, HIGH); break;
        case 'Y': r5_sb_mcp.digitalWrite(_56sb0, HIGH); r5_sb_mcp.digitalWrite(_56sb1, LOW); break;
        case 'G': r5_sb_mcp.digitalWrite(_56sb0, HIGH); r5_sb_mcp.digitalWrite(_56sb1, HIGH); break;
      }
      break;
    case 0x57:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_57sb0, LOW); r5_sb_mcp.digitalWrite(_57sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_57sb0, LOW); r5_sb_mcp.digitalWrite(_57sb1, HIGH); break;
        case 'Y': r5_sb_mcp.digitalWrite(_57sb0, HIGH); r5_sb_mcp.digitalWrite(_57sb1, LOW); break;
        case 'G': r5_sb_mcp.digitalWrite(_57sb0, HIGH); r5_sb_mcp.digitalWrite(_57sb1, HIGH); break;
      }
      break;
      
    // Row: 6 (a7-h7)
    case 0x60:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_60sb0, LOW); r6_sb_mcp.digitalWrite(_60sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_60sb0, LOW); r6_sb_mcp.digitalWrite(_60sb1, HIGH); break;
        case 'Y': r6_sb_mcp.digitalWrite(_60sb0, HIGH); r6_sb_mcp.digitalWrite(_60sb1, LOW); break;
        case 'G': r6_sb_mcp.digitalWrite(_60sb0, HIGH); r6_sb_mcp.digitalWrite(_60sb1, HIGH); break;
      }
      break;
    case 0x61:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_61sb0, LOW); r6_sb_mcp.digitalWrite(_61sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_61sb0, LOW); r6_sb_mcp.digitalWrite(_61sb1, HIGH); break;
        case 'Y': r6_sb_mcp.digitalWrite(_61sb0, HIGH); r6_sb_mcp.digitalWrite(_61sb1, LOW); break;
        case 'G': r6_sb_mcp.digitalWrite(_61sb0, HIGH); r6_sb_mcp.digitalWrite(_61sb1, HIGH); break;
      }
      break;
    case 0x62:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_62sb0, LOW); r6_sb_mcp.digitalWrite(_62sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_62sb0, LOW); r6_sb_mcp.digitalWrite(_62sb1, HIGH); break;
        case 'Y': r6_sb_mcp.digitalWrite(_62sb0, HIGH); r6_sb_mcp.digitalWrite(_62sb1, LOW); break;
        case 'G': r6_sb_mcp.digitalWrite(_62sb0, HIGH); r6_sb_mcp.digitalWrite(_62sb1, HIGH); break;
      }
      break;
    case 0x63:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_63sb0, LOW); r6_sb_mcp.digitalWrite(_63sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_63sb0, LOW); r6_sb_mcp.digitalWrite(_63sb1, HIGH); break;
        case 'Y': r6_sb_mcp.digitalWrite(_63sb0, HIGH); r6_sb_mcp.digitalWrite(_63sb1, LOW); break;
        case 'G': r6_sb_mcp.digitalWrite(_63sb0, HIGH); r6_sb_mcp.digitalWrite(_63sb1, HIGH); break;
      }
      break;
    case 0x64:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_64sb0, LOW); r6_sb_mcp.digitalWrite(_64sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_64sb0, LOW); r6_sb_mcp.digitalWrite(_64sb1, HIGH); break;
        case 'Y': r6_sb_mcp.digitalWrite(_64sb0, HIGH); r6_sb_mcp.digitalWrite(_64sb1, LOW); break;
        case 'G': r6_sb_mcp.digitalWrite(_64sb0, HIGH); r6_sb_mcp.digitalWrite(_64sb1, HIGH); break;
      }
      break;
    case 0x65:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_65sb0, LOW); r6_sb_mcp.digitalWrite(_65sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_65sb0, LOW); r6_sb_mcp.digitalWrite(_65sb1, HIGH); break;
        case 'Y': r6_sb_mcp.digitalWrite(_65sb0, HIGH); r6_sb_mcp.digitalWrite(_65sb1, LOW); break;
        case 'G': r6_sb_mcp.digitalWrite(_65sb0, HIGH); r6_sb_mcp.digitalWrite(_65sb1, HIGH); break;
      }
      break;
    case 0x66:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_66sb0, LOW); r6_sb_mcp.digitalWrite(_66sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_66sb0, LOW); r6_sb_mcp.digitalWrite(_66sb1, HIGH); break;
        case 'Y': r6_sb_mcp.digitalWrite(_66sb0, HIGH); r6_sb_mcp.digitalWrite(_66sb1, LOW); break;
        case 'G': r6_sb_mcp.digitalWrite(_66sb0, HIGH); r6_sb_mcp.digitalWrite(_66sb1, HIGH); break;
      }
      break;
    case 0x67:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_67sb0, LOW); r6_sb_mcp.digitalWrite(_67sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_67sb0, LOW); r6_sb_mcp.digitalWrite(_67sb1, HIGH); break;
        case 'Y': r6_sb_mcp.digitalWrite(_67sb0, HIGH); r6_sb_mcp.digitalWrite(_67sb1, LOW); break;
        case 'G': r6_sb_mcp.digitalWrite(_67sb0, HIGH); r6_sb_mcp.digitalWrite(_67sb1, HIGH); break;
      }
      break;
      
    // Row: 7 (a8-h8)
    case 0x70:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_70sb0, LOW); r7_sb_mcp.digitalWrite(_70sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_70sb0, LOW); r7_sb_mcp.digitalWrite(_70sb1, HIGH); break;
        case 'Y': r7_sb_mcp.digitalWrite(_70sb0, HIGH); r7_sb_mcp.digitalWrite(_70sb1, LOW); break;
        case 'G': r7_sb_mcp.digitalWrite(_70sb0, HIGH); r7_sb_mcp.digitalWrite(_70sb1, HIGH); break;
      }
      break;
    case 0x71:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_71sb0, LOW); r7_sb_mcp.digitalWrite(_71sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_71sb0, LOW); r7_sb_mcp.digitalWrite(_71sb1, HIGH); break;
        case 'Y': r7_sb_mcp.digitalWrite(_71sb0, HIGH); r7_sb_mcp.digitalWrite(_71sb1, LOW); break;
        case 'G': r7_sb_mcp.digitalWrite(_71sb0, HIGH); r7_sb_mcp.digitalWrite(_71sb1, HIGH); break;
      }
      break;
    case 0x72:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_72sb0, LOW); r7_sb_mcp.digitalWrite(_72sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_72sb0, LOW); r7_sb_mcp.digitalWrite(_72sb1, HIGH); break;
        case 'Y': r7_sb_mcp.digitalWrite(_72sb0, HIGH); r7_sb_mcp.digitalWrite(_72sb1, LOW); break;
        case 'G': r7_sb_mcp.digitalWrite(_72sb0, HIGH); r7_sb_mcp.digitalWrite(_72sb1, HIGH); break;
      }
      break;
    case 0x73:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_73sb0, LOW); r7_sb_mcp.digitalWrite(_73sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_73sb0, LOW); r7_sb_mcp.digitalWrite(_73sb1, HIGH); break;
        case 'Y': r7_sb_mcp.digitalWrite(_73sb0, HIGH); r7_sb_mcp.digitalWrite(_73sb1, LOW); break;
        case 'G': r7_sb_mcp.digitalWrite(_73sb0, HIGH); r7_sb_mcp.digitalWrite(_73sb1, HIGH); break;
      }
      break;
    case 0x74:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_74sb0, LOW); r7_sb_mcp.digitalWrite(_74sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_74sb0, LOW); r7_sb_mcp.digitalWrite(_74sb1, HIGH); break;
        case 'Y': r7_sb_mcp.digitalWrite(_74sb0, HIGH); r7_sb_mcp.digitalWrite(_74sb1, LOW); break;
        case 'G': r7_sb_mcp.digitalWrite(_74sb0, HIGH); r7_sb_mcp.digitalWrite(_74sb1, HIGH); break;
      }
      break;
    case 0x75:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_75sb0, LOW); r7_sb_mcp.digitalWrite(_75sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_75sb0, LOW); r7_sb_mcp.digitalWrite(_75sb1, HIGH); break;
        case 'Y': r7_sb_mcp.digitalWrite(_75sb0, HIGH); r7_sb_mcp.digitalWrite(_75sb1, LOW); break;
        case 'G': r7_sb_mcp.digitalWrite(_75sb0, HIGH); r7_sb_mcp.digitalWrite(_75sb1, HIGH); break;
      }
      break;
    case 0x76:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_76sb0, LOW); r7_sb_mcp.digitalWrite(_76sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_76sb0, LOW); r7_sb_mcp.digitalWrite(_76sb1, HIGH); break;
        case 'Y': r7_sb_mcp.digitalWrite(_76sb0, HIGH); r7_sb_mcp.digitalWrite(_76sb1, LOW); break;
        case 'G': r7_sb_mcp.digitalWrite(_76sb0, HIGH); r7_sb_mcp.digitalWrite(_76sb1, HIGH); break;
      }
      break;
    case 0x77:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_77sb0, LOW); r7_sb_mcp.digitalWrite(_77sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_77sb0, LOW); r7_sb_mcp.digitalWrite(_77sb1, HIGH); break;
        case 'Y': r7_sb_mcp.digitalWrite(_77sb0, HIGH); r7_sb_mcp.digitalWrite(_77sb1, LOW); break;
        case 'G': r7_sb_mcp.digitalWrite(_77sb0, HIGH); r7_sb_mcp.digitalWrite(_77sb1, HIGH); break;
      }
      break;
      
    default:
      // Optionally handle an invalid tile value.
      break;
  }
}

/* method: PrintLCD
function: Prints text to both lines of the LCD.
params:
  	- c1: A character array to be printed on the first line of the LCD.
  	- c2: A character array to be printed on the second line of the LCD.
*/
void HardwareAPI::PrintLCD(const char c1[], const char c2[]) 
{
  ClearLCD();
  lcd.setCursor(0, 0);
  lcd.print(c1);
  lcd.setCursor(0, 1);
  lcd.print(c2);
}

/* method: PrintLCDL1
function: Prints text to the first line of the LCD.
params:
  	- str: A character array to be printed on the first line of the LCD.
*/
void HardwareAPI::PrintLCDL1(const char str[]) 
{
  ClearLCDL1();
  lcd.setCursor(0, 0);
  lcd.print(str);
}

/* method: PrintLCDL2
function: Prints text to the second line of the LCD.
params:
 	- str: A character array to be printed on the first line of the LCD.
*/
void HardwareAPI::PrintLCDL2(const char str[]) 
{
  ClearLCDL2();
  lcd.setCursor(0, 1);
  lcd.print(str);
}    
  
/* method: ClearLCD
function: Clears the entire LCD display.
details:
  - Removes any text from both the first and second lines of the LCD by printing 16 spaces to both lines of the LCD.
*/
void HardwareAPI::ClearLCD() 
{
  ClearLCDL1();
  ClearLCDL2();
}

/* method: ClearLCDL1
function: Clears the first line of the LCD.
details:
  - Removes any text from the first line of the LCD by printing 16 spaces.
*/
void HardwareAPI::ClearLCDL1() 
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
}

/* method: ClearLCDL2
function: Clears the second line of the LCD.
details:
  - Removes any text from the second line of the LCD by printing 16 spaces.
*/
void HardwareAPI::ClearLCDL2() 
{
  lcd.setCursor(0, 1);
  lcd.print("                ");
}