#include "Timer.h"

const int L1 = 2, L2 = 3, L3 = 4, L4 = 5, L5 = 6, L6 = 7, L7 = 8;
const int button = 9;
const int digit1 = 10, digit2 = 11;
bool right = 1;
int buttonPressed;
int counter = 0;
//Used ChatGPT to help come up with the idea to use Arrays so that I dn not need to 
//write digitalWrite() for all 7 segments repeatily for each possible outcome
const bool segment[10][7] = {
  {1,1,1,1,1,1,0},
  {0,1,1,0,0,0,0},
  {1,1,0,1,1,0,1},
  {1,1,1,1,0,0,1},
  {0,1,1,0,0,1,1},
  {1,0,1,1,0,1,1},
  {1,0,1,1,1,1,1},
  {1,1,1,0,0,0,0},
  {1,1,1,1,1,1,1},
  {1,1,1,0,0,1,1}
};
const int segmentPins [7] = {12, 13, A0, A1, A2, A3, A4};

//Used ChatGPT to debug this function
//Is the function the program calls to set display to show a certain number based
//on the counter argument 
void displayNumber(int counter){
  int dig2 = counter / 10;
  int dig1 = counter % 10;

  Serial.println(dig2);
  Serial.println(dig1);

  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, HIGH);


  for (int i = 0; i < 7; i++){
    digitalWrite(segmentPins[i], segment[dig1][i]);
  }
 
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, HIGH);

  while(!TimerFlag){}
  TimerFlag = 0; 

  for (int i = 0; i < 7; i++){
    digitalWrite(segmentPins[i], segment[dig2][i]);
  }

  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, LOW);


  while(!TimerFlag){}
  TimerFlag = 0; 

}

enum States_SevenLED {LED1, LED2, LED3, LED4, LED5, LED6, LED7} States_SevenLED = LED1;
enum States_Increment {WAIT, INCREMENT, PRESSED_WAIT, RESET} States_Increment = WAIT;

//The Increment function is the state machine that tells the program/Arduino when to increment the counter 
//value or reset it back to 0
void Increment(){

  //transitions
  switch (States_Increment){
    case WAIT:
    if (buttonPressed){
      States_Increment = WAIT;
    }
    else if (!buttonPressed && States_SevenLED == LED4){
      States_Increment = INCREMENT;
    }
    else {
      States_Increment = RESET;
    }
    break;

    case INCREMENT:
    if (!buttonPressed){
      States_Increment = PRESSED_WAIT;
    }
    else {
      States_Increment = WAIT;
    }
    break;

    case PRESSED_WAIT:
    if (!buttonPressed){
      States_Increment = PRESSED_WAIT;
    }
    else {
      States_Increment = WAIT;
    }
    break;

    case RESET:
    if (!buttonPressed){
      States_Increment = PRESSED_WAIT;
    }
    else {
      States_Increment = WAIT;
    }
    break;
  }

  //Actions
  switch (States_Increment){
    case WAIT:
    break;

    case INCREMENT:
    counter++;
    break;

    case PRESSED_WAIT:
    break;

    case RESET:
    counter = 0;
    break;
  }
}

//The AltLED() is what make the LED shift from left to right repeatidily 
void AltLED(){

    //Transitions
    switch (States_SevenLED){
    case LED1:
    if (!buttonPressed){
      States_SevenLED = LED1;
    }
    else {
      right = 1;
      States_SevenLED = LED2;
    }
    break;

    case LED2:
    if (!buttonPressed){
      States_SevenLED = LED2;
    }
    else if (right) {
      States_SevenLED = LED3;
    }
    else {
      States_SevenLED = LED1;
    }
    break;
    
    case LED3:
    if (!buttonPressed){
      States_SevenLED = LED3;
    }
    else if (right) {
      States_SevenLED = LED4;
    }
    else {
      States_SevenLED = LED2;
    }
    break;

    case LED4:
    if (!buttonPressed){
      States_SevenLED = LED4;
    }
    else if (right) {
      States_SevenLED = LED5;
    }
    else {
      States_SevenLED = LED3;
    }
    break;

    case LED5:
    if (!buttonPressed){
      States_SevenLED = LED5;
    }
    else if (right) {
      States_SevenLED = LED6;
    }
    else {
      States_SevenLED = LED4;
    }
    break;

    case LED6:
    if (!buttonPressed){
      States_SevenLED = LED6;
    }
    else if (right) {
      States_SevenLED = LED7;
    }
    else {
      States_SevenLED = LED5;
    }
    break;

    case LED7:
    if (!buttonPressed){
      States_SevenLED = LED7;
    }
    else {
      right = 0;
      States_SevenLED = LED6;
    }
    break;
  }

  //Actions
  switch (States_SevenLED){
    case LED1:
    allLEDOff();
    digitalWrite(L1, HIGH);
    break;

    case LED2:
    allLEDOff();
    digitalWrite(L2, HIGH);
    break;
    
    case LED3:
    allLEDOff();
    digitalWrite(L3, HIGH);
    break;

    case LED4:
    allLEDOff();
    digitalWrite(L4, HIGH);
    break;

    case LED5:
    allLEDOff();
    digitalWrite(L5, HIGH);
    break;

    case LED6:
    allLEDOff();
    digitalWrite(L6, HIGH);
    break;

    case LED7:
    allLEDOff();
    digitalWrite(L7, HIGH);
    break;
  }
}

//Helper function so that all the LEDs turn off
void allLEDOff(){
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(L3, LOW);
  digitalWrite(L4, LOW);
  digitalWrite(L5, LOW);
  digitalWrite(L6, LOW);
  digitalWrite(L7, LOW);
}  

void setup() {
  Serial.begin(9600);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  pinMode(L5, OUTPUT);
  pinMode(L6, OUTPUT);
  pinMode(L7, OUTPUT);
  pinMode(button, OUTPUT);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(L3, LOW);
  digitalWrite(L4, LOW);
  digitalWrite(L5, LOW);
  digitalWrite(L6, LOW);
  digitalWrite(L7, LOW);
  digitalWrite(button, HIGH);
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, LOW);
  TimerSet(10);
  TimerOn();
}

void loop() {
  buttonPressed = digitalRead(button);
  displayNumber(counter);
  AltLED();
  Increment();
  while(!TimerFlag){}
  TimerFlag = 0; 
}
