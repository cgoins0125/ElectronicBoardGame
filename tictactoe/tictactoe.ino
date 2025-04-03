#include "HardwareAPI.h"

HardwareAPI gameBoard;

char board[3][3] = {{' ', ' ', ' '},
                     {' ', ' ', ' '},
                     {' ', ' ', ' '}};

char currentPlayer = 'X';

std::array<char, 9> validHexTiles = {0x00,0x01,0x02,0x10,0x11,0x12,0x20,0x21,0x22};

void setup() {
    interrupts();
    gameBoard.begin();
    for (char tile : validHexTiles) {
        int port = gameBoard.getTilePort(tile);
        if (port == -1) break;
        pinMode(port, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(port), handleInterrupt, RISING); //Only trigger interrupts when magnet is brought close
      }
    gameBoard.turnOnMultipleTiles(validHexTiles,'G'); 
    gameBoard.printLCD("Tic Tac Toe", "Player X Start");
}

void loop() {
    delay(1000);
}

void handleInterrupt() {
    char tile = gameBoard.getInterruptTile(); // Wait for player selection
    if (tile == 0xFF) return; // No input
    if (!isValidTile(tile)) return; //invalid tile
    noInterrupts(); //pause interrupts
    int row = (tile >> 4) & 0x0F; //Get the first hex digit of valid tile with bitwishe shift to the right & a bit mask on shifted bits
    int col = tile & 0x0F; //Get the second hex digit of valid tile using a bit mask on 4 LSBs
    
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
    interrupts();
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
  }
  delay(500);
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
    interrupts();
    gameBoard.turnOnMultipleTiles(validHexTiles,'G'); 
    gameBoard.printLCD("Tic Tac Toe", "Player X Start");
    currentPlayer = 'X';
}

void toggleCurrentPlayer() {
  currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
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
  
  return (board[row][col] == ' ' && isValid);
}
