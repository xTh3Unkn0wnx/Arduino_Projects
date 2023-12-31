//Lab 3 Part 1
// C++ code
//

enum STATE {RED, GREEN_WAIT, GREEN, YELLOW_WAIT, YELLOW, RED_WAIT} gState = RED;
char buttonPressed = 0;

void tick(char a) {
  
  // transitions
  switch (gState) {
    case RED:
    if(a == 1){
      gState = GREEN_WAIT;
    }
    else {
      gState = RED;
    }
    break;
    
    case GREEN_WAIT:
    if(a == 1){
      gState = GREEN_WAIT;
    }
    else {
      gState = GREEN;
    }
    break;
    
    case GREEN:
    if(a == 1){
      gState = YELLOW_WAIT;
    }
    else {
      gState = GREEN;
    }
    break;
    
    case YELLOW_WAIT:
    if(a == 1){
      gState = YELLOW_WAIT;
    }
    else {
      gState = YELLOW;
    }
    break;
    
    case YELLOW:
    if(a == 1){
      gState = RED_WAIT;
    }
    else {
      gState = YELLOW;
    }
    break;
    
    case RED_WAIT:
    if(a == 1){
      gState = RED_WAIT;
    }
    else {
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

    case GREEN_WAIT:
    break;
    
    case GREEN:
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    break;

    case YELLOW_WAIT:
    break;
    
    case YELLOW:
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    break;

    case RED_WAIT:
    break;
  }
}

void setup() {
  pinMode(13, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop()
{
  buttonPressed = digitalRead(13);
  tick(buttonPressed);
  delay(100);
}