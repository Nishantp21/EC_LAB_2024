#include <Wire.h>

int i1 = 13;
int i2 = 12;
int i3 = 11;
int i4 = 10;
int i5 = 9;
int i6 = 8;
// i7 is ground
int i8 = 7;
int i9 = 6;
int i10 = 5;
int i11 = 4;
int i12 = 3;
int i13 = 2;
// i14 is vcc

int x = -1;
int result;

void setup() {

  Serial.begin(9600);

  Wire.begin(9);
  Wire.onReceive(receiveEvent);

}

void receiveEvent(int bytes){
  x = Wire.read();
}

bool gate7400(int input1, int input2, int output1){
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(output1, INPUT);
  
  digitalWrite(input1, LOW);
  digitalWrite(input2, LOW);
  if(digitalRead(output1) == LOW) return 0;

  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);
  if(digitalRead(output1) == LOW) return 0;

  digitalWrite(input1, LOW);
  digitalWrite(input2, HIGH);
  if(digitalRead(output1) == LOW) return 0;

  digitalWrite(input1, HIGH);
  digitalWrite(input2, HIGH);
  if(digitalRead(output1) == HIGH) return 0;

  return 1;
}

bool ic7400(){
  if(gate7400(i1, i2, i3) == 0) return 0;
  if(gate7400(i4, i5, i6) == 0) return 0;
  if(gate7400(i10, i9, i8) == 0) return 0;
  if(gate7400(i13, i12, i11) == 0) return 0;

  return 1;
}

bool gate7408(int input1, int input2, int output1){
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(output1, INPUT);
  
  digitalWrite(input1, LOW);
  digitalWrite(input2, LOW);
  if(digitalRead(output1) == HIGH) return 0;

  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);
  if(digitalRead(output1) == HIGH) return 0;

  digitalWrite(input1, LOW);
  digitalWrite(input2, HIGH);
  if(digitalRead(output1) == HIGH) return 0;

  digitalWrite(input1, HIGH);
  digitalWrite(input2, HIGH);
  if(digitalRead(output1) == LOW) return 0;

  return 1;
}

bool ic7408(){
  if(gate7408(i1, i2, i3) == 0) return 0;
  if(gate7408(i4, i5, i6) == 0) return 0;
  if(gate7408(i10, i9, i8) == 0) return 0;
  if(gate7408(i13, i12, i11) == 0) return 0;

  return 1;
}

bool gate7486(int input1, int input2, int output1){
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(output1, INPUT);
  
  digitalWrite(input1, LOW);
  digitalWrite(input2, LOW);
  if(digitalRead(output1) == HIGH) return 0;

  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);
  if(digitalRead(output1) == LOW) return 0;

  digitalWrite(input1, LOW);
  digitalWrite(input2, HIGH);
  if(digitalRead(output1) == LOW) return 0;

  digitalWrite(input1, HIGH);
  digitalWrite(input2, HIGH);
  if(digitalRead(output1) == HIGH) return 0;

  return 1;
}

bool ic7486(){
  if(gate7486(i1, i2, i3) == 0) return 0;
  if(gate7486(i4, i5, i6) == 0) return 0;
  if(gate7486(i10, i9, i8) == 0) return 0;
  if(gate7486(i13, i12, i11) == 0) return 0;

  return 1;
}

bool gate7404(int input1, int output1){
  pinMode(input1, OUTPUT);
  pinMode(output1, INPUT);

  digitalWrite(input1, HIGH);
  if(digitalRead(output1) == HIGH) return 0;

  digitalWrite(input1, LOW);
  if(digitalRead(output1) == LOW) return 0;

  return 1;
}

bool ic7404(){
  if(gate7404(i1, i2) == 0) return 0;
  if(gate7404(i3, i4) == 0) return 0;
  if(gate7404(i5, i6) == 0) return 0;
  if(gate7404(i9, i8) == 0) return 0;
  if(gate7404(i11, i10) == 0) return 0;
  if(gate7404(i13, i12) == 0) return 0;

  return 1;
}

void loop() {

  if(x == 2 || x == 3 || x == 4 || x == 5){
    if(x == 2){
      result = ic7404();
    }
    else if(x == 3){
      result = ic7400();
    }
    else if(x == 4){
      result = ic7408();
    }
    else if(x == 5){
      result = ic7486();
    }
    pinMode(i1, OUTPUT);
    if(result) digitalWrite(i1, HIGH);
    else digitalWrite(i1, LOW);
    if(result) Serial.println("Working good");
    else Serial.println("Not working");
    Serial.println(x);
    // delay(4000);
    x = -1;
  }
  
}
