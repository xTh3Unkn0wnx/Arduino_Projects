// C++ code
//
const int B[] = {2, 3, 4};
int a = 0x00;
int a0, a1, a2;

void setup()
{
  pinMode(B[0], OUTPUT);
  pinMode(B[1], OUTPUT);
  pinMode(B[2], OUTPUT);
  //pinMode(B[3], OUTPUT);
  Serial.begin(9600);
}

void resetB()
{
  //digitalWrite(B[3],LOW);
  digitalWrite(B[2],LOW);
  digitalWrite(B[1],LOW);
  digitalWrite(B[0],LOW);
}

void writeToB(unsigned char temp)
{
 
  //if ((temp>>3) & 0x01){digitalWrite(B[3],HIGH);}
  if (temp > 95){digitalWrite(B[2],HIGH);}
  if (temp >= 65 && temp <= 95){digitalWrite(B[1],HIGH);}
  if (temp < 65){digitalWrite(B[0],HIGH);}
}


void loop()
{
  while(Serial.available() == 0){}
  a = Serial.parseInt();
  resetB();
  writeToB(a); //This will display the value of a in binary on the LEDs
  
  delay(200);
}