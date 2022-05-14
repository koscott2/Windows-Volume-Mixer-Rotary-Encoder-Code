

#include <Arduino.h>
#include <RotaryEncoder.h>
#include <Bounce2.h>
#include <Keypad.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// static const unsigned char PROGMEM logo_bmp[] =
// { 0b00000000, 0b11000000,
//   0b00000001, 0b11000000,
//   0b00000001, 0b11000000,
//   0b00000011, 0b11100000,
//   0b11110011, 0b11100000,
//   0b11111110, 0b11111000,
//   0b01111110, 0b11111111,
//   0b00110011, 0b10011111,
//   0b00011111, 0b11111100,
//   0b00001101, 0b01110000,
//   0b00011011, 0b10100000,
//   0b00111111, 0b11100000,
//   0b00111111, 0b11110000,
//   0b01111100, 0b11110000,
//   0b01110000, 0b01110000,
//   0b00000000, 0b00110000 };

  char incoming[1000];

  

 #define button_PinA D1
 Bounce buttonA = Bounce();
 #define button_PinB D2
 Bounce buttonB = Bounce();
 #define button_PinC D0
 Bounce buttonC = Bounce();

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

#define PIN_IN1 D5
#define PIN_IN2 D4

RotaryEncoder encoderB(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);


#define PIN_IN3 A2
#define PIN_IN4 A3

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
  buttonA.attach(button_PinA,INPUT_PULLUP); 
  buttonA.interval(25);
  buttonB.attach(button_PinB,INPUT_PULLUP); 
  buttonB.interval(25);
  buttonC.attach(button_PinC,INPUT_PULLUP); 
  buttonC.interval(25);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.clearDisplay();
  
} 
 
void loop()
{
  encoder1();
  encoder2();
  encoder3();
  encoder4();
  switches();
  runKey();
  statout(56, 42, 16);  
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



void switches(){
  buttonA.update(); // Update the Bounce instance
   if ( buttonA.fell() ) {  // Call code if button transitions from HIGH to LOW
     Serial.println("encoderA: MUTE");
   }

   buttonB.update(); // Update the Bounce instance
   if ( buttonB.fell() ) {  // Call code if button transitions from HIGH to LOW
     Serial.println("encoderB: MUTE");
   }
    buttonC.update(); // Update the Bounce instance
   if ( buttonC.fell() ) {  // Call code if button transitions from HIGH to LOW
     Serial.println("encoderC: MUTE");
   }
}


void runKey(){
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key);
  }
}


void statout(int cpu_temp, int gpu_temp, int ram_perc) {
  
  display.setTextSize(2);     
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(0, 0);     
  display.cp437(true);
  String CPU = "CPU";
  String GPU = " GPU";
  String RAM = " RAM";
  display.print(CPU);
  display.setCursor(31, 0);
  display.print(GPU);
  display.setCursor(75, 0);        
  display.println(RAM);
  display.print(String(cpu_temp));
  display.print((char)248);
  display.setCursor(31, 16);
  display.print(" " + String(gpu_temp));
  display.print((char)248);
  display.setCursor(75, 16);
  display.print(" " + String(ram_perc));
  display.print((char)37);

  display.display();
  delay(2000);
}

