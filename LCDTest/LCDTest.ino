/*  The circuit:
 * 5V to Arduino 5V pin
 * GND to Arduino GND pin
 * CLK to SCL - Pin 21
 * DAT to SDA - Pin 20
*/

// include the library code:
#include "Adafruit_LiquidCrystal.h"

// Connect via i2c, default address #0 (A0-A2 not jumpered)
Adafruit_LiquidCrystal lcd(0);

//The hardware API class
class HardwareAPI {
  private:
    int maxLength=16;
  public:
    static void PrintLCD(const char c1[], const char c2[]) {
      ClearLCD();
      lcd.setCursor(0, 0);
      lcd.print(c1);
      lcd.setCursor(1, 0);
      lcd.print(c2);
    }

    static void PrintLCDL1(const char str[]) {
      ClearLCDL1();
      lcd.setCursor(0, 0);
      lcd.print(str);
    }

    static void PrintLCDL2(const char str[]) {
      ClearLCDL2();
      lcd.setCursor(0, 1);
      lcd.print(str);
    }    

    static void ClearLCD() {
      ClearLCDL1();
      ClearLCDL2();
    }

    static void ClearLCDL1() {
      lcd.setCursor(0, 0);
      lcd.print("                ");
    }

    static void ClearLCDL2() {
      lcd.setCursor(0, 1);
      lcd.print("                ");
    }
};

void setup() {
  // put your setup code here
 
  Serial.begin(115200);
  while(!Serial);
  Serial.println("LCD Character Backpack I2C Test.");

  // set up the LCD's number of rows and columns:
  if (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");
    while(1);
  }
  Serial.println("Backpack init'd.");

}

void loop() {
  HardwareAPI::PrintLCDL1("Hello, World");
  delay(3000);
  HardwareAPI::PrintLCDL1("Chris");
  delay(3000);
}