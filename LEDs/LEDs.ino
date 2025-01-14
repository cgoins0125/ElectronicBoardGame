class HardwareAPI {
  private:
public:
    static void turnOnLED(char hexTile, char color) {
      changeLEDcolor(hexTile, color);
      switch (hexTile) {
      case 0x00:
        digitalWrite(24, LOW);
        break;
      }
    }

    static void turnOffLED(char hexTile) {
      switch (hexTile) {
      case 0x00:
        digitalWrite(24, HIGH);
        break;
      }
    }

    /*
    method: changeLEDcolor
    function: changes LED color for specified tile to specified color
    params:
      hexTile:
        board is represented using the "0x88" system. 
        Pass a char between 0x00 and 0x88.
          examples:
            "a1" would be 0x00 (rank 8 = 0x0, file a = 0x0)
            "h8" would be 0x77 (rank 1 = 0x7, file h = 0x7)
      color: enum: ['R','G','B','Y']
        'R' - Red
        'G' - Green
        'B' - Blue
        'Y' - Yellow
    */

    static void changeLEDcolor(char hexTile, char color) {
      switch (hexTile) {
      case 0x00:
        switch (color) {
          case 'R':
            digitalWrite(26, LOW);
            digitalWrite(28, LOW);
            break;
          case 'B':
            digitalWrite(26, LOW);
            digitalWrite(28, HIGH);
            break;
          case 'Y':
            digitalWrite(26, HIGH);
            digitalWrite(28, LOW);
            break;
          case 'G':
            digitalWrite(26, HIGH);
            digitalWrite(28, HIGH);
            break;
          default:
            // Log invalid color case
            Serial.println("Invalid color input");
            break;
        }
        break;
      default:
        Serial.println("Invalid tile input");
        break;
      //invalid tile, do nothing
    }
  }
};

void setup() {
  Serial.begin(115200);
  while(!Serial);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);
}

void loop() {
  Serial.println("On - Green");
  HardwareAPI::turnOnLED(0x00, 'G');
  delay(5000);
  Serial.println("Red");
  HardwareAPI::changeLEDcolor(0x00, 'R');
  delay(5000);
  Serial.println("Blue");
  HardwareAPI::changeLEDcolor(0x00, 'B');
  delay(5000);
  Serial.println("Green");
  HardwareAPI::changeLEDcolor(0x00, 'G');
  delay(5000);
  Serial.println("Yellow");
  HardwareAPI::changeLEDcolor(0x00, 'Y');
  delay(5000);
  Serial.println("Off");
  HardwareAPI::turnOffLED(0x00);
  delay(5000);
}