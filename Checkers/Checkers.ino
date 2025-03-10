#include "Arduino.h"                        // Include the Arduino core library.
#include "HardwareAPI.h"                    // Include the provided Hardware API.
#include "Adafruit_LiquidCrystal.h"         // Include the LCD library.
#include <vector>                           // Include vector container for dynamic arrays.
#include <stdlib.h>                         // Include stdlib (for abs function).
#include <string.h>                         // Include string library (for strlen).

//---------------------------------------------------------------------
// Piece definitions for the checkers game.
//---------------------------------------------------------------------
enum Piece {
  EMPTY = 0,      // Represents an empty square.
  RED_MAN,        // Represents a red man (regular piece).
  RED_KING,       // Represents a red king (promoted piece).
  BLACK_MAN,      // Represents a black man.
  BLACK_KING      // Represents a black king.
};

//---------------------------------------------------------------------
// The CheckersGame class encapsulates the board state and game logic.
// It uses a board representation based on 0x88 notation (only indices
// where (tile & 0x88)==0 are valid). It manages moves, captures, and
// communicates with the Hardware API to light LEDs and update the LCD.
//---------------------------------------------------------------------
class CheckersGame {
public:
  // Constructor: Initialize the game with a reference to the hardware API.
  CheckersGame(HardwareAPI & api) 
    : api(api), redTurn(true), selectedTile(0xFF)  // redTurn starts true; no tile selected initially.
  {
    // Initialize all 128 board slots to EMPTY.
    for (int i = 0; i < 128; i++) {                 //128 is due to each tiles being equivalent to 8 bits
      board[i] = EMPTY;  // Set each board element to EMPTY.
    }
  }
  
  // Sets up the board with the starting positions for red and black pieces.
  void setupBoard(); //IDK how it knows when they are done setting up the board       ********
  
  // Called when a piece is lifted (removed from its square).
  void PieceLifted(char tile);// checked
  
  // Called when a piece is placed (set down) on a destination square.
  void PiecePlaced(char tile);// checked
  
  // Clears all LED highlights on the board.
  void clearHighlights();
  
  // Updates the LCD display to show which player's turn it is.
  void updateLCD();
  
private:
  HardwareAPI &api;            // Reference to the hardware API for controlling LEDs and LCD.
  Piece board[128];            // Array representing the board in 0x88 notation.
  bool redTurn;                // Boolean flag: true if it's red's turn, false if it's black's.
  char selectedTile;           // Holds the currently selected tile (0xFF means no selection).
  std::vector<char> legalMoves; // List of legal moves for the currently selected piece.
  
  // Returns a vector containing all legal destination tiles for the piece on the given tile.
  std::vector<char> getLegalMovesForPiece(char tile);
  
  // Helper: Returns true if the provided tile is a valid board square.
  bool isValidTile(char tile) { return ((tile & 0x88) == 0); }
  
  // Moves a piece from one tile to another, handling captures and promotions.
  void movePiece(char from, char to);
};

//---------------------------------------------------------------------
// setupBoard: Initializes the board with starting positions.
// - Red pieces are placed on dark squares in rows 0–2.
// - Black pieces are placed on dark squares in rows 5–7.
// - Light squares (where (row+col) % 2 != 0) remain empty.
//---------------------------------------------------------------------
void CheckersGame::setupBoard() {
  for (int row = 0; row < 8; row++) {              // Loop over all rows (0 to 7).
    for (int col = 0; col < 8; col++) {              // Loop over all columns (0 to 7).
    /* 
    tile is being converted to Binary with the upper 4 bits representing the row and the lower 4 representing the colomn.
    [row << 4 shifts the value over 4]
    */
      char tile = (row << 4) | col;                  // Compute tile value in 0x88 notation. 
      if (!isValidTile(tile)) continue;              // Skip if tile is not valid.
      if ((row + col) % 2 == 0) {                     // Only dark squares are used (even sum).
         if (row < 3) {                        // Rows 0 to 2: Red pieces
          board[tile] = RED_MAN;
          api.turnOnLED(tile, 'R');           // Light up tile in red
        } else if (row > 4) {                 // Rows 5 to 7: Black pieces
          board[tile] = BLACK_MAN;
          api.turnOnLED(tile, 'B');           // Light up tile in blue
        } else {                                     // For rows 3 and 4,
          board[tile] = EMPTY;                       // Leave the square empty.
        }
      } else {                                       // For light squares,
        board[tile] = EMPTY;                         // They remain empty.
      }
    }
  }
}

//---------------------------------------------------------------------
// getLegalMovesForPiece: Calculates all legal moves for the piece on the
// provided tile. It first checks for capturing moves (which are mandatory)
// and returns them exclusively if available. Otherwise, it returns simple
// diagonal moves.
//---------------------------------------------------------------------
std::vector<char> CheckersGame::getLegalMovesForPiece(char tile) {
  std::vector<char> moves;                          // Vector to hold legal moves.
  if (!isValidTile(tile)) return moves;             // If tile is invalid, return empty vector.
  Piece piece = board[tile];                        // Get the piece from the board.
  if (piece == EMPTY) return moves;                 // If no piece is present, return empty.
  
  int row = tile >> 4;                              // Extract row from the tile (upper nibble).
  int col = tile & 0x0F;                            // Extract column from the tile (lower nibble).
  
  // Define the four possible diagonal directions: down-left, down-right, up-left, up-right.
  int directions[4][2] = { {1, -1}, {1, 1}, {-1, -1}, {-1, 1} };
  int startDir = 0, endDir = 4;                      // Initialize to consider all directions.
  
  // For man pieces, restrict movement to "forward" direction.
  if (piece == RED_MAN) {
    startDir = 0; endDir = 2;                       // Red men move downward (increasing row).
  } else if (piece == BLACK_MAN) {
    startDir = 2; endDir = 4;                       // Black men move upward (decreasing row).
  }
  // Kings are allowed to move in all four directions, so startDir and endDir remain unchanged.
  
  // First, search for capturing moves.
  std::vector<char> captureMoves;                   // Vector to hold capture moves.
  for (int i = startDir; i < endDir; i++) {           // Loop through allowed directions.
    int dr = directions[i][0];                      // Row offset for this direction.
    int dc = directions[i][1];                      // Column offset for this direction.
    int midRow = row + dr;                          // Row of the adjacent square.
    int midCol = col + dc;                          // Column of the adjacent square.
    int destRow = row + 2 * dr;                     // Row of the landing square after a jump.
    int destCol = col + 2 * dc;                     // Column of the landing square after a jump.
    // Ensure the landing square is on the board.
    if (destRow >= 0 && destRow < 8 && destCol >= 0 && destCol < 8) {
      char midTile = (midRow << 4) | midCol;        // Calculate the tile of the piece being jumped over.
      char destTile = (destRow << 4) | destCol;       // Calculate the destination tile.
      if (board[destTile] == EMPTY) {                // Destination must be empty to move.
        Piece midPiece = board[midTile];            // Get the piece from the intermediate square.
        // For red pieces, check if the adjacent piece is black.
        if ((piece == RED_MAN || piece == RED_KING) &&
            (midPiece == BLACK_MAN || midPiece == BLACK_KING)) {
          captureMoves.push_back(destTile);         // Add capturing move for red.
        }
        // For black pieces, check if the adjacent piece is red.
        else if ((piece == BLACK_MAN || piece == BLACK_KING) &&
                 (midPiece == RED_MAN || midPiece == RED_KING)) {
          captureMoves.push_back(destTile);         // Add capturing move for black.
        }
      }
    }
  }
  // If any capture moves are found, return only those moves (as capturing is mandatory).
  /* This was removed because it should not be mandotory for a player to take
    if (!captureMoves.empty()) {
    return captureMoves;
  }
  */

  
  // If no captures are possible, check for simple (non-capturing) diagonal moves.
  for (int i = startDir; i < endDir; i++) {           // Loop through allowed directions.
    int dr = directions[i][0];                      // Row offset for this direction.
    int dc = directions[i][1];                      // Column offset for this direction.
    int destRow = row + dr;                         // Destination row for the move.
    int destCol = col + dc;                         // Destination column for the move.
    // Ensure the destination square is on the board.
    if (destRow >= 0 && destRow < 8 && destCol >= 0 && destCol < 8) {
      char destTile = (destRow << 4) | destCol;       // Compute the destination tile.
      if (board[destTile] == EMPTY) {                 // Check if the destination is empty.
        moves.push_back(destTile);                    // Add move to the list of legal moves.
      }
    }
  }
  return moves;                                     // Return the list of legal moves.
}

//---------------------------------------------------------------------
// clearHighlights: Turns off the LED indicator for every board square.
//---------------------------------------------------------------------
void CheckersGame::clearHighlights() {
  for (int row = 0; row =< 8; row++) {                // Loop through every row. added "=<"
    for (int col = 0; col =< 8; col++) {              // Loop through every column. added "=<"
      char tile = (row << 4) | col;                  // Compute tile value in 0x88 notation.
      api.turnOffLED(tile);                          // Use the hardware API to turn off the LED for this tile.
    }
  }
}

//---------------------------------------------------------------------
// movePiece: Moves a piece from the source tile ("from") to the destination tile ("to").
// - If the move is a jump (capture), removes the captured piece.
// - Promotes a man to a king if it reaches the far side of the board.
//---------------------------------------------------------------------
void CheckersGame::movePiece(char from, char to) {
  int fromRow = from >> 4;                          // Extract the source row.
  int fromCol = from & 0x0F;                        // Extract the source column.
  int toRow   = to   >> 4;                          // Extract the destination row.
  int toCol   = to   & 0x0F;                        // Extract the destination column.
  
  // Determine if the move is a capturing move (a jump covers 2 rows).
  bool isCapture = (abs(toRow - fromRow) == 2);
  
  board[to] = board[from];                          // Place the moving piece at the destination.
  board[from] = EMPTY;                              // Clear the source square.
  
  if (isCapture) {                                  // If the move was a capture:
    int capRow = (fromRow + toRow) / 2;              // Calculate the row of the captured piece.
    int capCol = (fromCol + toCol) / 2;              // Calculate the column of the captured piece.
    char capTile = (capRow << 4) | capCol;           // Compute the tile for the captured piece.
    board[capTile] = EMPTY;                          // Remove the captured piece from the board.
    api.turnOffLED(capTile);                         // Turn off any LED highlighting on the captured square.
  }
  
  // Check for promotion: a red man reaching the last row becomes a red king.
  if (board[to] == RED_MAN && toRow == 7)
    board[to] = RED_KING;                           // Promote red man to red king.
  // Check for promotion: a black man reaching the first row becomes a black king.
  if (board[to] == BLACK_MAN && toRow == 0)
    board[to] = BLACK_KING;                         // Promote black man to black king.
}

//---------------------------------------------------------------------
// PieceLifted: Called when a piece is lifted from the board by the player.
// - Verifies that the piece belongs to the current player.
// - Computes its legal moves and highlights those destination tiles with yellow LEDs.
// - Updates the LCD to indicate the selected tile.
//---------------------------------------------------------------------
void CheckersGame::PieceLifted(char tile) {
  if (!isValidTile(tile)) return;                   // Ignore if the tile is invalid.
  Piece piece = board[tile];                        // Retrieve the piece at the tile. [Is it black or red]
  if (piece == EMPTY) return;                       // Ignore if no piece is present
  // Check if the piece belongs to the player whose turn it is.
  if (redTurn && (piece != RED_MAN && piece != RED_KING)) return;
  if (!redTurn && (piece != BLACK_MAN && piece != BLACK_KING)) return;
  
  selectedTile = tile;                              // Set the selected tile.
  
  legalMoves = getLegalMovesForPiece(tile);         // Compute legal moves for the selected piece.
  
  for (char move : legalMoves) {                    // For every legal move:
    api.turnOnLED(move, 'Y');                       // Highlight the destination tile with a yellow LED.
  }
  
  char buf[17];                                     // Buffer for the LCD message.
  snprintf(buf, 17, "Slc: %X", tile);               // Format a message showing the selected tile in hex.
  api.PrintLCDL1(buf);                              // Display the message on the LCD's first line.
}

//---------------------------------------------------------------------
// PiecePlaced: Called when a player places a piece on a board square.
// - Validates that the destination is a legal move.
// - If valid, performs the move, handles captures and multi-captures,
//   and then switches turns if no additional capture is available.
//---------------------------------------------------------------------
void CheckersGame::PiecePlaced(char tile) {
  if (selectedTile == 0xFF) return;                 // If no piece is selected, do nothing.
  
  bool valid = false;                               // Flag to check if move is legal.
  for (char move : legalMoves) {                    // Check each legal move.
    if (move == tile) {                             // If destination matches a legal move:
      valid = true;                                // Mark the move as valid.
      break;                                       // Exit the loop.
    }
    else{
       api.PrintLCDL2("Invalid Move");                // Display an error message on the LCD.
    return;
    }
  }
  
  clearHighlights();                                // Clear all LED highlights before moving.
  
  char fromTile = selectedTile;                     // Save the original tile of the selected piece.
  
  movePiece(selectedTile, tile);                    // Execute the move from the selected tile to the destination.
  
  int fromRow = fromTile >> 4;                      // Get the source row.
  int toRow   = tile >> 4;                          // Get the destination row.

  bool didCapture = (abs(toRow - fromRow) == 2);      // Determine if the move was a capture (jump).
  
  if (didCapture) {                                 // If a capture was made:
    std::vector<char> furtherCaptures = getLegalMovesForPiece(tile); // Check for additional capturing moves.
    if (!furtherCaptures.empty()) {                 // If further captures are available:
      selectedTile = tile;                          // Keep the piece selected.
      legalMoves = furtherCaptures;                 // Update legal moves with further captures.
      for (char move : legalMoves) {                // Highlight each additional capture move.
        api.turnOnLED(move, 'Y');
      }
      api.PrintLCDL2("Multi-capture!");             // Inform the player about the multi-capture.
      return;                                       // Do not switch turns until capture sequence ends.
    }
  }
  
  selectedTile = 0xFF;                              // Clear the selected tile.
  legalMoves.clear();                               // Clear the list of legal moves.
  redTurn = !redTurn;                               // Switch turns to the other player.
  updateLCD();                                      // Update the LCD with the current turn information.
}

//---------------------------------------------------------------------
// updateLCD: Updates the LCD display to show which player's turn it is.
//---------------------------------------------------------------------
void CheckersGame::updateLCD() {
  if (redTurn)
    api.PrintLCD("Red's turn", "");                // Display "Red's turn" if it's red's turn.
  else
    api.PrintLCD("Black's turn", "");              // Display "Black's turn" if it's black's turn.
}

//---------------------------------------------------------------------
// coordToTile: Converts a coordinate string (e.g., "a3") into a tile in
// 0x88 notation. Returns 0xFF if the coordinate is invalid.
//---------------------------------------------------------------------
char coordToTile(const char* coord) {
  if (coord == NULL || strlen(coord) < 2) return 0xFF;  // Ensure the coordinate string is valid.
  char fileChar = coord[0];                        // First character: file letter (a-h).
  char rankChar = coord[1];                        // Second character: rank number (1-8).
  int col = fileChar - 'a';                        // Convert file to a column index (0-7).
  int row = rankChar - '1';                        // Convert rank to a row index (0-7).
  if (col < 0 || col > 7 || row < 0 || row > 7) return 0xFF; // Validate that row and column are within range.
  return (row << 4) | col;                         // Return the tile in 0x88 notation.
}

//---------------------------------------------------------------------
// Global objects and Arduino setup/loop functions.
//---------------------------------------------------------------------
CheckersGame *game;                                // Pointer to our CheckersGame object.
HardwareAPI hw;                                    // Create an instance of the HardwareAPI.

//---------------------------------------------------------------------
// setup: Arduino initialization function.
// - Initializes serial communication and the hardware.
// - Creates and sets up the checkers game board.
// - Updates the LCD with the starting player's turn.
//---------------------------------------------------------------------
void setup() {
  Serial.begin(9600);                              // Begin serial communication at 9600 baud. This affects the speed of the communication in the Arduino
  hw.begin();                                      // Initialize the hardware API (LEDs, LCD, etc.).
  
  game = new CheckersGame(hw);                     // Create a new CheckersGame instance.
  game->setupBoard();                              // Set up the board with the initial piece configuration.
  game->updateLCD();                               // Update the LCD to display which player's turn it is.
  
  Serial.println("Checkers Game Started");         // Output a start message to the serial monitor.
  Serial.println("Commands: L <coord> (lift), P <coord> (place)"); // Display the command instructions.
}

//---------------------------------------------------------------------
// loop: Arduino main loop.
// - Checks for serial input to simulate piece lift and placement.
// - Interprets commands and calls the appropriate CheckersGame methods.
//---------------------------------------------------------------------
void loop() {
  if (Serial.available() > 0) {                    // If there is serial input available,
    String input = Serial.readStringUntil('\n');   // Read input until newline.
    input.trim();                                  // Remove any leading/trailing whitespace.
    if (input.length() < 3) return;                // If the input is too short, ignore it.
    
    char command = input.charAt(0);                // The first character is the command (L or P).
    String coordStr = input.substring(2);          // The rest is the coordinate string.
    coordStr.trim();                               // Trim any extra whitespace from the coordinate.
    char tile = coordToTile(coordStr.c_str());     // Convert the coordinate string to a tile.
    if (tile == 0xFF) {                            // If the conversion fails,
      Serial.println("Invalid coordinate");        // notify the user and exit.
      return;
    }
    
    // Process the command based on the first character.
    if (command == 'L' || command == 'l') {         // If command is lift:
      game->PieceLifted(tile);                   // Call the PieceLifted method.
      Serial.print("Lifted piece at ");            // Inform via serial monitor.
      Serial.println(coordStr);
    } 
    else if (command == 'P' || command == 'p') {      // If command is place:
      game->PiecePlaced(tile);                   // Call the PiecePlaced method.
      Serial.print("Placed piece at ");            // Inform via serial monitor.
      Serial.println(coordStr);
    }
  }
}
