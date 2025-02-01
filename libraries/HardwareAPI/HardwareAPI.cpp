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
HardwareAPI::HardwareAPI()
{	
	
    // Row 0 (0x00 - 0x07)
    _00sb0 = 26; 
    _00sb1 = 28;
    _00eb  = 24;
    _01sb0 = 0;  
    _01sb1 = 0;
    _01eb  = 0;
    _02sb0 = 0;  
    _02sb1 = 0;
    _02eb  = 0;
    _03sb0 = 0;  
    _03sb1 = 0;
    _03eb  = 0;
    _04sb0 = 0;  
    _04sb1 = 0;
    _04eb  = 0;
    _05sb0 = 0;  
    _05sb1 = 0;
    _05eb  = 0;
    _06sb0 = 0;  
    _06sb1 = 0;
    _06eb  = 0;
    _07sb0 = 0;  
    _07sb1 = 0;
    _07eb  = 0;

    // Row 1 (0x10 - 0x17)
    _10sb0 = 0;  
    _10sb1 = 0;
    _10eb  = 0;
    _11sb0 = 0;  
    _11sb1 = 0;
    _11eb  = 0;
    _12sb0 = 0;  
    _12sb1 = 0;
    _12eb  = 0;
    _13sb0 = 0;  
    _13sb1 = 0;
    _13eb  = 0;
    _14sb0 = 0;  
    _14sb1 = 0;
    _14eb  = 0;
    _15sb0 = 0;  
    _15sb1 = 0;
    _15eb  = 0;
    _16sb0 = 0;  
    _16sb1 = 0;
    _16eb  = 0;
    _17sb0 = 0;  
    _17sb1 = 0;
    _17eb  = 0;

    // Row 2 (0x20 - 0x27)
    _20sb0 = 0;  
    _20sb1 = 0;
    _20eb  = 0;
    _21sb0 = 0;  
    _21sb1 = 0;
    _21eb  = 0;
    _22sb0 = 0;  
    _22sb1 = 0;
    _22eb  = 0;
    _23sb0 = 0;  
    _23sb1 = 0;
    _23eb  = 0;
    _24sb0 = 0;  
    _24sb1 = 0;
    _24eb  = 0;
    _25sb0 = 0;  
    _25sb1 = 0;
    _25eb  = 0;
    _26sb0 = 0;  
    _26sb1 = 0;
    _26eb  = 0;
    _27sb0 = 0;  
    _27sb1 = 0;
    _27eb  = 0;

    // Row 3 (0x30 - 0x37)
    _30sb0 = 0;  
    _30sb1 = 0;
    _30eb  = 0;
    _31sb0 = 0;  
    _31sb1 = 0;
    _31eb  = 0;
    _32sb0 = 0;  
    _32sb1 = 0;
    _32eb  = 0;
    _33sb0 = 0;  
    _33sb1 = 0;
    _33eb  = 0;
    _34sb0 = 0;  
    _34sb1 = 0;
    _34eb  = 0;
    _35sb0 = 0;  
    _35sb1 = 0;
    _35eb  = 0;
    _36sb0 = 0;  
    _36sb1 = 0;
    _36eb  = 0;
    _37sb0 = 0;  
    _37sb1 = 0;
    _37eb  = 0;

    // Row 4 (0x40 - 0x47)
    _40sb0 = 0;  
    _40sb1 = 0;
    _40eb  = 0;
    _41sb0 = 0;  
    _41sb1 = 0;
    _41eb  = 0;
    _42sb0 = 0;  
    _42sb1 = 0;
    _42eb  = 0;
    _43sb0 = 0;  
    _43sb1 = 0;
    _43eb  = 0;
    _44sb0 = 0;  
    _44sb1 = 0;
    _44eb  = 0;
    _45sb0 = 0;  
    _45sb1 = 0;
    _45eb  = 0;
    _46sb0 = 0;  
    _46sb1 = 0;
    _46eb  = 0;
    _47sb0 = 0;  
    _47sb1 = 0;
    _47eb  = 0;

    // Row 5 (0x50 - 0x57)
    _50sb0 = 0;  
    _50sb1 = 0;
    _50eb  = 0;
    _51sb0 = 0;  
    _51sb1 = 0;
    _51eb  = 0;
    _52sb0 = 0;  
    _52sb1 = 0;
    _52eb  = 0;
    _53sb0 = 0;  
    _53sb1 = 0;
    _53eb  = 0;
    _54sb0 = 0;  
    _54sb1 = 0;
    _54eb  = 0;
    _55sb0 = 0;  
    _55sb1 = 0;
    _55eb  = 0;
    _56sb0 = 0;  
    _56sb1 = 0;
    _56eb  = 0;
    _57sb0 = 0;  
    _57sb1 = 0;
    _57eb  = 0;

    // Row 6 (0x60 - 0x67)
    _60sb0 = 0;  
    _60sb1 = 0;
    _60eb  = 0;
    _61sb0 = 0;  
    _61sb1 = 0;
    _61eb  = 0;
    _62sb0 = 0;  
    _62sb1 = 0;
    _62eb  = 0;
    _63sb0 = 0;  
    _63sb1 = 0;
    _63eb  = 0;
    _64sb0 = 0;  
    _64sb1 = 0;
    _64eb  = 0;
    _65sb0 = 0;  
    _65sb1 = 0;
    _65eb  = 0;
    _66sb0 = 0;  
    _66sb1 = 0;
    _66eb  = 0;
    _67sb0 = 0;  
    _67sb1 = 0;
    _67eb  = 0;

    // Row 7 (0x70 - 0x77)
    _70sb0 = 0;  
    _70sb1 = 0;
    _70eb  = 0;
    _71sb0 = 0;  
    _71sb1 = 0;
    _71eb  = 0;
    _72sb0 = 0;  
    _72sb1 = 0;
    _72eb  = 0;
    _73sb0 = 0;  
    _73sb1 = 0;
    _73eb  = 0;
    _74sb0 = 0;  
    _74sb1 = 0;
    _74eb  = 0;
    _75sb0 = 0;  
    _75sb1 = 0;
    _75eb  = 0;
    _76sb0 = 0;  
    _76sb1 = 0;
    _76eb  = 0;
    _77sb0 = 0;  
    _77sb1 = 0;
    _77eb  = 0;
}

/*
method: begin
function: Initializes the hardware.
details:
	- Initializes the LCD display (assumed to be 16 columns by 2 rows).
  	- Sets up the pin modes for all 64 LED tiles (both LED control pins and enable bits).
*/
void HardwareAPI::begin() 
{  
	//start up the lcd
    lcd.begin(16, 2);

    // Set pin modes for Row 0 (0x00 - 0x07)
    pinMode(_00sb0, OUTPUT);
    pinMode(_00sb1, OUTPUT);
    pinMode(_00eb, OUTPUT);
    pinMode(_01sb0, OUTPUT);
    pinMode(_01sb1, OUTPUT);
    pinMode(_01eb, OUTPUT);
    pinMode(_02sb0, OUTPUT);
    pinMode(_02sb1, OUTPUT);
    pinMode(_02eb, OUTPUT);
    pinMode(_03sb0, OUTPUT);
    pinMode(_03sb1, OUTPUT);
    pinMode(_03eb, OUTPUT);
    pinMode(_04sb0, OUTPUT);
    pinMode(_04sb1, OUTPUT);
    pinMode(_04eb, OUTPUT);
    pinMode(_05sb0, OUTPUT);
    pinMode(_05sb1, OUTPUT);
    pinMode(_05eb, OUTPUT);
    pinMode(_06sb0, OUTPUT);
    pinMode(_06sb1, OUTPUT);
    pinMode(_06eb, OUTPUT);
    pinMode(_07sb0, OUTPUT);
    pinMode(_07sb1, OUTPUT);
    pinMode(_07eb, OUTPUT);

    // Set pin modes for Row 1 (0x10 - 0x17)
    pinMode(_10sb0, OUTPUT);
    pinMode(_10sb1, OUTPUT);
    pinMode(_10eb, OUTPUT);
    pinMode(_11sb0, OUTPUT);
    pinMode(_11sb1, OUTPUT);
    pinMode(_11eb, OUTPUT);
    pinMode(_12sb0, OUTPUT);
    pinMode(_12sb1, OUTPUT);
    pinMode(_12eb, OUTPUT);
    pinMode(_13sb0, OUTPUT);
    pinMode(_13sb1, OUTPUT);
    pinMode(_13eb, OUTPUT);
    pinMode(_14sb0, OUTPUT);
    pinMode(_14sb1, OUTPUT);
    pinMode(_14eb, OUTPUT);
    pinMode(_15sb0, OUTPUT);
    pinMode(_15sb1, OUTPUT);
    pinMode(_15eb, OUTPUT);
    pinMode(_16sb0, OUTPUT);
    pinMode(_16sb1, OUTPUT);
    pinMode(_16eb, OUTPUT);
    pinMode(_17sb0, OUTPUT);
    pinMode(_17sb1, OUTPUT);
    pinMode(_17eb, OUTPUT);

    // Set pin modes for Row 2 (0x20 - 0x27)
    pinMode(_20sb0, OUTPUT);
    pinMode(_20sb1, OUTPUT);
    pinMode(_20eb, OUTPUT);
    pinMode(_21sb0, OUTPUT);
    pinMode(_21sb1, OUTPUT);
    pinMode(_21eb, OUTPUT);
    pinMode(_22sb0, OUTPUT);
    pinMode(_22sb1, OUTPUT);
    pinMode(_22eb, OUTPUT);
    pinMode(_23sb0, OUTPUT);
    pinMode(_23sb1, OUTPUT);
    pinMode(_23eb, OUTPUT);
    pinMode(_24sb0, OUTPUT);
    pinMode(_24sb1, OUTPUT);
    pinMode(_24eb, OUTPUT);
    pinMode(_25sb0, OUTPUT);
    pinMode(_25sb1, OUTPUT);
    pinMode(_25eb, OUTPUT);
    pinMode(_26sb0, OUTPUT);
    pinMode(_26sb1, OUTPUT);
    pinMode(_26eb, OUTPUT);
    pinMode(_27sb0, OUTPUT);
    pinMode(_27sb1, OUTPUT);
    pinMode(_27eb, OUTPUT);

    // Set pin modes for Row 3 (0x30 - 0x37)
    pinMode(_30sb0, OUTPUT);
    pinMode(_30sb1, OUTPUT);
    pinMode(_30eb, OUTPUT);
    pinMode(_31sb0, OUTPUT);
    pinMode(_31sb1, OUTPUT);
    pinMode(_31eb, OUTPUT);
    pinMode(_32sb0, OUTPUT);
    pinMode(_32sb1, OUTPUT);
    pinMode(_32eb, OUTPUT);
    pinMode(_33sb0, OUTPUT);
    pinMode(_33sb1, OUTPUT);
    pinMode(_33eb, OUTPUT);
    pinMode(_34sb0, OUTPUT);
    pinMode(_34sb1, OUTPUT);
    pinMode(_34eb, OUTPUT);
    pinMode(_35sb0, OUTPUT);
    pinMode(_35sb1, OUTPUT);
    pinMode(_35eb, OUTPUT);
    pinMode(_36sb0, OUTPUT);
    pinMode(_36sb1, OUTPUT);
    pinMode(_36eb, OUTPUT);
    pinMode(_37sb0, OUTPUT);
    pinMode(_37sb1, OUTPUT);
    pinMode(_37eb, OUTPUT);

    // Set pin modes for Row 4 (0x40 - 0x47)
    pinMode(_40sb0, OUTPUT);
    pinMode(_40sb1, OUTPUT);
    pinMode(_40eb, OUTPUT);
    pinMode(_41sb0, OUTPUT);
    pinMode(_41sb1, OUTPUT);
    pinMode(_41eb, OUTPUT);
    pinMode(_42sb0, OUTPUT);
    pinMode(_42sb1, OUTPUT);
    pinMode(_42eb, OUTPUT);
    pinMode(_43sb0, OUTPUT);
    pinMode(_43sb1, OUTPUT);
    pinMode(_43eb, OUTPUT);
    pinMode(_44sb0, OUTPUT);
    pinMode(_44sb1, OUTPUT);
    pinMode(_44eb, OUTPUT);
    pinMode(_45sb0, OUTPUT);
    pinMode(_45sb1, OUTPUT);
    pinMode(_45eb, OUTPUT);
    pinMode(_46sb0, OUTPUT);
    pinMode(_46sb1, OUTPUT);
    pinMode(_46eb, OUTPUT);
    pinMode(_47sb0, OUTPUT);
    pinMode(_47sb1, OUTPUT);
    pinMode(_47eb, OUTPUT);

    // Set pin modes for Row 5 (0x50 - 0x57)
    pinMode(_50sb0, OUTPUT);
    pinMode(_50sb1, OUTPUT);
    pinMode(_50eb, OUTPUT);
    pinMode(_51sb0, OUTPUT);
    pinMode(_51sb1, OUTPUT);
    pinMode(_51eb, OUTPUT);
    pinMode(_52sb0, OUTPUT);
    pinMode(_52sb1, OUTPUT);
    pinMode(_52eb, OUTPUT);
    pinMode(_53sb0, OUTPUT);
    pinMode(_53sb1, OUTPUT);
    pinMode(_53eb, OUTPUT);
    pinMode(_54sb0, OUTPUT);
    pinMode(_54sb1, OUTPUT);
    pinMode(_54eb, OUTPUT);
    pinMode(_55sb0, OUTPUT);
    pinMode(_55sb1, OUTPUT);
    pinMode(_55eb, OUTPUT);
    pinMode(_56sb0, OUTPUT);
    pinMode(_56sb1, OUTPUT);
    pinMode(_56eb, OUTPUT);
    pinMode(_57sb0, OUTPUT);
    pinMode(_57sb1, OUTPUT);
    pinMode(_57eb, OUTPUT);

    // Set pin modes for Row 6 (0x60 - 0x67)
    pinMode(_60sb0, OUTPUT);
    pinMode(_60sb1, OUTPUT);
    pinMode(_60eb, OUTPUT);
    pinMode(_61sb0, OUTPUT);
    pinMode(_61sb1, OUTPUT);
    pinMode(_61eb, OUTPUT);
    pinMode(_62sb0, OUTPUT);
    pinMode(_62sb1, OUTPUT);
    pinMode(_62eb, OUTPUT);
    pinMode(_63sb0, OUTPUT);
    pinMode(_63sb1, OUTPUT);
    pinMode(_63eb, OUTPUT);
    pinMode(_64sb0, OUTPUT);
    pinMode(_64sb1, OUTPUT);
    pinMode(_64eb, OUTPUT);
    pinMode(_65sb0, OUTPUT);
    pinMode(_65sb1, OUTPUT);
    pinMode(_65eb, OUTPUT);
    pinMode(_66sb0, OUTPUT);
    pinMode(_66sb1, OUTPUT);
    pinMode(_66eb, OUTPUT);
    pinMode(_67sb0, OUTPUT);
    pinMode(_67sb1, OUTPUT);
    pinMode(_67eb, OUTPUT);

    // Set pin modes for Row 7 (0x70 - 0x77)
    pinMode(_70sb0, OUTPUT);
    pinMode(_70sb1, OUTPUT);
    pinMode(_70eb, OUTPUT);
    pinMode(_71sb0, OUTPUT);
    pinMode(_71sb1, OUTPUT);
    pinMode(_71eb, OUTPUT);
    pinMode(_72sb0, OUTPUT);
    pinMode(_72sb1, OUTPUT);
    pinMode(_72eb, OUTPUT);
    pinMode(_73sb0, OUTPUT);
    pinMode(_73sb1, OUTPUT);
    pinMode(_73eb, OUTPUT);
    pinMode(_74sb0, OUTPUT);
    pinMode(_74sb1, OUTPUT);
    pinMode(_74eb, OUTPUT);
    pinMode(_75sb0, OUTPUT);
    pinMode(_75sb1, OUTPUT);
    pinMode(_75eb, OUTPUT);
    pinMode(_76sb0, OUTPUT);
    pinMode(_76sb1, OUTPUT);
    pinMode(_76eb, OUTPUT);
    pinMode(_77sb0, OUTPUT);
    pinMode(_77sb1, OUTPUT);
    pinMode(_77eb, OUTPUT);


}

/*
method: turnOnLED
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
        case 0x00: digitalWrite(_00eb, LOW); break;
        case 0x01: digitalWrite(_01eb, LOW); break;
        case 0x02: digitalWrite(_02eb, LOW); break;
        case 0x03: digitalWrite(_03eb, LOW); break;
        case 0x04: digitalWrite(_04eb, LOW); break;
        case 0x05: digitalWrite(_05eb, LOW); break;
        case 0x06: digitalWrite(_06eb, LOW); break;
        case 0x07: digitalWrite(_07eb, LOW); break;

        // Row 1 (0x10 - 0x17)
        case 0x10: digitalWrite(_10eb, LOW); break;
        case 0x11: digitalWrite(_11eb, LOW); break;
        case 0x12: digitalWrite(_12eb, LOW); break;
        case 0x13: digitalWrite(_13eb, LOW); break;
        case 0x14: digitalWrite(_14eb, LOW); break;
        case 0x15: digitalWrite(_15eb, LOW); break;
        case 0x16: digitalWrite(_16eb, LOW); break;
        case 0x17: digitalWrite(_17eb, LOW); break;

        // Row 2 (0x20 - 0x27)
        case 0x20: digitalWrite(_20eb, LOW); break;
        case 0x21: digitalWrite(_21eb, LOW); break;
        case 0x22: digitalWrite(_22eb, LOW); break;
        case 0x23: digitalWrite(_23eb, LOW); break;
        case 0x24: digitalWrite(_24eb, LOW); break;
        case 0x25: digitalWrite(_25eb, LOW); break;
        case 0x26: digitalWrite(_26eb, LOW); break;
        case 0x27: digitalWrite(_27eb, LOW); break;

        // Row 3 (0x30 - 0x37)
        case 0x30: digitalWrite(_30eb, LOW); break;
        case 0x31: digitalWrite(_31eb, LOW); break;
        case 0x32: digitalWrite(_32eb, LOW); break;
        case 0x33: digitalWrite(_33eb, LOW); break;
        case 0x34: digitalWrite(_34eb, LOW); break;
        case 0x35: digitalWrite(_35eb, LOW); break;
        case 0x36: digitalWrite(_36eb, LOW); break;
        case 0x37: digitalWrite(_37eb, LOW); break;

        // Row 4 (0x40 - 0x47)
        case 0x40: digitalWrite(_40eb, LOW); break;
        case 0x41: digitalWrite(_41eb, LOW); break;
        case 0x42: digitalWrite(_42eb, LOW); break;
        case 0x43: digitalWrite(_43eb, LOW); break;
        case 0x44: digitalWrite(_44eb, LOW); break;
        case 0x45: digitalWrite(_45eb, LOW); break;
        case 0x46: digitalWrite(_46eb, LOW); break;
        case 0x47: digitalWrite(_47eb, LOW); break;

        // Row 5 (0x50 - 0x57)
        case 0x50: digitalWrite(_50eb, LOW); break;
        case 0x51: digitalWrite(_51eb, LOW); break;
        case 0x52: digitalWrite(_52eb, LOW); break;
        case 0x53: digitalWrite(_53eb, LOW); break;
        case 0x54: digitalWrite(_54eb, LOW); break;
        case 0x55: digitalWrite(_55eb, LOW); break;
        case 0x56: digitalWrite(_56eb, LOW); break;
        case 0x57: digitalWrite(_57eb, LOW); break;

        // Row 6 (0x60 - 0x67)
        case 0x60: digitalWrite(_60eb, LOW); break;
        case 0x61: digitalWrite(_61eb, LOW); break;
        case 0x62: digitalWrite(_62eb, LOW); break;
        case 0x63: digitalWrite(_63eb, LOW); break;
        case 0x64: digitalWrite(_64eb, LOW); break;
        case 0x65: digitalWrite(_65eb, LOW); break;
        case 0x66: digitalWrite(_66eb, LOW); break;
        case 0x67: digitalWrite(_67eb, LOW); break;

        // Row 7 (0x70 - 0x77)
        case 0x70: digitalWrite(_70eb, LOW); break;
        case 0x71: digitalWrite(_71eb, LOW); break;
        case 0x72: digitalWrite(_72eb, LOW); break;
        case 0x73: digitalWrite(_73eb, LOW); break;
        case 0x74: digitalWrite(_74eb, LOW); break;
        case 0x75: digitalWrite(_75eb, LOW); break;
        case 0x76: digitalWrite(_76eb, LOW); break;
        case 0x77: digitalWrite(_77eb, LOW); break;

        default:
            // Optionally handle an invalid tile value.
            break;
    }
}

/*
method: turnOffLED
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
        case 0x00: digitalWrite(_00eb, HIGH); break;
        case 0x01: digitalWrite(_01eb, HIGH); break;
        case 0x02: digitalWrite(_02eb, HIGH); break;
        case 0x03: digitalWrite(_03eb, HIGH); break;
        case 0x04: digitalWrite(_04eb, HIGH); break;
        case 0x05: digitalWrite(_05eb, HIGH); break;
        case 0x06: digitalWrite(_06eb, HIGH); break;
        case 0x07: digitalWrite(_07eb, HIGH); break;

        // Row 1 (0x10 - 0x17)
        case 0x10: digitalWrite(_10eb, HIGH); break;
        case 0x11: digitalWrite(_11eb, HIGH); break;
        case 0x12: digitalWrite(_12eb, HIGH); break;
        case 0x13: digitalWrite(_13eb, HIGH); break;
        case 0x14: digitalWrite(_14eb, HIGH); break;
        case 0x15: digitalWrite(_15eb, HIGH); break;
        case 0x16: digitalWrite(_16eb, HIGH); break;
        case 0x17: digitalWrite(_17eb, HIGH); break;

        // Row 2 (0x20 - 0x27)
        case 0x20: digitalWrite(_20eb, HIGH); break;
        case 0x21: digitalWrite(_21eb, HIGH); break;
        case 0x22: digitalWrite(_22eb, HIGH); break;
        case 0x23: digitalWrite(_23eb, HIGH); break;
        case 0x24: digitalWrite(_24eb, HIGH); break;
        case 0x25: digitalWrite(_25eb, HIGH); break;
        case 0x26: digitalWrite(_26eb, HIGH); break;
        case 0x27: digitalWrite(_27eb, HIGH); break;

        // Row 3 (0x30 - 0x37)
        case 0x30: digitalWrite(_30eb, HIGH); break;
        case 0x31: digitalWrite(_31eb, HIGH); break;
        case 0x32: digitalWrite(_32eb, HIGH); break;
        case 0x33: digitalWrite(_33eb, HIGH); break;
        case 0x34: digitalWrite(_34eb, HIGH); break;
        case 0x35: digitalWrite(_35eb, HIGH); break;
        case 0x36: digitalWrite(_36eb, HIGH); break;
        case 0x37: digitalWrite(_37eb, HIGH); break;

        // Row 4 (0x40 - 0x47)
        case 0x40: digitalWrite(_40eb, HIGH); break;
        case 0x41: digitalWrite(_41eb, HIGH); break;
        case 0x42: digitalWrite(_42eb, HIGH); break;
        case 0x43: digitalWrite(_43eb, HIGH); break;
        case 0x44: digitalWrite(_44eb, HIGH); break;
        case 0x45: digitalWrite(_45eb, HIGH); break;
        case 0x46: digitalWrite(_46eb, HIGH); break;
        case 0x47: digitalWrite(_47eb, HIGH); break;

        // Row 5 (0x50 - 0x57)
        case 0x50: digitalWrite(_50eb, HIGH); break;
        case 0x51: digitalWrite(_51eb, HIGH); break;
        case 0x52: digitalWrite(_52eb, HIGH); break;
        case 0x53: digitalWrite(_53eb, HIGH); break;
        case 0x54: digitalWrite(_54eb, HIGH); break;
        case 0x55: digitalWrite(_55eb, HIGH); break;
        case 0x56: digitalWrite(_56eb, HIGH); break;
        case 0x57: digitalWrite(_57eb, HIGH); break;

        // Row 6 (0x60 - 0x67)
        case 0x60: digitalWrite(_60eb, HIGH); break;
        case 0x61: digitalWrite(_61eb, HIGH); break;
        case 0x62: digitalWrite(_62eb, HIGH); break;
        case 0x63: digitalWrite(_63eb, HIGH); break;
        case 0x64: digitalWrite(_64eb, HIGH); break;
        case 0x65: digitalWrite(_65eb, HIGH); break;
        case 0x66: digitalWrite(_66eb, HIGH); break;
        case 0x67: digitalWrite(_67eb, HIGH); break;

        // Row 7 (0x70 - 0x77)
        case 0x70: digitalWrite(_70eb, HIGH); break;
        case 0x71: digitalWrite(_71eb, HIGH); break;
        case 0x72: digitalWrite(_72eb, HIGH); break;
        case 0x73: digitalWrite(_73eb, HIGH); break;
        case 0x74: digitalWrite(_74eb, HIGH); break;
        case 0x75: digitalWrite(_75eb, HIGH); break;
        case 0x76: digitalWrite(_76eb, HIGH); break;
        case 0x77: digitalWrite(_77eb, HIGH); break;

        default:
            // Optionally handle an invalid tile value.
            break;
    }
}

/*
method: changeLEDcolor
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
        case 'R': digitalWrite(_00sb0, LOW); digitalWrite(_00sb1, LOW); break;
        case 'B': digitalWrite(_00sb0, LOW); digitalWrite(_00sb1, HIGH); break;
        case 'Y': digitalWrite(_00sb0, HIGH); digitalWrite(_00sb1, LOW); break;
        case 'G': digitalWrite(_00sb0, HIGH); digitalWrite(_00sb1, HIGH); break;
      }
      break;
    case 0x01:
      switch (color) {
        case 'R': digitalWrite(_01sb0, LOW); digitalWrite(_01sb1, LOW); break;
        case 'B': digitalWrite(_01sb0, LOW); digitalWrite(_01sb1, HIGH); break;
        case 'Y': digitalWrite(_01sb0, HIGH); digitalWrite(_01sb1, LOW); break;
        case 'G': digitalWrite(_01sb0, HIGH); digitalWrite(_01sb1, HIGH); break;
      }
      break;
    case 0x02:
      switch (color) {
        case 'R': digitalWrite(_02sb0, LOW); digitalWrite(_02sb1, LOW); break;
        case 'B': digitalWrite(_02sb0, LOW); digitalWrite(_02sb1, HIGH); break;
        case 'Y': digitalWrite(_02sb0, HIGH); digitalWrite(_02sb1, LOW); break;
        case 'G': digitalWrite(_02sb0, HIGH); digitalWrite(_02sb1, HIGH); break;
      }
      break;
    case 0x03:
      switch (color) {
        case 'R': digitalWrite(_03sb0, LOW); digitalWrite(_03sb1, LOW); break;
        case 'B': digitalWrite(_03sb0, LOW); digitalWrite(_03sb1, HIGH); break;
        case 'Y': digitalWrite(_03sb0, HIGH); digitalWrite(_03sb1, LOW); break;
        case 'G': digitalWrite(_03sb0, HIGH); digitalWrite(_03sb1, HIGH); break;
      }
      break;
    case 0x04:
      switch (color) {
        case 'R': digitalWrite(_04sb0, LOW); digitalWrite(_04sb1, LOW); break;
        case 'B': digitalWrite(_04sb0, LOW); digitalWrite(_04sb1, HIGH); break;
        case 'Y': digitalWrite(_04sb0, HIGH); digitalWrite(_04sb1, LOW); break;
        case 'G': digitalWrite(_04sb0, HIGH); digitalWrite(_04sb1, HIGH); break;
      }
      break;
    case 0x05:
      switch (color) {
        case 'R': digitalWrite(_05sb0, LOW); digitalWrite(_05sb1, LOW); break;
        case 'B': digitalWrite(_05sb0, LOW); digitalWrite(_05sb1, HIGH); break;
        case 'Y': digitalWrite(_05sb0, HIGH); digitalWrite(_05sb1, LOW); break;
        case 'G': digitalWrite(_05sb0, HIGH); digitalWrite(_05sb1, HIGH); break;
      }
      break;
    case 0x06:
      switch (color) {
        case 'R': digitalWrite(_06sb0, LOW); digitalWrite(_06sb1, LOW); break;
        case 'B': digitalWrite(_06sb0, LOW); digitalWrite(_06sb1, HIGH); break;
        case 'Y': digitalWrite(_06sb0, HIGH); digitalWrite(_06sb1, LOW); break;
        case 'G': digitalWrite(_06sb0, HIGH); digitalWrite(_06sb1, HIGH); break;
      }
      break;
    case 0x07:
      switch (color) {
        case 'R': digitalWrite(_07sb0, LOW); digitalWrite(_07sb1, LOW); break;
        case 'B': digitalWrite(_07sb0, LOW); digitalWrite(_07sb1, HIGH); break;
        case 'Y': digitalWrite(_07sb0, HIGH); digitalWrite(_07sb1, LOW); break;
        case 'G': digitalWrite(_07sb0, HIGH); digitalWrite(_07sb1, HIGH); break;
      }
      break;
      
    // Row: 1 (a2-h2)
    case 0x10:
      switch (color) {
        case 'R': digitalWrite(_10sb0, LOW); digitalWrite(_10sb1, LOW); break;
        case 'B': digitalWrite(_10sb0, LOW); digitalWrite(_10sb1, HIGH); break;
        case 'Y': digitalWrite(_10sb0, HIGH); digitalWrite(_10sb1, LOW); break;
        case 'G': digitalWrite(_10sb0, HIGH); digitalWrite(_10sb1, HIGH); break;
      }
      break;
    case 0x11:
      switch (color) {
        case 'R': digitalWrite(_11sb0, LOW); digitalWrite(_11sb1, LOW); break;
        case 'B': digitalWrite(_11sb0, LOW); digitalWrite(_11sb1, HIGH); break;
        case 'Y': digitalWrite(_11sb0, HIGH); digitalWrite(_11sb1, LOW); break;
        case 'G': digitalWrite(_11sb0, HIGH); digitalWrite(_11sb1, HIGH); break;
      }
      break;
    case 0x12:
      switch (color) {
        case 'R': digitalWrite(_12sb0, LOW); digitalWrite(_12sb1, LOW); break;
        case 'B': digitalWrite(_12sb0, LOW); digitalWrite(_12sb1, HIGH); break;
        case 'Y': digitalWrite(_12sb0, HIGH); digitalWrite(_12sb1, LOW); break;
        case 'G': digitalWrite(_12sb0, HIGH); digitalWrite(_12sb1, HIGH); break;
      }
      break;
    case 0x13:
      switch (color) {
        case 'R': digitalWrite(_13sb0, LOW); digitalWrite(_13sb1, LOW); break;
        case 'B': digitalWrite(_13sb0, LOW); digitalWrite(_13sb1, HIGH); break;
        case 'Y': digitalWrite(_13sb0, HIGH); digitalWrite(_13sb1, LOW); break;
        case 'G': digitalWrite(_13sb0, HIGH); digitalWrite(_13sb1, HIGH); break;
      }
      break;
    case 0x14:
      switch (color) {
        case 'R': digitalWrite(_14sb0, LOW); digitalWrite(_14sb1, LOW); break;
        case 'B': digitalWrite(_14sb0, LOW); digitalWrite(_14sb1, HIGH); break;
        case 'Y': digitalWrite(_14sb0, HIGH); digitalWrite(_14sb1, LOW); break;
        case 'G': digitalWrite(_14sb0, HIGH); digitalWrite(_14sb1, HIGH); break;
      }
      break;
    case 0x15:
      switch (color) {
        case 'R': digitalWrite(_15sb0, LOW); digitalWrite(_15sb1, LOW); break;
        case 'B': digitalWrite(_15sb0, LOW); digitalWrite(_15sb1, HIGH); break;
        case 'Y': digitalWrite(_15sb0, HIGH); digitalWrite(_15sb1, LOW); break;
        case 'G': digitalWrite(_15sb0, HIGH); digitalWrite(_15sb1, HIGH); break;
      }
      break;
    case 0x16:
      switch (color) {
        case 'R': digitalWrite(_16sb0, LOW); digitalWrite(_16sb1, LOW); break;
        case 'B': digitalWrite(_16sb0, LOW); digitalWrite(_16sb1, HIGH); break;
        case 'Y': digitalWrite(_16sb0, HIGH); digitalWrite(_16sb1, LOW); break;
        case 'G': digitalWrite(_16sb0, HIGH); digitalWrite(_16sb1, HIGH); break;
      }
      break;
    case 0x17:
      switch (color) {
        case 'R': digitalWrite(_17sb0, LOW); digitalWrite(_17sb1, LOW); break;
        case 'B': digitalWrite(_17sb0, LOW); digitalWrite(_17sb1, HIGH); break;
        case 'Y': digitalWrite(_17sb0, HIGH); digitalWrite(_17sb1, LOW); break;
        case 'G': digitalWrite(_17sb0, HIGH); digitalWrite(_17sb1, HIGH); break;
      }
      break;
      
    // Row: 2 (a3-h3)
    case 0x20:
      switch (color) {
        case 'R': digitalWrite(_20sb0, LOW); digitalWrite(_20sb1, LOW); break;
        case 'B': digitalWrite(_20sb0, LOW); digitalWrite(_20sb1, HIGH); break;
        case 'Y': digitalWrite(_20sb0, HIGH); digitalWrite(_20sb1, LOW); break;
        case 'G': digitalWrite(_20sb0, HIGH); digitalWrite(_20sb1, HIGH); break;
      }
      break;
    case 0x21:
      switch (color) {
        case 'R': digitalWrite(_21sb0, LOW); digitalWrite(_21sb1, LOW); break;
        case 'B': digitalWrite(_21sb0, LOW); digitalWrite(_21sb1, HIGH); break;
        case 'Y': digitalWrite(_21sb0, HIGH); digitalWrite(_21sb1, LOW); break;
        case 'G': digitalWrite(_21sb0, HIGH); digitalWrite(_21sb1, HIGH); break;
      }
      break;
    case 0x22:
      switch (color) {
        case 'R': digitalWrite(_22sb0, LOW); digitalWrite(_22sb1, LOW); break;
        case 'B': digitalWrite(_22sb0, LOW); digitalWrite(_22sb1, HIGH); break;
        case 'Y': digitalWrite(_22sb0, HIGH); digitalWrite(_22sb1, LOW); break;
        case 'G': digitalWrite(_22sb0, HIGH); digitalWrite(_22sb1, HIGH); break;
      }
      break;
    case 0x23:
      switch (color) {
        case 'R': digitalWrite(_23sb0, LOW); digitalWrite(_23sb1, LOW); break;
        case 'B': digitalWrite(_23sb0, LOW); digitalWrite(_23sb1, HIGH); break;
        case 'Y': digitalWrite(_23sb0, HIGH); digitalWrite(_23sb1, LOW); break;
        case 'G': digitalWrite(_23sb0, HIGH); digitalWrite(_23sb1, HIGH); break;
      }
      break;
    case 0x24:
      switch (color) {
        case 'R': digitalWrite(_24sb0, LOW); digitalWrite(_24sb1, LOW); break;
        case 'B': digitalWrite(_24sb0, LOW); digitalWrite(_24sb1, HIGH); break;
        case 'Y': digitalWrite(_24sb0, HIGH); digitalWrite(_24sb1, LOW); break;
        case 'G': digitalWrite(_24sb0, HIGH); digitalWrite(_24sb1, HIGH); break;
      }
      break;
    case 0x25:
      switch (color) {
        case 'R': digitalWrite(_25sb0, LOW); digitalWrite(_25sb1, LOW); break;
        case 'B': digitalWrite(_25sb0, LOW); digitalWrite(_25sb1, HIGH); break;
        case 'Y': digitalWrite(_25sb0, HIGH); digitalWrite(_25sb1, LOW); break;
        case 'G': digitalWrite(_25sb0, HIGH); digitalWrite(_25sb1, HIGH); break;
      }
      break;
    case 0x26:
      switch (color) {
        case 'R': digitalWrite(_26sb0, LOW); digitalWrite(_26sb1, LOW); break;
        case 'B': digitalWrite(_26sb0, LOW); digitalWrite(_26sb1, HIGH); break;
        case 'Y': digitalWrite(_26sb0, HIGH); digitalWrite(_26sb1, LOW); break;
        case 'G': digitalWrite(_26sb0, HIGH); digitalWrite(_26sb1, HIGH); break;
      }
      break;
    case 0x27:
      switch (color) {
        case 'R': digitalWrite(_27sb0, LOW); digitalWrite(_27sb1, LOW); break;
        case 'B': digitalWrite(_27sb0, LOW); digitalWrite(_27sb1, HIGH); break;
        case 'Y': digitalWrite(_27sb0, HIGH); digitalWrite(_27sb1, LOW); break;
        case 'G': digitalWrite(_27sb0, HIGH); digitalWrite(_27sb1, HIGH); break;
      }
      break;
      
    // Row: 3 (a4-h4)
    case 0x30:
      switch (color) {
        case 'R': digitalWrite(_30sb0, LOW); digitalWrite(_30sb1, LOW); break;
        case 'B': digitalWrite(_30sb0, LOW); digitalWrite(_30sb1, HIGH); break;
        case 'Y': digitalWrite(_30sb0, HIGH); digitalWrite(_30sb1, LOW); break;
        case 'G': digitalWrite(_30sb0, HIGH); digitalWrite(_30sb1, HIGH); break;
      }
      break;
    case 0x31:
      switch (color) {
        case 'R': digitalWrite(_31sb0, LOW); digitalWrite(_31sb1, LOW); break;
        case 'B': digitalWrite(_31sb0, LOW); digitalWrite(_31sb1, HIGH); break;
        case 'Y': digitalWrite(_31sb0, HIGH); digitalWrite(_31sb1, LOW); break;
        case 'G': digitalWrite(_31sb0, HIGH); digitalWrite(_31sb1, HIGH); break;
      }
      break;
    case 0x32:
      switch (color) {
        case 'R': digitalWrite(_32sb0, LOW); digitalWrite(_32sb1, LOW); break;
        case 'B': digitalWrite(_32sb0, LOW); digitalWrite(_32sb1, HIGH); break;
        case 'Y': digitalWrite(_32sb0, HIGH); digitalWrite(_32sb1, LOW); break;
        case 'G': digitalWrite(_32sb0, HIGH); digitalWrite(_32sb1, HIGH); break;
      }
      break;
    case 0x33:
      switch (color) {
        case 'R': digitalWrite(_33sb0, LOW); digitalWrite(_33sb1, LOW); break;
        case 'B': digitalWrite(_33sb0, LOW); digitalWrite(_33sb1, HIGH); break;
        case 'Y': digitalWrite(_33sb0, HIGH); digitalWrite(_33sb1, LOW); break;
        case 'G': digitalWrite(_33sb0, HIGH); digitalWrite(_33sb1, HIGH); break;
      }
      break;
    case 0x34:
      switch (color) {
        case 'R': digitalWrite(_34sb0, LOW); digitalWrite(_34sb1, LOW); break;
        case 'B': digitalWrite(_34sb0, LOW); digitalWrite(_34sb1, HIGH); break;
        case 'Y': digitalWrite(_34sb0, HIGH); digitalWrite(_34sb1, LOW); break;
        case 'G': digitalWrite(_34sb0, HIGH); digitalWrite(_34sb1, HIGH); break;
      }
      break;
    case 0x35:
      switch (color) {
        case 'R': digitalWrite(_35sb0, LOW); digitalWrite(_35sb1, LOW); break;
        case 'B': digitalWrite(_35sb0, LOW); digitalWrite(_35sb1, HIGH); break;
        case 'Y': digitalWrite(_35sb0, HIGH); digitalWrite(_35sb1, LOW); break;
        case 'G': digitalWrite(_35sb0, HIGH); digitalWrite(_35sb1, HIGH); break;
      }
      break;
    case 0x36:
      switch (color) {
        case 'R': digitalWrite(_36sb0, LOW); digitalWrite(_36sb1, LOW); break;
        case 'B': digitalWrite(_36sb0, LOW); digitalWrite(_36sb1, HIGH); break;
        case 'Y': digitalWrite(_36sb0, HIGH); digitalWrite(_36sb1, LOW); break;
        case 'G': digitalWrite(_36sb0, HIGH); digitalWrite(_36sb1, HIGH); break;
      }
      break;
    case 0x37:
      switch (color) {
        case 'R': digitalWrite(_37sb0, LOW); digitalWrite(_37sb1, LOW); break;
        case 'B': digitalWrite(_37sb0, LOW); digitalWrite(_37sb1, HIGH); break;
        case 'Y': digitalWrite(_37sb0, HIGH); digitalWrite(_37sb1, LOW); break;
        case 'G': digitalWrite(_37sb0, HIGH); digitalWrite(_37sb1, HIGH); break;
      }
      break;
      
    // Row: 4 (a5-h5)
    case 0x40:
      switch (color) {
        case 'R': digitalWrite(_40sb0, LOW); digitalWrite(_40sb1, LOW); break;
        case 'B': digitalWrite(_40sb0, LOW); digitalWrite(_40sb1, HIGH); break;
        case 'Y': digitalWrite(_40sb0, HIGH); digitalWrite(_40sb1, LOW); break;
        case 'G': digitalWrite(_40sb0, HIGH); digitalWrite(_40sb1, HIGH); break;
      }
      break;
    case 0x41:
      switch (color) {
        case 'R': digitalWrite(_41sb0, LOW); digitalWrite(_41sb1, LOW); break;
        case 'B': digitalWrite(_41sb0, LOW); digitalWrite(_41sb1, HIGH); break;
        case 'Y': digitalWrite(_41sb0, HIGH); digitalWrite(_41sb1, LOW); break;
        case 'G': digitalWrite(_41sb0, HIGH); digitalWrite(_41sb1, HIGH); break;
      }
      break;
    case 0x42:
      switch (color) {
        case 'R': digitalWrite(_42sb0, LOW); digitalWrite(_42sb1, LOW); break;
        case 'B': digitalWrite(_42sb0, LOW); digitalWrite(_42sb1, HIGH); break;
        case 'Y': digitalWrite(_42sb0, HIGH); digitalWrite(_42sb1, LOW); break;
        case 'G': digitalWrite(_42sb0, HIGH); digitalWrite(_42sb1, HIGH); break;
      }
      break;
    case 0x43:
      switch (color) {
        case 'R': digitalWrite(_43sb0, LOW); digitalWrite(_43sb1, LOW); break;
        case 'B': digitalWrite(_43sb0, LOW); digitalWrite(_43sb1, HIGH); break;
        case 'Y': digitalWrite(_43sb0, HIGH); digitalWrite(_43sb1, LOW); break;
        case 'G': digitalWrite(_43sb0, HIGH); digitalWrite(_43sb1, HIGH); break;
      }
      break;
    case 0x44:
      switch (color) {
        case 'R': digitalWrite(_44sb0, LOW); digitalWrite(_44sb1, LOW); break;
        case 'B': digitalWrite(_44sb0, LOW); digitalWrite(_44sb1, HIGH); break;
        case 'Y': digitalWrite(_44sb0, HIGH); digitalWrite(_44sb1, LOW); break;
        case 'G': digitalWrite(_44sb0, HIGH); digitalWrite(_44sb1, HIGH); break;
      }
      break;
    case 0x45:
      switch (color) {
        case 'R': digitalWrite(_45sb0, LOW); digitalWrite(_45sb1, LOW); break;
        case 'B': digitalWrite(_45sb0, LOW); digitalWrite(_45sb1, HIGH); break;
        case 'Y': digitalWrite(_45sb0, HIGH); digitalWrite(_45sb1, LOW); break;
        case 'G': digitalWrite(_45sb0, HIGH); digitalWrite(_45sb1, HIGH); break;
      }
      break;
    case 0x46:
      switch (color) {
        case 'R': digitalWrite(_46sb0, LOW); digitalWrite(_46sb1, LOW); break;
        case 'B': digitalWrite(_46sb0, LOW); digitalWrite(_46sb1, HIGH); break;
        case 'Y': digitalWrite(_46sb0, HIGH); digitalWrite(_46sb1, LOW); break;
        case 'G': digitalWrite(_46sb0, HIGH); digitalWrite(_46sb1, HIGH); break;
      }
      break;
    case 0x47:
      switch (color) {
        case 'R': digitalWrite(_47sb0, LOW); digitalWrite(_47sb1, LOW); break;
        case 'B': digitalWrite(_47sb0, LOW); digitalWrite(_47sb1, HIGH); break;
        case 'Y': digitalWrite(_47sb0, HIGH); digitalWrite(_47sb1, LOW); break;
        case 'G': digitalWrite(_47sb0, HIGH); digitalWrite(_47sb1, HIGH); break;
      }
      break;
      
    // Row: 5 (a6-h6)
    case 0x50:
      switch (color) {
        case 'R': digitalWrite(_50sb0, LOW); digitalWrite(_50sb1, LOW); break;
        case 'B': digitalWrite(_50sb0, LOW); digitalWrite(_50sb1, HIGH); break;
        case 'Y': digitalWrite(_50sb0, HIGH); digitalWrite(_50sb1, LOW); break;
        case 'G': digitalWrite(_50sb0, HIGH); digitalWrite(_50sb1, HIGH); break;
      }
      break;
    case 0x51:
      switch (color) {
        case 'R': digitalWrite(_51sb0, LOW); digitalWrite(_51sb1, LOW); break;
        case 'B': digitalWrite(_51sb0, LOW); digitalWrite(_51sb1, HIGH); break;
        case 'Y': digitalWrite(_51sb0, HIGH); digitalWrite(_51sb1, LOW); break;
        case 'G': digitalWrite(_51sb0, HIGH); digitalWrite(_51sb1, HIGH); break;
      }
      break;
    case 0x52:
      switch (color) {
        case 'R': digitalWrite(_52sb0, LOW); digitalWrite(_52sb1, LOW); break;
        case 'B': digitalWrite(_52sb0, LOW); digitalWrite(_52sb1, HIGH); break;
        case 'Y': digitalWrite(_52sb0, HIGH); digitalWrite(_52sb1, LOW); break;
        case 'G': digitalWrite(_52sb0, HIGH); digitalWrite(_52sb1, HIGH); break;
      }
      break;
    case 0x53:
      switch (color) {
        case 'R': digitalWrite(_53sb0, LOW); digitalWrite(_53sb1, LOW); break;
        case 'B': digitalWrite(_53sb0, LOW); digitalWrite(_53sb1, HIGH); break;
        case 'Y': digitalWrite(_53sb0, HIGH); digitalWrite(_53sb1, LOW); break;
        case 'G': digitalWrite(_53sb0, HIGH); digitalWrite(_53sb1, HIGH); break;
      }
      break;
    case 0x54:
      switch (color) {
        case 'R': digitalWrite(_54sb0, LOW); digitalWrite(_54sb1, LOW); break;
        case 'B': digitalWrite(_54sb0, LOW); digitalWrite(_54sb1, HIGH); break;
        case 'Y': digitalWrite(_54sb0, HIGH); digitalWrite(_54sb1, LOW); break;
        case 'G': digitalWrite(_54sb0, HIGH); digitalWrite(_54sb1, HIGH); break;
      }
      break;
    case 0x55:
      switch (color) {
        case 'R': digitalWrite(_55sb0, LOW); digitalWrite(_55sb1, LOW); break;
        case 'B': digitalWrite(_55sb0, LOW); digitalWrite(_55sb1, HIGH); break;
        case 'Y': digitalWrite(_55sb0, HIGH); digitalWrite(_55sb1, LOW); break;
        case 'G': digitalWrite(_55sb0, HIGH); digitalWrite(_55sb1, HIGH); break;
      }
      break;
    case 0x56:
      switch (color) {
        case 'R': digitalWrite(_56sb0, LOW); digitalWrite(_56sb1, LOW); break;
        case 'B': digitalWrite(_56sb0, LOW); digitalWrite(_56sb1, HIGH); break;
        case 'Y': digitalWrite(_56sb0, HIGH); digitalWrite(_56sb1, LOW); break;
        case 'G': digitalWrite(_56sb0, HIGH); digitalWrite(_56sb1, HIGH); break;
      }
      break;
    case 0x57:
      switch (color) {
        case 'R': digitalWrite(_57sb0, LOW); digitalWrite(_57sb1, LOW); break;
        case 'B': digitalWrite(_57sb0, LOW); digitalWrite(_57sb1, HIGH); break;
        case 'Y': digitalWrite(_57sb0, HIGH); digitalWrite(_57sb1, LOW); break;
        case 'G': digitalWrite(_57sb0, HIGH); digitalWrite(_57sb1, HIGH); break;
      }
      break;
      
    // Row: 6 (a7-h7)
    case 0x60:
      switch (color) {
        case 'R': digitalWrite(_60sb0, LOW); digitalWrite(_60sb1, LOW); break;
        case 'B': digitalWrite(_60sb0, LOW); digitalWrite(_60sb1, HIGH); break;
        case 'Y': digitalWrite(_60sb0, HIGH); digitalWrite(_60sb1, LOW); break;
        case 'G': digitalWrite(_60sb0, HIGH); digitalWrite(_60sb1, HIGH); break;
      }
      break;
    case 0x61:
      switch (color) {
        case 'R': digitalWrite(_61sb0, LOW); digitalWrite(_61sb1, LOW); break;
        case 'B': digitalWrite(_61sb0, LOW); digitalWrite(_61sb1, HIGH); break;
        case 'Y': digitalWrite(_61sb0, HIGH); digitalWrite(_61sb1, LOW); break;
        case 'G': digitalWrite(_61sb0, HIGH); digitalWrite(_61sb1, HIGH); break;
      }
      break;
    case 0x62:
      switch (color) {
        case 'R': digitalWrite(_62sb0, LOW); digitalWrite(_62sb1, LOW); break;
        case 'B': digitalWrite(_62sb0, LOW); digitalWrite(_62sb1, HIGH); break;
        case 'Y': digitalWrite(_62sb0, HIGH); digitalWrite(_62sb1, LOW); break;
        case 'G': digitalWrite(_62sb0, HIGH); digitalWrite(_62sb1, HIGH); break;
      }
      break;
    case 0x63:
      switch (color) {
        case 'R': digitalWrite(_63sb0, LOW); digitalWrite(_63sb1, LOW); break;
        case 'B': digitalWrite(_63sb0, LOW); digitalWrite(_63sb1, HIGH); break;
        case 'Y': digitalWrite(_63sb0, HIGH); digitalWrite(_63sb1, LOW); break;
        case 'G': digitalWrite(_63sb0, HIGH); digitalWrite(_63sb1, HIGH); break;
      }
      break;
    case 0x64:
      switch (color) {
        case 'R': digitalWrite(_64sb0, LOW); digitalWrite(_64sb1, LOW); break;
        case 'B': digitalWrite(_64sb0, LOW); digitalWrite(_64sb1, HIGH); break;
        case 'Y': digitalWrite(_64sb0, HIGH); digitalWrite(_64sb1, LOW); break;
        case 'G': digitalWrite(_64sb0, HIGH); digitalWrite(_64sb1, HIGH); break;
      }
      break;
    case 0x65:
      switch (color) {
        case 'R': digitalWrite(_65sb0, LOW); digitalWrite(_65sb1, LOW); break;
        case 'B': digitalWrite(_65sb0, LOW); digitalWrite(_65sb1, HIGH); break;
        case 'Y': digitalWrite(_65sb0, HIGH); digitalWrite(_65sb1, LOW); break;
        case 'G': digitalWrite(_65sb0, HIGH); digitalWrite(_65sb1, HIGH); break;
      }
      break;
    case 0x66:
      switch (color) {
        case 'R': digitalWrite(_66sb0, LOW); digitalWrite(_66sb1, LOW); break;
        case 'B': digitalWrite(_66sb0, LOW); digitalWrite(_66sb1, HIGH); break;
        case 'Y': digitalWrite(_66sb0, HIGH); digitalWrite(_66sb1, LOW); break;
        case 'G': digitalWrite(_66sb0, HIGH); digitalWrite(_66sb1, HIGH); break;
      }
      break;
    case 0x67:
      switch (color) {
        case 'R': digitalWrite(_67sb0, LOW); digitalWrite(_67sb1, LOW); break;
        case 'B': digitalWrite(_67sb0, LOW); digitalWrite(_67sb1, HIGH); break;
        case 'Y': digitalWrite(_67sb0, HIGH); digitalWrite(_67sb1, LOW); break;
        case 'G': digitalWrite(_67sb0, HIGH); digitalWrite(_67sb1, HIGH); break;
      }
      break;
      
    // Row: 7 (a8-h8)
    case 0x70:
      switch (color) {
        case 'R': digitalWrite(_70sb0, LOW); digitalWrite(_70sb1, LOW); break;
        case 'B': digitalWrite(_70sb0, LOW); digitalWrite(_70sb1, HIGH); break;
        case 'Y': digitalWrite(_70sb0, HIGH); digitalWrite(_70sb1, LOW); break;
        case 'G': digitalWrite(_70sb0, HIGH); digitalWrite(_70sb1, HIGH); break;
      }
      break;
    case 0x71:
      switch (color) {
        case 'R': digitalWrite(_71sb0, LOW); digitalWrite(_71sb1, LOW); break;
        case 'B': digitalWrite(_71sb0, LOW); digitalWrite(_71sb1, HIGH); break;
        case 'Y': digitalWrite(_71sb0, HIGH); digitalWrite(_71sb1, LOW); break;
        case 'G': digitalWrite(_71sb0, HIGH); digitalWrite(_71sb1, HIGH); break;
      }
      break;
    case 0x72:
      switch (color) {
        case 'R': digitalWrite(_72sb0, LOW); digitalWrite(_72sb1, LOW); break;
        case 'B': digitalWrite(_72sb0, LOW); digitalWrite(_72sb1, HIGH); break;
        case 'Y': digitalWrite(_72sb0, HIGH); digitalWrite(_72sb1, LOW); break;
        case 'G': digitalWrite(_72sb0, HIGH); digitalWrite(_72sb1, HIGH); break;
      }
      break;
    case 0x73:
      switch (color) {
        case 'R': digitalWrite(_73sb0, LOW); digitalWrite(_73sb1, LOW); break;
        case 'B': digitalWrite(_73sb0, LOW); digitalWrite(_73sb1, HIGH); break;
        case 'Y': digitalWrite(_73sb0, HIGH); digitalWrite(_73sb1, LOW); break;
        case 'G': digitalWrite(_73sb0, HIGH); digitalWrite(_73sb1, HIGH); break;
      }
      break;
    case 0x74:
      switch (color) {
        case 'R': digitalWrite(_74sb0, LOW); digitalWrite(_74sb1, LOW); break;
        case 'B': digitalWrite(_74sb0, LOW); digitalWrite(_74sb1, HIGH); break;
        case 'Y': digitalWrite(_74sb0, HIGH); digitalWrite(_74sb1, LOW); break;
        case 'G': digitalWrite(_74sb0, HIGH); digitalWrite(_74sb1, HIGH); break;
      }
      break;
    case 0x75:
      switch (color) {
        case 'R': digitalWrite(_75sb0, LOW); digitalWrite(_75sb1, LOW); break;
        case 'B': digitalWrite(_75sb0, LOW); digitalWrite(_75sb1, HIGH); break;
        case 'Y': digitalWrite(_75sb0, HIGH); digitalWrite(_75sb1, LOW); break;
        case 'G': digitalWrite(_75sb0, HIGH); digitalWrite(_75sb1, HIGH); break;
      }
      break;
    case 0x76:
      switch (color) {
        case 'R': digitalWrite(_76sb0, LOW); digitalWrite(_76sb1, LOW); break;
        case 'B': digitalWrite(_76sb0, LOW); digitalWrite(_76sb1, HIGH); break;
        case 'Y': digitalWrite(_76sb0, HIGH); digitalWrite(_76sb1, LOW); break;
        case 'G': digitalWrite(_76sb0, HIGH); digitalWrite(_76sb1, HIGH); break;
      }
      break;
    case 0x77:
      switch (color) {
        case 'R': digitalWrite(_77sb0, LOW); digitalWrite(_77sb1, LOW); break;
        case 'B': digitalWrite(_77sb0, LOW); digitalWrite(_77sb1, HIGH); break;
        case 'Y': digitalWrite(_77sb0, HIGH); digitalWrite(_77sb1, LOW); break;
        case 'G': digitalWrite(_77sb0, HIGH); digitalWrite(_77sb1, HIGH); break;
      }
      break;
      
    default:
      // Optionally handle an invalid tile value.
      break;
  }
}

/*
method: PrintLCD
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

/*
method: PrintLCDL1
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

/*
method: PrintLCDL2
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
  
/*
method: ClearLCD
function: Clears the entire LCD display.
details:
  - Removes any text from both the first and second lines of the LCD by printing 16 spaces to both lines of the LCD.
*/
void HardwareAPI::ClearLCD() 
{
  ClearLCDL1();
  ClearLCDL2();
}

/*
method: ClearLCDL1
function: Clears the first line of the LCD.
details:
  - Removes any text from the first line of the LCD by printing 16 spaces.
*/
void HardwareAPI::ClearLCDL1() 
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
}

/*
method: ClearLCDL2
function: Clears the second line of the LCD.
details:
  - Removes any text from the second line of the LCD by printing 16 spaces.
*/
void HardwareAPI::ClearLCDL2() 
{
  lcd.setCursor(0, 1);
  lcd.print("                ");
}