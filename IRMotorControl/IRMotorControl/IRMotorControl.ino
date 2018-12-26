#include <CPE123_EncoderLib.h>

#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <CPutil.h>

// Simple sketch to just test a motor
//Ria Bhatt team 10 session 3-6pm

// Define our pins
const int rightMotorPin1 = 2;
const int rightMotorPin2 = 3;
const int leftMotorPin1 = 4;
const int leftMotorPin2 = 5;
const int buttonPin = 8; 
Button button(buttonPin);

const int IR_PIN = 10;
IRrecv irDetect(IR_PIN);
decode_results irIn;

void setup() 
{
    motorsSetup(); 
    pinMode(buttonPin, INPUT); 
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
   irDetect.enableIRIn(); // Start the Receiver
  setupMessage(__FILE__, "Simple Motor Test sketch");
  delay(500);
     
}

void motorsSetup() { 
  // Initalize the pins for output 
   pinMode(rightMotorPin1, OUTPUT);
   pinMode(rightMotorPin2, OUTPUT);
   pinMode(leftMotorPin1, OUTPUT);
   pinMode(leftMotorPin2, OUTPUT);

    // Stop the motor
   analogWrite(rightMotorPin1, 0);
   analogWrite(rightMotorPin2, 0);
   analogWrite(leftMotorPin1, 0);
   analogWrite(leftMotorPin2, 0);
}

void loop() 
{
  control(); 
}
void control(){
  if (irDetect.decode(&irIn)) 
  {
    decodeIR();
    irDetect.resume(); 
  }
  
  if(Serial1.available()){
    int num = Serial1.parseInt();
    if(num == 0){
      robotStop();
      Serial.println("Robot Stopped");
    }
  }
}

void decodeIR() // Indicate what key is pressed
{
  unsigned int aSpeed = 200;
  static int speedCounter = 1;
  switch(irIn.value)
  {
  case 0xFF18E7:  
    Serial.println("Up Arrow");
    robotForward(aSpeed); 
  break;

  case 0xFF10EF:  
    Serial.println("Left Arrow"); 
    robotLeft(aSpeed);
  break;

  case 0xFF38C7:  
    Serial.println("OK"); 
    robotStop();
  break;

  case 0xFF5AA5:  
    Serial.println("Right Arrow"); 
    robotRight(aSpeed);
  break;

  case 0xFF4AB5:  
    Serial.println("Down Arrow"); 
    robotBackward(180);
  break;

  case 0xFFA25D:  
    Serial.println("1"); 
  break;

  case 0xFF629D:  
    Serial.println("2"); 
  break;

  case 0xFFE21D:  
    Serial.println("3"); 
  break;

  case 0xFF22DD:  
    Serial.println("4"); 
  break;

  case 0xFF02FD:  
    Serial.println("5"); 
  break;

  case 0xFFC23D:  
    Serial.println("6"); 
  break;

  case 0xFFE01F:  
    Serial.println("7"); 
  break;

  case 0xFFA857:  
    Serial.println("8"); 
    aSpeed = aSpeed + 50;
  break;

  case 0xFF906F:  
    Serial.println("9"); 
  break;

  case 0xFF6897:  
    //send signal to alert alarm
    Serial1.println("*"); 
    break;

  case 0xFF9867:  
    Serial.println("0"); 
    aSpeed = aSpeed - 50;
    break;

  case 0xFFB04F:  
    Serial.println("#"); 
  break; 

  default: 
  break;

  }
}


void robotRight(int aSpeed) {
  enum{TURNING, STANDING}; 
  static int state = TURNING; 
  
  switch (state) {
    case(TURNING):
        rightTurn(aSpeed); 
    break; 
  }
}

void robotLeft(int aSpeed) {
  enum{TURNING, STANDING}; 
  static int state = TURNING; 
  switch (state) {
    case(TURNING):
        leftTurn(aSpeed); 
     break; 
  }
}
void robotBackward(int aSpeed) {
  enum{DRIVING, STANDING}; 
  static int state = DRIVING; 
  switch (state) {
    case(DRIVING):
      rightMotorBackward(aSpeed); 
      leftMotorBackward(aSpeed); 
    break; 
  }
}

void robotForward(int aSpeed){ 
  enum{DRIVING}; 
  static int state = DRIVING; 
  
  switch(state){
    case(DRIVING):
        rightMotorForward(aSpeed); 
        leftMotorForward(aSpeed);
    break; 
  }
}

void robotStop() { 
  rightMotorStop();
  leftMotorStop(); 
}
void rightTurn(int aSpeed) { 
  leftMotorForward(aSpeed); 
  rightMotorStop();
}
void leftTurn(int aSpeed) {
  rightMotorForward(aSpeed); 
  leftMotorStop(); 
}
void rightMotorStop() {
  motorControl(rightMotorPin1, rightMotorPin2, 0); 
}
void leftMotorStop() { 
  motorControl(leftMotorPin1, leftMotorPin2, 0); 
}
void rightMotorBackward(int aSpeed) { 
  motorControl(rightMotorPin2, rightMotorPin1, aSpeed); 
}
void leftMotorBackward(int aSpeed) { 
  motorControl(leftMotorPin2, leftMotorPin1, aSpeed); 
}

void leftMotorForward(int aSpeed) {
  motorControl(leftMotorPin1,leftMotorPin2, aSpeed);  
}

void rightMotorForward(int aSpeed) { 
  motorControl(rightMotorPin1, rightMotorPin2, aSpeed);
}

void motorControl(int pin1, int pin2, int aSpeed) {
  analogWrite(pin1, aSpeed); 
  analogWrite(pin2, 0); 
  
}
