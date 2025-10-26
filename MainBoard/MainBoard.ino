//Keep in mind, this will only work for testing with the Giga R1, not the UNO R3 due to the limited external interrupt pins
const int inputAddress[] = {3,4,5}; //inputs to encoders
const int encoderAddress[] = {6,7,8}; //select bits for multiplexers - represents the encoder addresses
const int interruptPins[] = {9,10,11,12,13,14,15,16};
const int interruptPinAddress[] = {0b000,0b001,0b010,0b011,0b100,0b101,0b110,0b111}; //address of the encoders (0-7)
const int enable = 2;
volatile int encoder = 0b000;
volatile int input = 0b000;
volatile int tile = 0b000000;
volatile bool activeInput = false;

void setup(){
    Serial.begin(9600);
    //Set up enable pin
    pinMode(enable, OUTPUT);
    digitalWrite(enable, LOW);
    //Set up input address pins as inputs
    for (int i = 0; i < 3; i++){
        pinMode(inputAddress[i], INPUT);
    }
    //Set up encoder address pins as outputs
    for (int i = 0; i < 3; i++){
        pinMode(encoderAddress[i], OUTPUT);
    }
    //Set up interrupt(GS) pins - 9 = E0...17 = E7
    for (int i = 0; i < 8; i++){
        attachInterrupt(digitalPinToInterrupt(interruptPins[i]), interruptHandler, LOW);
    }
    
}

void loop(){
    interrupts();
    //Print the output (active input)
    if(activeInput != false){
        Serial.print("Tile ");
        Serial.print(tile);
        Serial.print("'s state changed.");
        activeInput = false;
    }
    //Serial.print("I");
}

void interruptHandler(){
    //Determine the encoder address and write to encoderAddress pins
    for (int i = 0; i < 8; i++){
        if (digitalRead(interruptPins[i]) == LOW){
            encoder = interruptPinAddress[i];
        }
    }
    //Write to encoderAddress pins
    digitalWrite(encoderAddress[0], encoder && 0b100);
    digitalWrite(encoderAddress[1], encoder && 0b010);
    digitalWrite(encoderAddress[2], encoder && 0b001);
    //Read from the inputAddress
    input = digitalRead(inputAddress[0] << 2) + digitalRead(inputAddress[1] < 1) + digitalRead(inputAddress[2]);
    //Set tile address - combine encoder and input addresses (shift encoder left three times)
    tile = (encoder << 3) + ~input;
    //Set activeInput as true to print tile address
    activeInput = true;
}