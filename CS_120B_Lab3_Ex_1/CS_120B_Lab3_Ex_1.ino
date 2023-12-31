//Lab 3 Part 1
// C++ code
//

enum STATE {offWait, on, onWait, off} gState = offWait;
char buttonPressed = 0;

void tick(char a) {
  
  // transitions
  switch (gState) {
    case offWait:
    if (a == 1){
    	gState = on;
    }
    else {
      	gState = offWait;
    }
    break;
    
    case on:
    if (a == 1){
    	gState = on;
    }
    else {
      	gState = onWait;
    }
    break;
    
    case onWait:
    if (a == 1){
    	gState = off;
    }
    else {
      	gState = onWait;
    }
    break;
    
    case off:
    if (a == 1){
    	gState = off;
    }
    else {
      	gState = offWait;
    }
    break;
  }
  
  // actions
  switch (gState) {
    case offWait:
    break;

    case on:
    digitalWrite(2, HIGH);
    break;
    
    case onWait:
    break;
    
    case off:
    digitalWrite(2, LOW);
    break;
  }
}

void setup() {
  pinMode(13, INPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  buttonPressed = digitalRead(13);
  tick(buttonPressed);
  delay(100);
}