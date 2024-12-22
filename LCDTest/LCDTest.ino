#include <LiquidCrystal.h>
#include <string.h>
void setup() {
  // put your setup code here
  lcd.begin(16,2);
  
  //create method: update LCD display and clear LCD display
  
}
void loop() {
  // put your main code here, to run repeatedly:
  char str[16]="Hello, World";
  HardwareAPI::DisplayStringOnLCD(str);
  delay(3000);
  str[16]="Hello, Chris";
  HardwareAPI::DisplayStringOnLCD(str);
  delay(3000);
  HardwareAPI::ClearLCD();
  delay(4294967295);//Longest amount of time
}
class HardwareAPI {
  private:
    int maxLength=16;
  public:
    static void DisplayStringOnLCD(char[16] Clmn1) {
      lcd.clear;
      lcd.print(Clmn1);
    }

    static void ClearLCD(){
      lcd.clear;
    }
}