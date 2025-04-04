#include "HardwareAPI.h"

//Instantiate the gameBoard object
HardwareAPI gameBoard;
volatile bool interruptDetected = false;
volatile char interruptTile;

//These are the tiles being used for tic tac toe - edit this for game being programmed - be sure to specify the size (9 tiles used for this game)
std::array<char, 9> validHexTiles = {0x00,0x01,0x02,0x10,0x11,0x12,0x20,0x21,0x22};

//tic tac toe specific variables for keeping up with Xs and Os
char board[3][3] = {{' ', ' ', ' '},
                     {' ', ' ', ' '},
                     {' ', ' ', ' '}};
char currentPlayer = 'X';


void (*ISR_map[69])(void); // Array to hold ISR function pointers

void setup() {

    // Assign ISRs to the ISR_map array for each port
    ISR_map[0] = ISR_0;
    ISR_map[1] = ISR_1;
    ISR_map[2] = ISR_2;
    ISR_map[3] = ISR_3;
    ISR_map[4] = ISR_4;
    ISR_map[5] = ISR_5;
    ISR_map[6] = ISR_6;
    ISR_map[7] = ISR_7;
    ISR_map[8] = ISR_8;
    ISR_map[67] = ISR_67; //Port 9 broken for interrupts
    ISR_map[10] = ISR_10;
    ISR_map[11] = ISR_11;
    ISR_map[12] = ISR_12;
    ISR_map[13] = ISR_13;
    ISR_map[14] = ISR_14;
    ISR_map[15] = ISR_15;
    ISR_map[16] = ISR_16;
    ISR_map[68] = ISR_68; // Port 17 broken for interrupts
    ISR_map[18] = ISR_18;
    ISR_map[19] = ISR_19;
    //Skip 20 and 21
    ISR_map[22] = ISR_22;
    ISR_map[23] = ISR_23;
    ISR_map[24] = ISR_24;
    ISR_map[25] = ISR_25;
    ISR_map[26] = ISR_26;
    ISR_map[27] = ISR_27;
    ISR_map[28] = ISR_28;
    ISR_map[29] = ISR_29;
    ISR_map[30] = ISR_30;
    ISR_map[31] = ISR_31;
    ISR_map[32] = ISR_32;
    ISR_map[33] = ISR_33;
    ISR_map[34] = ISR_34;
    ISR_map[35] = ISR_35;
    ISR_map[36] = ISR_36;
    ISR_map[37] = ISR_37;
    ISR_map[38] = ISR_38;
    ISR_map[39] = ISR_39;
    ISR_map[40] = ISR_40;
    ISR_map[41] = ISR_41;
    ISR_map[42] = ISR_42;
    ISR_map[43] = ISR_43;
    ISR_map[44] = ISR_44;
    ISR_map[45] = ISR_45;
    ISR_map[46] = ISR_46;
    ISR_map[47] = ISR_47;
    ISR_map[48] = ISR_48;
    ISR_map[49] = ISR_49;
    ISR_map[50] = ISR_50;
    ISR_map[51] = ISR_51;
    ISR_map[52] = ISR_52;
    ISR_map[53] = ISR_53;
    ISR_map[54] = ISR_54;
    ISR_map[55] = ISR_55;
    ISR_map[56] = ISR_56;
    ISR_map[57] = ISR_57;
    ISR_map[58] = ISR_58;
    ISR_map[59] = ISR_59;
    ISR_map[60] = ISR_60;
    ISR_map[61] = ISR_61;
    ISR_map[62] = ISR_62;
    ISR_map[63] = ISR_63;
    ISR_map[64] = ISR_64;
    ISR_map[65] = ISR_65; //Port 66 broken for interrupts

    /* copy the following lines exactly only changing interrupt trigger as needed */
    Serial.begin(9600);
    while(!Serial)
    gameBoard.begin();
    int port = 0;
    for (char tile : validHexTiles) { //Loop over the tiles needed for the game
        port = gameBoard.getTilePort(tile); //get port that is mapped to the tile
        Serial.print("port:");
        Serial.println(port);
        if (port == -1) break;
        pinMode(port, INPUT_PULLUP);
        Serial.println("Port set as INPUT_PULLUP");

        /*
         * RISING: Only trigger interrupts when game piece is brought close to tile
         * FALLING: Only trigger interrupts when game piece is taken away from tile
         * CHANGING: trigger interrupts when game piece is brought close to or taken away from tile
        */
        if (digitalPinToInterrupt(port) == NOT_AN_INTERRUPT) {
          Serial.println("Selected port is not interrupt-capable, skipping.");
          continue;
        } else {
        attachInterrupt(digitalPinToInterrupt(port), ISR_map[port], RISING);}
        Serial.println("Port set as interrupt");
    }
    //This method turns all valid tiles green for tic tac toe - **note maximum on tile are 32.
    interrupts();
    gameBoard.turnOnMultipleTiles(validHexTiles,'G'); 
    gameBoard.printLCD("Tic Tac Toe", "Player X Start");
}

void loop() {
    //do nothing unless player has triggered an interrupt 
    if (interruptDetected) {
      handleInterrupts(interruptTile);
      interruptDetected = false;
    }
}

void handleInterrupts(char tile) {
    int row = (tile >> 4) & 0x0F; //Get the first hex digit of valid tile with bitwishe shift to the right & a bit mask on shifted bits
    int col = tile & 0x0F; //Get the second hex digit of valid tile using a bit mask on 4 LSBs
    if (tile == 0xFF) return; //interupt tile was not found
    if (!isValidTile(tile)) return; //invalid tile for tic tac toe - this method was created below and is not part of the API
    
    //tic tac toe logic below
    if (board[row][col] == ' ') {
        board[row][col] = currentPlayer;
        gameBoard.changeLEDcolor(tile, (currentPlayer == 'X') ? 'R' : 'B');
        
        if (isWinner()) {
            gameBoard.printLCD("Winner:", (currentPlayer == 'X') ? "Player X" : "Player O");
            flashWinningBoard();
            resetGame();
        } else if (isBoardFull()) {
            gameBoard.printLCD("Game Over", "It's a Tie!");
            delay(5000);
            resetGame();
        } else {
            toggleCurrentPlayer();
            gameBoard.printLCD("Player Turn", (currentPlayer == 'X') ? "Player X" : "Player O");
        }
    }
}

bool isWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) return true;
        if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) return true;
    }
    if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) return true;
    if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) return true;
    return false;
}

void flashWinningBoard() {
  for (int i = 0; i < 5; i++) { // Flash 5 times
    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < 3; col++) {
        char tile = (row << 4) | col; //create hex value from two ints
        gameBoard.turnOnLED(tile, (i % 2 == 0) ? 'R' : 'B');
      }
    }
    delay(500);
  }
}

bool isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

void resetGame() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
    gameBoard.clearLCD();
    gameBoard.turnOnMultipleTiles(validHexTiles,'G'); 
    gameBoard.printLCD("Tic Tac Toe", "Player X Start");
    currentPlayer = 'X';
}

void toggleCurrentPlayer() {
  currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

bool isValidTile(char hexTile) {
  Serial.println("checking if tile is valid");
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
  return (board[row][col] == ' ' && isValid);
}


/*
-------------------------------------------------
ISRs
-------------------------------------------------
*/
void ISR_0() { interruptTile = 0x00; interruptDetected = true; }
void ISR_1() { interruptTile = 0x01; interruptDetected = true; }
void ISR_2() { interruptTile = 0x02; interruptDetected = true; }
void ISR_3() { interruptTile = 0x03; interruptDetected = true; }
void ISR_4() { interruptTile = 0x04; interruptDetected = true; }
void ISR_5() { interruptTile = 0x05; interruptDetected = true; }
void ISR_6() { interruptTile = 0x06; interruptDetected = true; }
void ISR_7() { interruptTile = 0x07; interruptDetected = true; }

void ISR_8() { interruptTile = 0x10; interruptDetected = true; }
void ISR_67() { interruptTile = 0x11; interruptDetected = true; }
void ISR_10() { interruptTile = 0x12; interruptDetected = true; }
void ISR_11() { interruptTile = 0x13; interruptDetected = true; }
void ISR_12() { interruptTile = 0x14; interruptDetected = true; }
void ISR_13() { interruptTile = 0x15; interruptDetected = true; }
void ISR_14() { interruptTile = 0x16; interruptDetected = true; }
void ISR_15() { interruptTile = 0x17; interruptDetected = true; }

void ISR_16() { interruptTile = 0x20; interruptDetected = true; }
void ISR_68() { interruptTile = 0x21; interruptDetected = true; }
void ISR_18() { interruptTile = 0x22; interruptDetected = true; }
void ISR_19() { interruptTile = 0x23; interruptDetected = true; }
// Skipping ISR_20 and ISR_21 for I2C
void ISR_22() { interruptTile = 0x24; interruptDetected = true; }
void ISR_23() { interruptTile = 0x25; interruptDetected = true; }
void ISR_24() { interruptTile = 0x26; interruptDetected = true; }
void ISR_25() { interruptTile = 0x27; interruptDetected = true; }

void ISR_26() { interruptTile = 0x30; interruptDetected = true; }
void ISR_27() { interruptTile = 0x31; interruptDetected = true; }
void ISR_28() { interruptTile = 0x32; interruptDetected = true; }
void ISR_29() { interruptTile = 0x33; interruptDetected = true; }
void ISR_30() { interruptTile = 0x34; interruptDetected = true; }
void ISR_31() { interruptTile = 0x35; interruptDetected = true; }
void ISR_32() { interruptTile = 0x36; interruptDetected = true; }
void ISR_33() { interruptTile = 0x37; interruptDetected = true; }

void ISR_34() { interruptTile = 0x40; interruptDetected = true; }
void ISR_35() { interruptTile = 0x41; interruptDetected = true; }
void ISR_36() { interruptTile = 0x42; interruptDetected = true; }
void ISR_37() { interruptTile = 0x43; interruptDetected = true; }
void ISR_38() { interruptTile = 0x44; interruptDetected = true; }
void ISR_39() { interruptTile = 0x45; interruptDetected = true; }
void ISR_40() { interruptTile = 0x46; interruptDetected = true; }
void ISR_41() { interruptTile = 0x47; interruptDetected = true; }

void ISR_42() { interruptTile = 0x50; interruptDetected = true; }
void ISR_43() { interruptTile = 0x51; interruptDetected = true; }
void ISR_44() { interruptTile = 0x52; interruptDetected = true; }
void ISR_45() { interruptTile = 0x53; interruptDetected = true; }
void ISR_46() { interruptTile = 0x54; interruptDetected = true; }
void ISR_47() { interruptTile = 0x55; interruptDetected = true; }
void ISR_48() { interruptTile = 0x56; interruptDetected = true; }
void ISR_49() { interruptTile = 0x57; interruptDetected = true; }

void ISR_50() { interruptTile = 0x60; interruptDetected = true; }
void ISR_51() { interruptTile = 0x61; interruptDetected = true; }
void ISR_52() { interruptTile = 0x62; interruptDetected = true; }
void ISR_53() { interruptTile = 0x63; interruptDetected = true; }
void ISR_54() { interruptTile = 0x64; interruptDetected = true; }
void ISR_55() { interruptTile = 0x65; interruptDetected = true; }
void ISR_56() { interruptTile = 0x66; interruptDetected = true; }
void ISR_57() { interruptTile = 0x67; interruptDetected = true; }

void ISR_58() { interruptTile = 0x70; interruptDetected = true; }
void ISR_59() { interruptTile = 0x71; interruptDetected = true; }
void ISR_60() { interruptTile = 0x72; interruptDetected = true; }
void ISR_61() { interruptTile = 0x73; interruptDetected = true; }
void ISR_62() { interruptTile = 0x74; interruptDetected = true; }
void ISR_63() { interruptTile = 0x75; interruptDetected = true; }
void ISR_64() { interruptTile = 0x76; interruptDetected = true; }
void ISR_65() { interruptTile = 0x77; interruptDetected = true; }