//Lab 3 Part 1
// C++ code
//

enum STATE {INIT, X_WAIT, X_STATE, Y_WAIT, Y_STATE, Z_WAIT, LED_CHANGE} gState = INIT;
char xButtonPressed = 0;
char yButtonPressed = 0;
char zButtonPressed = 0;

void tick(void) {
  
  // transitions
  switch (gState) {
    case INIT:
    if(xButtonPressed == 1){
     gState = X_WAIT; 
    }
    else {
     gState = INIT;
    }
    break;
    
    case X_WAIT:
    if(xButtonPressed == 1){
     gState = X_WAIT; 
    }
    else {
     gState = X_STATE;
    }
    break;
    
    case X_STATE:
    if(xButtonPressed == 1){
     gState = X_WAIT; 
    }
    else if(xButtonPressed == 0 && yButtonPressed == 0 && zButtonPressed ==0) {
     gState = X_STATE;
    }
    else if(yButtonPressed == 1){
     gState = Y_WAIT; 
    }
    else {
     gState = INIT;
    }
    break;
    
    case Y_WAIT:
    if(yButtonPressed == 1){
     gState = Y_WAIT; 
    }
    else {
     gState = Y_STATE;
    }
    break;
    
    case Y_STATE:
    if(xButtonPressed == 1){
     gState = X_WAIT; 
    }
    else if(xButtonPressed == 0 && yButtonPressed == 0 && zButtonPressed ==0) {
     gState = Y_STATE;
    }
    else if(zButtonPressed == 1){
     gState = Z_WAIT; 
    }
    else {
     gState = INIT;
    }
    break;
    
    case Z_WAIT:
    if(zButtonPressed == 1){
     gState = Z_WAIT; 
    }
    else {
     gState = LED_CHANGE;
    }
    break;
    
    case LED_CHANGE:
    gState = INIT;
    break;
  }
  
  // actions
  switch (gState) {
    case INIT:
    break;

    case LED_CHANGE:
    if(digitalRead(2) == 0) {
      digitalWrite(2, HIGH);
    }
    else {
      digitalWrite(2, LOW);
    }
    break;
  }
}

void setup() {
  pinMode(13, INPUT);
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  xButtonPressed = digitalRead(13);
  yButtonPressed = digitalRead(12);
  zButtonPressed = digitalRead(11);
  tick();
  delay(100);
}