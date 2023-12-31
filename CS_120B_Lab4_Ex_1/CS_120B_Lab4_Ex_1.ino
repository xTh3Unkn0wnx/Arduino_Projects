//Lab 4 Starter
// C++ code
//Note: Upon downloading, this code does nothing except run without errors at a period of 500ms
//      It is up to you to figure out how to manipulate these timing details for your own purposes
#include "Timer.h"

enum STATE {OFF, SLOW_WAIT, SLOW_ON, SLOW_OFF, FAST_WAIT, FAST_ON, FAST_OFF, OFF_WAIT} gState = OFF;
char buttonPressed = 0;
int i = 0;

void tick(void) {
  
  // transitions
  switch (gState) {
    case OFF:
    if (buttonPressed == 1){
		gState = SLOW_WAIT;
    }
    else {
     	gState = OFF;
    }
    break;
    
    case SLOW_WAIT:
    if (buttonPressed == 1){
		gState = SLOW_WAIT;
    }
    else {
     	gState = SLOW_ON;
    }
    break;
    
    case SLOW_ON:
    if (buttonPressed == 1){
    	gState = FAST_WAIT;
      	i = 0;
    }
    else {
    	if (i < 3){
      		i++;
          gState = SLOW_ON;
      	}
      	else {
         	gState = SLOW_OFF;
          i = 0;
        }
    }
    break;
    
    case SLOW_OFF:
    if (buttonPressed == 1){
    	gState = FAST_WAIT;
      	i = 0;
    }
    else {
    	if (i < 3){
      		i++;
          	gState = SLOW_OFF;
      	}
      	else {
         	gState = SLOW_ON;
          	i = 0;
        }
    }
    break;
    
    case FAST_WAIT:
    if (buttonPressed == 1){
		gState = FAST_WAIT;
    }
    else {
     	gState = FAST_ON;
    }
    break;
    
    case FAST_ON:
    if (buttonPressed == 1){
    	gState = OFF_WAIT;
      	i = 0;
    }
    else {
    	if (i < 2){
      		i++;
          	gState = FAST_ON;
      	}
      	else {
         	gState = FAST_OFF;
          	i = 0;
        }
    }
    break;
    
    case FAST_OFF:
    if (buttonPressed == 1){
    	gState = OFF_WAIT;
      	i = 0;
    }
    else {
    	if (i < 2){
      		i++;
          	gState = FAST_OFF;
      	}
      	else {
         	gState = FAST_ON;
          	i = 0;
        }
    };
    break;
    
    case OFF_WAIT:
    if (buttonPressed == 1){
		gState = OFF_WAIT;
    }
    else {
     	gState = OFF;
    }
    break;
    
    default:
    gState = OFF;
    break;
  }
  
  // actions
  switch (gState) {
    case OFF:
    digitalWrite(2, LOW);
    break;

    case SLOW_WAIT:
    break;
    
    case SLOW_ON:
    digitalWrite(2, HIGH);
    break;
    
    case SLOW_OFF:
    digitalWrite(2, LOW);
    break;
    
    case FAST_WAIT:
    break;
    
    case FAST_ON:
    digitalWrite(2, HIGH);
    break;
    
    case FAST_OFF:
    digitalWrite(2, LOW);
    break;
    
    case OFF_WAIT:
    break;
    
    default:
    digitalWrite(2, LOW);
    break;
  }
}


void setup() {
  pinMode(13, INPUT);
  pinMode(2, OUTPUT);
  TimerSet(200); //this value (500) is the period in ms
  TimerOn();
}

void loop()
{
  buttonPressed = digitalRead(13);
  tick();
  while(!TimerFlag){}
  TimerFlag = 0;  
}