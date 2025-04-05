#include "HardwareAPI.h"

//These are the tiles being used for tic tac toe - edit this for game being programmed
std::vector<char> validHexTiles = {0x00,0x01,0x02,0x10,0x11,0x12,0x20,0x21,0x22};

//Instantiate the gameBoard object
HardwareAPI gameBoard(validHexTiles);\

//tic tac toe specific variables for keeping up with Xs and Os
char board[3][3] = {{' ', ' ', ' '},
                     {' ', ' ', ' '},
                     {' ', ' ', ' '}};
char currentPlayer = 'X';

void setup() {
    HardwareAPI::setInstance(&gameBoard);
    /* copy the following lines exactly only changing interrupt trigger as needed */
    gameBoard.begin();
    //This method turns all valid tiles green for tic tac toe - **note maximum on tile are 32.
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
    int row = gameBoard.getRow(tile);
    int col = gameBoard.getCol(tile);
        
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
  int row = gameBoard.getRow(hexTile);
  int col = gameBoard.getCol(hexTile);
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
