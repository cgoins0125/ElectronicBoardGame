#include "HardwareAPI.h"
#include "ArduinoLowPower.h"

HardwareAPI gameBoard;

char board[3][3] = {{' ', ' ', ' '},
                     {' ', ' ', ' '},
                     {' ', ' ', ' '}};

char currentPlayer = 'X'; 

void setup() {
    interrupts();
    for (port = 0 ; port <= 65 ; port++) {
      if (port != 20 && port != 21) {
        pinMode(port, INPUT_PULLUP);
        LowPower.attachInterruptWakeup(digitalPinToInterrupt(port), handleInterrupt, RISING); //Only trigger interrupts when magnet is brought close
      }
    }
    gameBoard.begin();
    gameBoard.turnOnMultipleTiles([0x00,0x01,0x02,0x10,0x11,0x12,0x20,0x21,0x22],9,'G')
    gameBoard.printLCD("Tic Tac Toe", "Player X Start");
}

void loop() {
    sleep(SLEEP_MODE_IDLE);
}

void handleInterrupt() {
    char tile = gameBoard.getInterruptTile(); // Wait for player selection
    if (tile == -1) return; // No input
    if (!isValidTile(tile)) return; //invalid tile
    noInterrupts(); //pause interrupts
    int row = (tile >> 4) & 0x0F; //Get the first hex digit of valid tile
    int col = tile & 0x0F; //Get the second hex digit of valid tile
    
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
            interrupts();
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
        char tile = (row << 4) | col;
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
    gameBoard.printLCD("Tic Tac Toe", "Player X Start");
    currentPlayer = 'X';
}

void toggleCurrentPlayer() {
  currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

bool isValidTile(char hexTile) {
  int row = (tile >> 4) & 0x0F; //Get the first hex digit of valid tile
  int col = tile & 0x0F; //Get the second hex digit of valid tile
  return (gameBoard[row][col] == ' ' && (hexTile == 0x20 || hexTile == 0x21 || hexTile == 0x22 ||
      hexTile == 0x10 || hexTile == 0x311|| hexTile == 0x12 ||
      hexTile == 0x00 || hexTile == 0x01 || hexTile == 0x02))
}
