#include "HardwareAPI.h"

//Instantiate the gameBoard object
HardwareAPI gameBoard;

//These are all of the tiles. edit this for game being programmed - be sure to specify the size (64 tiles total)
std::array<char, 64> validHexTiles = {0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
                                     0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
                                     0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
                                     0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
                                     0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                                     0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                                     0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                     0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}

void setup() {
    /* copy the following lines exactly only changing interrupt trigger as needed */
    interrupts();
    gameBoard.begin();
    for (char tile : validHexTiles) { //Loop over the tiles needed for the game
        int port = gameBoard.getTilePort(tile); //get port that is mapped to the tile
        if (port == -1) break;
        pinMode(port, INPUT_PULLUP); 
        /*
         * RISING: Only trigger interrupts when game piece is brought close to tile
         * FALLING: Only trigger interrupts when game piece is taken away from tile
         * CHANGING: trigger interrupts when game piece is brought close to or taken away from tile
        */
        attachInterrupt(digitalPinToInterrupt(port), handleInterrupt, RISING);
      }

}

void loop() {
    //do nothing unless player has triggered an interrupt 
    delay(1000);
}

void handleInterrupt() {
    char tile = gameBoard.getInterruptTile(); // Wait for player selection
    if (tile == 0xFF) return; //interupt tile was not found
    if (!isValidTile(tile)) return; //invalid tile this method was created below and is not part of the API - may not be needed
    noInterrupts(); //pause interrupts while handling this one
    int row = (tile >> 4) & 0x0F; //Get the first hex digit of valid tile with bitwishe shift to the right & a bit mask on shifted bits
    int col = tile & 0x0F; //Get the second hex digit of valid tile using a bit mask on 4 LSBs
    
    /*
     * CREATE GAME LOGIC HERE
     *
     *
     *
     *
     *
     *
     *
    */

    //re-enable interrupts after this one is handled
    interrupts();
}

bool isValidTile(char hexTile) {
  int row = (hexTile >> 4) & 0x0F; //Get the first hex digit of valid tile
  int col = hexTile & 0x0F; //Get the second hex digit of valid tile

  if (row >= 3 || col >= 3) {return false;}

  bool isValid = false;
  for (char validTile : validHexTiles) {
    if (validTile == hexTile) {
      isValid = true;
      break;
    }
  }
  
  return (isValid);
}