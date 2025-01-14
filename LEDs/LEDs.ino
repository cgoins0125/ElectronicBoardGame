void setup() {
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
}

void loop() {
  HardwareAPI::turnOnLED(13);
  delay(5000);
  HardwareAPI::turnOffLED(13);
  delay(5000);
  HardwareAPI::changeLEDcolor(13, 'R'); //00
  delay(5000);
  HardwareAPI::changeLEDcolor(13, 'B'); //01
  delay(5000);
  HardwareAPI::changeLEDcolor(13, 'G'); //10
  delay(5000);
  HardwareAPI::changeLEDcolor(13, 'Y'); //11
}

class HardwareAPI {
  private:

  public:
    static void turnOnLED(char port) {
      digitalWrite(port, HIGH);
    }

    static void turnOffLED(char port) {
      digitalWrite(port, LOW);
    }

    static void changeLEDcolor(char port, char color) {
      switch (port) {
      case 13:
        switch (color) {
          case 'R':
            digitalWrite(14, LOW);
            digitalWrite(15, LOW);
            break;
          case 'B':
            digitalWrite(14, LOW);
            digitalWrite(15, HIGH);
            break;
          case 'G':
            digitalWrite(14, HIGH);
            digitalWrite(15, LOW);
            break;
          case 'Y':
            digitalWrite(14, HIGH);
            digitalWrite(15, HIGH);
            break;
        }
        break;
      

      case 16:

      default:  
      }
    }
}