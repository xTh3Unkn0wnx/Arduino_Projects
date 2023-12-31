#include "Timer.h"

enum STATE {RED, BUTTON_PRESSED, GREEN, YELLOW} gState = RED;
char buttonPressed = 0;
int i = 0;

void tick(void) {
  
  // transitions
  switch (gState) {
    case RED:
    if (buttonPressed == 1){
		gState = BUTTON_PRESSED;
    }
    else {
      	gState = RED;
    }
    break;
    
    case BUTTON_PRESSED:
    if (buttonPressed == 1){
		gState = BUTTON_PRESSED;
    }
    else {
      	gState = GREEN;
    }
    break;
    
    case GREEN:
    if (i < 21){
      	i++;
		gState = GREEN;
    }
    else {
      	i = 0;
      	gState = YELLOW;
    }
    break;
    
    case YELLOW:
    if (i < 11){
      	i++;
		gState = YELLOW;
    }
    else {
      	i = 0;
      	gState = RED;
    }
    break;
  }
  
  // actions
  switch (gState) {
    case RED:
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    break;

    case BUTTON_PRESSED:
    break;
    
    case GREEN:
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    break;

    case YELLOW:
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    break;
  }
}

void setup() {
  pinMode(13, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  TimerSet(500); //this value (500) is the period in ms
  TimerOn();
}

void loop()
{
  buttonPressed = digitalRead(13);
  tick();
  while(!TimerFlag){}
  TimerFlag = 0;  
}