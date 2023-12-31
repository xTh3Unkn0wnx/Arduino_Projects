#include "Timer.h"
#include <LiquidCrystal_74HC595.h> // LiquidCrystal_74HC595 library
#include <DHT.h> // DHT sensor library 

// Global Variables
// Intantiate LCD screen module to act with 74HC595 Shift Register
LiquidCrystal_74HC595 lcd(11, 13, 12, 1, 3, 4, 5, 6, 7);
const int TempHumSensor = 2;
const int Buzzer = 3;
const int button = 7;
const int PERIOD = 50;
const int clockPeriod = 1000;
const int htcPeriod = 2000;
const int LCDPeriod = 1000;
int clockElasped = 1000;
int htcElasped = 2000;
int LCDElasped = 1000;
bool buttonPressed;
bool timer = 0;
unsigned char temp = 0;
unsigned char humid = 0;
int sec = 50;
int min = 59;
int hr = 9;
bool am_check = 1;
int tmr_min = 0;
int tmr_hr = 10;
bool tmr_am = 1;
bool alarm = 0;
int i = 0, j=1000;
// Intsntiate the HTC module, also tells the Ardiono it is the HTC11 model
DHT dht(TempHumSensor, DHT11);

// Settle the states for each State Machines that will be used in this code
enum min_counter {MIN_WAIT, MIN_INCREMENT} min_counter = MIN_WAIT;
enum hr_counter {HR_WAIT, HR_INCREMENT} hr_counter = HR_WAIT;
enum alarm_SM {WAIT, ALARM, OFF_WAIT} alarm_SM = WAIT;

// Increment the sec global variable every time the period hits 1 sec (In this case every 20 cycles)
void sec_increment(){
  sec = sec + 1;
}

// Increment the min global variable, dependent on the variable sec
void min_SM(){
  //Transitions
  switch (min_counter){
    case MIN_WAIT:
    if (sec < 60){
      min_counter = MIN_WAIT;
    }
    else {
      min_counter = MIN_INCREMENT;
    }
    break;
    case MIN_INCREMENT:
    min_counter = MIN_WAIT;
    break;
  }

  //Actions
  switch(min_counter){
    case MIN_WAIT:
    break;
    case MIN_INCREMENT:
    min = min + 1;
    sec = 0;
    break;
  }
}

// Increment the hr global variable, dependent on the global variable min
void hr_SM(){
  //Transitions
  switch (hr_counter){
    case HR_WAIT:
    if (min < 60){
      hr_counter = HR_WAIT;
    }
    else {
      hr_counter = HR_INCREMENT;
    }
    break;
    case HR_INCREMENT:
    hr_counter = HR_WAIT;
    break;
  }

  //Actions
  switch(hr_counter){
    case HR_WAIT:
    break;
    case HR_INCREMENT:
    min = 0;
    if (hr < 12){
      hr++;
      if(hr == 12){
        if(am_check == 1){
          am_check = 0;
        }
        else {
          am_check = 1;
        }
      }
    }
    else {
      hr = 1;
    }
    break;
  }
}

// Set the alarm bool value at 0 or 1
// If tmr_min == min, tmr_hr == hr AND tmr_am == am_check, set alarm at 1
// alarm will remain at 1 until button is pressed
void alarmSM(){
  // Transition
  switch(alarm_SM){
    case WAIT:
    if (tmr_min == min && tmr_hr == hr && tmr_am == am_check){
      alarm_SM = ALARM;
    }
    else{
      alarm_SM = WAIT;
    }
    break;
    case ALARM:
    if (!buttonPressed){
      alarm_SM = OFF_WAIT;
    }
    else {
      alarm_SM = ALARM;
    }
    break;
    case OFF_WAIT:
    if ((tmr_hr == hr && tmr_min == min) || !buttonPressed){
      alarm_SM = OFF_WAIT;
    }
    else {
      alarm_SM = WAIT;
    }
    break;
  }

  // Actions
  switch(alarm_SM){
    case WAIT:
    alarm = 0;
    break;
    case ALARM:
    alarm = 1;
    break;
    case OFF_WAIT:
    alarm = 0;
    break;
  }
}

// If alarm is 1, the passive buzzer will emit a sound using the same tone every 11th periods,
// tone it produces is different after each period
void clockAlarm(){
  if (alarm){
    if (i < 11){
      i++;
    }
    else{
      i = 0;
    }
    tone(Buzzer, i*100);
  }
  else {
    noTone(Buzzer);
    i = 0;
  }
}


// The function resposnible writing the information onto the LCD display 
void writeLCD(){
  lcd.clear();
  // Writes the temp on top left of LCD
  if(temp >= 100){
    lcd.setCursor(0, 0);
    lcd.print(temp);
  } else if(temp >= 10){
    lcd.setCursor(1, 0);
    lcd.print(temp);
  } else {
    lcd.setCursor(2, 0);
    lcd.print(temp);
  }
  lcd.setCursor(3, 0);
  lcd.print("oF");
  // Writes humidity on bottom left of LCD
  if(humid >= 10){
    lcd.setCursor(0, 1);
    lcd.print(humid);
  } else {
    lcd.setCursor(1, 1);
    lcd.print(humid);
  }
  lcd.setCursor(2, 1);
  lcd.print("%H");
  // Writes time on top right of LCD
  if(hr < 10){
    lcd.setCursor(7, 0);
    lcd.print(hr);
  }else{
    lcd.setCursor(6, 0);
    lcd.print(hr);
  }
  lcd.setCursor(8, 0);
  lcd.print(":");
  if(min < 10){
    lcd.setCursor(9, 0);
    lcd.print(0);
    lcd.setCursor(10, 0);
    lcd.print(min);
  } else {
    lcd.setCursor(9, 0);
    lcd.print(min);
  }
  lcd.setCursor(11, 0);
  lcd.print(":");
  if(sec < 10){
    lcd.setCursor(12, 0);
    lcd.print(0);
    lcd.setCursor(13, 0);
    lcd.print(sec);
  }else {
    lcd.setCursor(12, 0);
    lcd.print(sec);
  }
  lcd.setCursor(14, 0);
  if (am_check == 1){
    lcd.print("AM");
  }else{
    lcd.print("PM");
  }
  // Writes alarm time on bottom left on LCD 
  if(tmr_hr < 10){
    lcd.setCursor(10, 1);
    lcd.print(tmr_hr);
  }else{
    lcd.setCursor(9, 1);
    lcd.print(tmr_hr);
  }
  lcd.setCursor(11, 1);
  lcd.print(":");
  if(tmr_min < 10){
    lcd.setCursor(12, 1);
    lcd.print(0);
    lcd.setCursor(13, 1);
    lcd.print(tmr_min);
  } else {
    lcd.setCursor(12, 1);
    lcd.print(tmr_min);
  }
  lcd.setCursor(14, 1);
  if (tmr_am == 1){
    lcd.print("AM");
  }else{
    lcd.print("PM");
  }
}

// This function updates the temp and humid global variable every htcPeriod
void htcRead(){
    if (!isnan(TempHumSensor)){
      temp = dht.readTemperature(true);
      humid = dht.readHumidity();
    } 
}

void setup() {
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(button, OUTPUT);
  pinMode(TempHumSensor, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(button, HIGH);
  lcd.begin(16, 2);
  lcd.clear();
  dht.begin();
  TimerSet(PERIOD);
  TimerOn();
  Serial.begin(9600);
}

void loop() {
  // Checks the pin connected to the button to see if its pressed
  buttonPressed = digitalRead(button);
  // Every second, every function in this loop will execute
  if (clockElasped >= clockPeriod){
    sec_increment();
    min_SM();
    hr_SM();
    clockElasped = 0;
  }
  clockElasped = clockElasped + PERIOD;
  // Every 2 seconds, the htcRead function will execute
  if (htcElasped >= htcPeriod){
    htcRead();
    htcElasped = 0;
  }
  htcElasped = htcElasped + PERIOD;
  // Every 1 second, the program will update the LCD display 
  if(LCDElasped >= LCDPeriod){
    writeLCD();
    LCDElasped = 0;
  }
  LCDElasped = LCDElasped + PERIOD;
  // Alarm should turn on instantanously and turn off instantanouly 
  // So the alarmSM and clockAlarm function will execute every period 
  alarmSM();
  clockAlarm();
  //Period should be 50ms so the loop is execute every 1/20th seconds 
  while(!TimerFlag){}
  TimerFlag = 0; 
}