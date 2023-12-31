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
 
  if ((temp>>3) & 0x01){digitalWrite(B[3],HIGH);}
  if ((temp>>2) & 0x01){digitalWrite(B[2],HIGH);}
  if ((temp>>1) & 0x01){digitalWrite(B[1],HIGH);}
  if (temp & 0x01){digitalWrite(B[0],HIGH);}
}

unsigned char getChar(int x){
  if (x == 4){
	return 0x0F;
  }
  else if (x == 3) {
	return 0x07;
  }
  else if (x == 2) {
   return 0x03; 
  }
  else if (x == 1) {
   return 0x01; 
  }
  else {
   return 0x00; 
  }
}


void loop()
{
  //while(Serial.available() == 0){}
  resetB();
  a = analogRead(A0);
  a = map(a, 0, 1000, 0, 4);
  unsigned char b = getChar(a);
  writeToB(b); //This will display the value of a in binary on the LEDs
  
  delay(200);
}