

#include <Arduino.h>
#include <RotaryEncoder.h>

#include <Keypad.h>


  int ButtonState = 0;

const byte ROWS = 3; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'A','B','C','D'},
  {'1','2','3','4'},
  {'W','X','Y','Z'},
};
byte rowPins[ROWS] = {12,11,10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6,7,8,9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define PIN_IN1 A2
#define PIN_IN2 A3
#define input_A A4

RotaryEncoder encoderB(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);


#define PIN_IN3 5
#define PIN_IN4 4

RotaryEncoder encoderD(PIN_IN3, PIN_IN4, RotaryEncoder::LatchMode::TWO03);


#define PIN_IN5 A1
#define PIN_IN6 A0 

RotaryEncoder encoderC(PIN_IN5, PIN_IN6, RotaryEncoder::LatchMode::TWO03);

#define PIN_IN7 A6
#define PIN_IN8 A7

RotaryEncoder encoderA(PIN_IN7, PIN_IN8, RotaryEncoder::LatchMode::TWO03);
void setup()
{
  Serial.begin(115200);
  while(! Serial);
  Serial.println("SimplePollRotator example for the RotaryEncoder library.");
} 

void loop()
{
  send
  clear
  encoder1();
  encoder2();
  encoder3();
  encoder4();
  // switches();
  runKey();
} 

void encoder1(){
  static int pos = 0;
  encoderA.tick();

  int newPos = encoderA.getPosition();
  if (pos != newPos) {
    Serial.print("encoderA: ");
    Serial.println((int)(encoderA.getDirection()));
    pos = newPos;
  } 

}

void encoder2(){
  static int posB = 0;
  encoderB.tick();

  int newPosB = encoderB.getPosition();
  if (posB != newPosB) {
    Serial.print("encoderB: ");
    Serial.println((int)(encoderB.getDirection()));
    posB = newPosB;
  } 

}

void encoder3(){
  static int posC = 0;
  encoderC.tick();

  int newPosC = encoderC.getPosition();
  if (posC != newPosC) {
    Serial.print("encoderC: ");
    Serial.println((int)(encoderC.getDirection()));
    posC = newPosC;
  } 

}

void encoder4(){
  static int posD = 0;
  encoderD.tick();

  int newPosD = encoderD.getPosition();
  if (posD != newPosD) {
    Serial.print("encoderD: ");
    Serial.println((int)(encoderD.getDirection()));
    posD = newPosD;
  } 

}

// void switches(){
//   ButtonState = digitalRead(input_A);
//   if(ButtonState == HIGH){
//      Serial.println("MUTE");
//   }
//   else{
//     Serial.println("MUTE 2");
//   }
// }


void runKey(){
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key);
  }
}