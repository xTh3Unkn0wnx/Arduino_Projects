#include "Timer.h"
#include <LiquidCrystal.h>
#include <string.h>

enum STATE {START, PRINT, WAIT, RESET} gState = RESET;
const int rs = 12, rw = 11, en = 10, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int xMove = A0, yMove = A1, SW = 8; 
LiquidCrystal lcd(rs, rw, en, d4, d5, d6, d7);
char let = 'a';
int xPos = 0, yPos = 0;
int counter = 0, xMovement = 0, yMovement = 0, press;

String word1 = "";
String word2 = "";
String temp = "";
bool complete = 0;

void moveCursor(){
  
  if(xMovement < 250 && xPos != 0){
    xPos--;
  }
  if(xMovement > 750 && xPos != 15){
    xPos++;
  }
  if(yMovement < 250 && yPos != 0){
    yPos--;
  }
  if(yMovement > 750 && yPos !=1){
    yPos++;
  }
  lcd.setCursor(xPos, yPos);
}

void tick(void) {
  
  // transitions
  switch (gState) {
    case START:
    if(!press && counter < 5){
      gState = PRINT;
    }
    else if (!press && !(counter < 5)){
      gState = RESET;
    }
    else {
      gState = START;
    }
    break;
    
    case PRINT:
    gState = WAIT;
    break;
    
    case WAIT:
    if(!press) {
      gState = WAIT;
    }
    else {
      gState = START;
    }
    break;

    case RESET:
    if (!press) {
      gState = RESET;
    }
    else {
      gState = START;
    }
    break;
  }

    // actions
  switch (gState) {
    case START:
    break;
    
    case PRINT:
    lcd.print(let);
    counter++;
    break;
    
    case WAIT:
    break;

    case RESET:
    lcd.clear();
    xPos = 0;
    yPos = 0;
    counter = 0;
    break;
  }
}

void setup(){
  lcd.begin(16,2);
  lcd.clear();
  lcd.cursor();
  Serial.begin(9600);
  TimerSet(200);
  pinMode(xMove, INPUT);
  pinMode(yMove, INPUT);
  pinMode(SW, INPUT);
  digitalWrite(SW, HIGH);
  TimerOn();
}

void loop() {
  xMovement = analogRead(xMove);
  yMovement = analogRead(yMove);
  press = digitalRead(SW);
  moveCursor();
  tick();
  while(!TimerFlag){}
  TimerFlag = 0; 
}

