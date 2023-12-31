#include "Timer.h"

enum STATE {CENTER, LEFT, LEFT_MOST, RIGHT, RIGHT_MOST} gState = CENTER;
const int xMove = A0;
const int SW = 8;
int movement, LED = HIGH;

void tick(void) {
  
  // transitions
  switch (gState) {
    case CENTER:
    if (movement < 200){
      gState = LEFT;
    }
    else if (movement > 800){
      gState = RIGHT;
    }
    else {
      gState = CENTER;
    }
    break;
    
    case LEFT:
    if (movement < 200){
      gState = LEFT_MOST;
    }
    else if (movement > 800){
      gState = CENTER;
    }
    else {
      gState = LEFT;
    }
    break;
    
    case LEFT_MOST:
    if (movement > 800){
      gState = LEFT;
    }
    else {
      gState = LEFT_MOST;
    }
    break;

    case RIGHT:
    if (movement < 200){
      gState = CENTER;
    }
    else if (movement > 800){
      gState = RIGHT_MOST;
    }
    else {
      gState = RIGHT;
    }
    break;
    
    case RIGHT_MOST:
      if (movement < 200){
      gState = RIGHT;
    }
    else {
      gState = RIGHT_MOST;
    }
    break;
  }
  
  // actions
  switch (gState) {
    case CENTER:
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LED);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    break;
    
    case LEFT:
    digitalWrite(2, LOW);
    digitalWrite(3, LED);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    break;
    
    case LEFT_MOST:
    digitalWrite(2, LED);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    break;

    case RIGHT:
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LED);
    digitalWrite(6, LOW);
    break;
    
    case RIGHT_MOST:
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LED);
    break;
  }
}

void setup() {
  pinMode(xMove, INPUT);
  pinMode(SW, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(SW, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  TimerSet(200);
  TimerOn();
  Serial.begin(9600);
}

void loop() {
  movement = analogRead(xMove);
  int press = digitalRead(SW);
  if (!press) {
    while(!press){press = digitalRead(SW);}
    if (LED == HIGH){
      LED = LOW;
    }
    else {
      LED = HIGH;
    }
  }
  tick();
  while(!TimerFlag){}
  TimerFlag = 0; 
}
