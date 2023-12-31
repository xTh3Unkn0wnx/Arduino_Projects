// C++ code
//

#include "Timer.h"

enum STATE {OFF, LIT_OFF, LIT_ON} gState = OFF;
const int photoPIN = A0;
int light;
int i = 0;


void tick(void) {
  
  // transitions
  switch (gState) {
    case OFF:
    if (light > 500){
		gState = OFF;
    }
    else {
      	gState = LIT_OFF;
    }
    break;
    
    case LIT_OFF:
    if (light < 500){
      if (i < 10){
        i++;
        Serial.println(i);
        gState = LIT_OFF;
      }
      else {
      	gState = LIT_ON;
        i = 0;
      }
    }
    else {
      	i = 0;
      	gState = LIT_OFF;
    }
    break;
    
    case LIT_ON:
    if (light < 500) {
      gState = LIT_ON;
    }
    else {
      gState = OFF;
    }
    break;
  }
  
  // actions
  switch (gState) {
    case OFF:
    digitalWrite(9, LOW);
    break;

    case LIT_OFF:
    break;
    
    case LIT_ON:
    digitalWrite(9, HIGH);
    break;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(photoPIN, INPUT);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  TimerSet(500); //this value (500) is the period in ms
  TimerOn();
}

void loop()
{
  light = analogRead(photoPIN);
  tick();
  while(!TimerFlag){}
  TimerFlag = 0;  
}