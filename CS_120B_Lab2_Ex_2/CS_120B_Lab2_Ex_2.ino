// C++ code
//
const int B[] = {2, 3, 4, 5};
int a = 0x00;
int a0, a1, a2, a3;

void setup()
{
  pinMode(B[0], OUTPUT);
  pinMode(B[1], OUTPUT);
  pinMode(B[2], OUTPUT);
  pinMode(B[3], OUTPUT);
  Serial.begin(9600);
}

void resetB()
{
  digitalWrite(B[3],LOW);
  digitalWrite(B[2],LOW);
  digitalWrite(B[1],LOW);
  digitalWrite(B[0],LOW);
}

void writeToB(unsigned char temp)
{
  
  if (temp < 0){
    temp = 0;
  }
  else if (temp > 15) {
    temp = 15;
  }

  if ((temp>>3) & 0x01){digitalWrite(B[3],HIGH);}
  if ((temp>>2) & 0x01){digitalWrite(B[2],HIGH);}
  if ((temp>>1) & 0x01){digitalWrite(B[1],HIGH);}
  if (temp & 0x01){digitalWrite(B[0],HIGH);}
}

int farToCelConverter(int a){
  unsigned int c = ((a - 32) * 5) / 9;
  return c; 
}


void loop()
{
  while(Serial.available() == 0){}
  a = Serial.parseInt();
  int c = farToCelConverter(a);
  resetB();
  writeToB(c); //This will display the value of a in binary on the LEDs
  
  delay(200);
}