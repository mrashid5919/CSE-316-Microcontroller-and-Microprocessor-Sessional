#include<SoftwareSerial.h>


SoftwareSerial SUART(2, 3); //RX = DPin-2; TX = DPin-3


void setup() {
  Serial.begin(9600);
  SUART.begin(9600);
  pinMode(8, OUTPUT);
}


void loop() {
  byte n = SUART.available();
  if (n != 0)
  {
    char x = SUART.read();
    Serial.print(x);
    digitalWrite(8, !digitalRead(8)); //toggle LED
    delay(500);
  }
}