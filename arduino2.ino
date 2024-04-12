#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3);  // RX | TX

int received = 5;

int sensorPin = 7;
int Vin = 5;
float Vout = 0;
float R1 = 1000;
float R2 = 0;
float buffer = 0;
int raw = 0;

int chargePin = 12;
int dischargePin = 11;
int analogPin = 2;
float Rc = 100000;
unsigned long startTime;
unsigned long elapsedTime;
float microFarads;
float nanoFarads;

void setup() {
  BTserial.begin(9600);
  Serial.begin(9600);
  pinMode(chargePin, OUTPUT);
  digitalWrite(chargePin, LOW);

  Wire.begin();
}

void resistance(){
  // Resistance
  raw = analogRead(sensorPin);
  if (raw) {
    buffer = raw * Vin;
    Vout = (buffer) / 1024.0;
    buffer = (Vin / Vout) - 1;
    R2 = R1 * buffer;
    BTserial.println((String)R2);
  }
}

void capacitance(){
  //Capacitance
  digitalWrite(chargePin, HIGH);  // set chargePin HIGH and capacitor charging
  startTime = millis();  
  while(analogRead(analogPin) < 648){}
  elapsedTime= millis() - startTime;
  microFarads = ((float)elapsedTime / Rc) * 1000;
  if (microFarads > 1){
    BTserial.println((String)microFarads + " μF");
  }
  else
  {
    microFarads = ((float)elapsedTime * 1e6) / Rc;
    nanoFarads = microFarads ;
    BTserial.println((String)nanoFarads + " nF");
  }
  digitalWrite(chargePin, LOW);
  pinMode(dischargePin, OUTPUT);
  digitalWrite(dischargePin, LOW);
  while(analogRead(analogPin) > 0){}
  pinMode(dischargePin, INPUT);
}

void loop() {

  if(BTserial.available()){
    int s = BTserial.read();

    if(s == 0){
      resistance();
    }
    else if(s == 1){
      capacitance();
    }
    else if(s == 2 || s == 3 || s == 4 || s == 5){
      Wire.beginTransmission(9);
      Wire.write(s);
      Wire.endTransmission();
      delay(300);
      int ans = digitalRead(received);
      if(s == 2){
        if(ans) BTserial.println("IC 7404 is working fine");
        else BTserial.println("IC 7404 is not working fine");
      }
      else if(s == 3){
        if(ans) BTserial.println("IC 7400 is working fine");
        else BTserial.println("IC 7400 is not working fine");
      }
      else if(s == 4){
        if(ans) BTserial.println("IC 7408 is working fine");
        else BTserial.println("IC 7408 is not working fine");
      }
      else if(s == 5){
        if(ans) BTserial.println("IC 7486 is working fine");
        else BTserial.println("IC 7486 is not working fine");
      }
      Serial.println(ans);
    }
  }
}