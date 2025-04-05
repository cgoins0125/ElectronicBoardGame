#include <HardwareAPI.h>
#include <array>

HardwareAPI api;

std::array<char, 8> r1tiles = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};  // Row 1 tiles (0x00 to 0x07)
std::array<char, 8> r2tiles = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};  // Row 2 tiles (0x10 to 0x17)
std::array<char, 8> r3tiles = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27};  // Row 3 tiles (0x20 to 0x27)
std::array<char, 8> r4tiles = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};  // Row 4 tiles (0x30 to 0x37)
std::array<char, 8> r5tiles = {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47};  // Row 5 tiles (0x40 to 0x47)
std::array<char, 8> r6tiles = {0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57};  // Row 6 tiles (0x50 to 0x57)
std::array<char, 8> r7tiles = {0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67};  // Row 7 tiles (0x60 to 0x67)
std::array<char, 8> r8tiles = {0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77};  // Row 8 tiles (0x70 to 0x77)

void setup() {
  api.begin();
}

void loop() {
  // Loop through all rows
  std::array<std::array<char, 8>, 8> rows = {r1tiles, r2tiles, r3tiles, r4tiles, r5tiles, r6tiles, r7tiles, r8tiles};
  
  // Define colors
  std::array<char, 4> colors = {'G', 'R', 'B', 'Y'};  // Green, Red, Blue, Yellow
    
    // Iterate over each color
    for (char color : colors) {
      // Display current color and row on the LCD
      api.printLCD("Current: " + color, rowMessage);

      // Turn on the LEDs in the current row with the current color
      api.turnOnMultipleTiles(currentRow, color);

      // Wait for 5 seconds
      delay(5000);

      // Change the color for the next iteration
      if (color != 'Y') {
        api.changeMultipleTileColors(currentRow, color);
      }
    }
    
    // Turn off all LEDs for the current row before moving to the next row
    api.turnOffMultipleTiles(currentRow);
    delay(5000);
  }
}
