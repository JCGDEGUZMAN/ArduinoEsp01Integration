#include<SoftwareSerial.h>
SoftwareSerial mySerial(2,3); //RX TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(500);
}

void loop() {
  String IncomingString="";

  if(mySerial.available()){
    IncomingString =  mySerial.readString();
    Serial.println("Received String: " + IncomingString);
  }
}
