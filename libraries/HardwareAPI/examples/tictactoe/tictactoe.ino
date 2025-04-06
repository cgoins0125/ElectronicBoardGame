#include "HardwareAPI.h"

//These are the tiles being used for tic tac toe - edit this for game being programmed
// std::vector<char> validHexTiles = {0x50, 0x51, 0x52, 0x60, 0x61, 0x62, 0x70, 0x71, 0x72};
// std::vector<char> validHexTiles = {0x51, 0x52, 0x53, 0x61, 0x62, 0x63, 0x71, 0x72, 0x73};
// std::vector<char> validHexTiles = {0x52, 0x53, 0x54, 0x62, 0x63, 0x64, 0x72, 0x73, 0x74};
// std::vector<char> validHexTiles = {0x53, 0x54, 0x55, 0x63, 0x64, 0x65, 0x73, 0x74, 0x75};
// std::vector<char> validHexTiles = {0x54, 0x55, 0x56, 0x64, 0x65, 0x66, 0x74, 0x75, 0x76};
// std::vector<char> validHexTiles = {0x55, 0x56, 0x57, 0x65, 0x66, 0x67, 0x75, 0x76, 0x77};
// std::vector<char> validHexTiles = {0x40, 0x41, 0x42, 0x50, 0x51, 0x52, 0x60, 0x61, 0x62};
// std::vector<char> validHexTiles = {0x41, 0x42, 0x43, 0x51, 0x52, 0x53, 0x61, 0x62, 0x63};
// std::vector<char> validHexTiles = {0x42, 0x43, 0x44, 0x52, 0x53, 0x54, 0x62, 0x63, 0x64};
// std::vector<char> validHexTiles = {0x43, 0x44, 0x45, 0x53, 0x54, 0x55, 0x63, 0x64, 0x65};
// std::vector<char> validHexTiles = {0x44, 0x45, 0x46, 0x54, 0x55, 0x56, 0x64, 0x65, 0x66};
// std::vector<char> validHexTiles = {0x45, 0x46, 0x47, 0x55, 0x56, 0x57, 0x65, 0x66, 0x67};
// std::vector<char> validHexTiles = {0x30, 0x31, 0x32, 0x40, 0x41, 0x42, 0x50, 0x51, 0x52};
// std::vector<char> validHexTiles = {0x31, 0x32, 0x33, 0x41, 0x42, 0x43, 0x51, 0x52, 0x53};
// std::vector<char> validHexTiles = {0x32, 0x33, 0x34, 0x42, 0x43, 0x44, 0x52, 0x53, 0x54};
// std::vector<char> validHexTiles = {0x33, 0x34, 0x35, 0x43, 0x44, 0x45, 0x53, 0x54, 0x55};
// std::vector<char> validHexTiles = {0x34, 0x35, 0x36, 0x44, 0x45, 0x46, 0x54, 0x55, 0x56};
// std::vector<char> validHexTiles = {0x35, 0x36, 0x37, 0x45, 0x46, 0x47, 0x55, 0x56, 0x57};
// std::vector<char> validHexTiles = {0x20, 0x21, 0x22, 0x30, 0x31, 0x32, 0x40, 0x41, 0x42};
// std::vector<char> validHexTiles = {0x21, 0x22, 0x23, 0x31, 0x32, 0x33, 0x41, 0x42, 0x43};
// std::vector<char> validHexTiles = {0x22, 0x23, 0x24, 0x32, 0x33, 0x34, 0x42, 0x43, 0x44};
// std::vector<char> validHexTiles = {0x23, 0x24, 0x25, 0x33, 0x34, 0x35, 0x43, 0x44, 0x45};
// std::vector<char> validHexTiles = {0x24, 0x25, 0x26, 0x34, 0x35, 0x36, 0x44, 0x45, 0x46};
// std::vector<char> validHexTiles = {0x25, 0x26, 0x27, 0x35, 0x36, 0x37, 0x45, 0x46, 0x47};
// std::vector<char> validHexTiles = {0x10, 0x11, 0x12, 0x20, 0x21, 0x22, 0x30, 0x31, 0x32};
// std::vector<char> validHexTiles = {0x11, 0x12, 0x13, 0x21, 0x22, 0x23, 0x31, 0x32, 0x33};
// std::vector<char> validHexTiles = {0x12, 0x13, 0x14, 0x22, 0x23, 0x24, 0x32, 0x33, 0x34};
// std::vector<char> validHexTiles = {0x13, 0x14, 0x15, 0x23, 0x24, 0x25, 0x33, 0x34, 0x35};
// std::vector<char> validHexTiles = {0x14, 0x15, 0x16, 0x24, 0x25, 0x26, 0x34, 0x35, 0x36};
// std::vector<char> validHexTiles = {0x15, 0x16, 0x17, 0x25, 0x26, 0x27, 0x35, 0x36, 0x37};
// std::vector<char> validHexTiles = {0x00, 0x01, 0x02, 0x10, 0x11, 0x12, 0x20, 0x21, 0x22};
// std::vector<char> validHexTiles = {0x01, 0x02, 0x03, 0x11, 0x12, 0x13, 0x21, 0x22, 0x23};
// std::vector<char> validHexTiles = {0x02, 0x03, 0x04, 0x12, 0x13, 0x14, 0x22, 0x23, 0x24};
// std::vector<char> validHexTiles = {0x03, 0x04, 0x05, 0x13, 0x14, 0x15, 0x23, 0x24, 0x25};
 std::vector<char> validHexTiles = {0x04, 0x05, 0x06, 0x14, 0x15, 0x16, 0x24, 0x25, 0x26};
// std::vector<char> validHexTiles = {0x05, 0x06, 0x07, 0x15, 0x16, 0x17, 0x25, 0x26, 0x27};

//Instantiate the gameBoard object
HardwareAPI gameBoard(validHexTiles);

//tic tac toe specific variables for keeping up with Xs and Os
char board[3][3] = {{' ', ' ', ' '},
                     {' ', ' ', ' '},
                     {' ', ' ', ' '}};
char currentPlayer = 'X';

void setup() {
    HardwareAPI::setInstance(&gameBoard);
    /* copy the following lines exactly only changing interrupt trigger as needed */
    gameBoard.begin();
    interrupts();
    gameBoard.turnOnMultipleTiles(validHexTiles,'G'); 
    gameBoard.printLCD("Tic Tac Toe", "Player X Start");
}

void loop() {
    //do nothing unless player has triggered an interrupt 
    if (gameBoard.isInterruptDetected()) {
      handleInterrupts(gameBoard.getInterruptTile());
      gameBoard.setInterruptTile(0xFF);
      gameBoard.setInterruptDetected(false);
    }
}

void handleInterrupts(char tile) {
    if (tile == 0xFF) return; //interupt tile was not found
    if (!isValidTile(tile)) return; //invalid tile for tic tac toe
    int rowOffset = gameBoard.getRow(validHexTiles[0]);
    int row = gameBoard.getRow(tile);
    row -= rowOffset;
    int colOffset = gameBoard.getCol(validHexTiles[0]);
    int col = gameBoard.getCol(tile);
    col -= colOffset;
        
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
    int rowStart = gameBoard.getRow(validHexTiles[0]);
    int rowEnd = gameBoard.getRow(validHexTiles[8]);
    int colStart = gameBoard.getCol(validHexTiles[0]);
    int colEnd = gameBoard.getCol(validHexTiles[8]);
    for (int row = rowStart; row <= rowEnd; row++) {
      for (int col = colStart; col <= colEnd ; col++) {
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
    int rowOffset = gameBoard.getRow(validHexTiles[0]);
    int row = gameBoard.getRow(hexTile);
    row -= rowOffset;
    int colOffset = gameBoard.getCol(validHexTiles[0]);
    int col = gameBoard.getCol(hexTile);
    col -= colOffset;
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