#include "Timer.h"
#include <LiquidCrystal.h>
#include <string.h>

const int rs = 12, rw = 11, en = 10, d4 = 5, d5 = 4, d6 = 3, d7 = 2; 
//LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
LiquidCrystal lcd(rs, rw, en, d4, d5, d6, d7);

String word1 = "";
String word2 = "";
String temp = "";
bool complete = 0;

void setup()
{
  lcd.begin(16,2);
  lcd.clear();
  Serial.begin(9600);
}

void loop() {
  while(Serial.available() == 0){}
  while (Serial.available()) {
    char getChar = Serial.read();
    if (getChar != '\n'){
      temp += getChar;
    }
    else {
        complete = 1;
    }
  }
  if (complete){
    if (word1 == ""){
      word1 = temp;
      lcd.setCursor(0, 0);
      lcd.print(word1);
    }
    else if (word2 == ""){
      word2 = temp;
      lcd.setCursor(0, 1);
      lcd.print(word2);
    }
    complete = false;
    temp = "";
  }
}

