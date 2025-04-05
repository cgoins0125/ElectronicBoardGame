#include <HardwareAPI.h>
#include <vector>

HardwareAPI api;

std::vector<char> r1tiles = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
std::vector<char> r2tiles = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};
std::vector<char> r3tiles = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27};
std::vector<char> r4tiles = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};
std::vector<char> r5tiles = {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47};
std::vector<char> r6tiles = {0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57};
std::vector<char> r7tiles = {0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67};
std::vector<char> r8tiles = {0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77};

void setup() {
  api.begin();
}

void loop() {
  // Array of rows (8 rows with 8 tiles each)
  std::vector<std::vector<char>> rows = {r1tiles, r2tiles, r3tiles, r4tiles, r5tiles, r6tiles, r7tiles, r8tiles};

  // Define colors
  std::array<char, 4> colors = {'G', 'R', 'B', 'Y'};  // Green, Red, Blue, Yellow

  // Loop through all rows
  for (auto& currentRow : rows) {
    // Iterate over each color
    for (char color : colors) {
      // Display current color on the LCD
      api.printLCD("Current: ");

      // Turn on the LEDs in the current row with the current color
      api.turnOnMultipleTiles(currentRow, color);

      // Wait for 1 seconds
      delay(1000);

      // Change the color for the next iteration
      if (color != 'Y') {
        api.changeMultipleTileColors(currentRow, color);
      }
    }

    // Turn off all LEDs for the current row before moving to the next row
    api.turnOffMultipleTiles(currentRow);
    delay(1000);  // Wait before moving to the next row
  }
}
