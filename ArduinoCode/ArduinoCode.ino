#include<SoftwareSerial.h>
SoftwareSerial mySerial(2,3); //RX TX

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  String IncomingString="";
  boolean StringReady = false;
//  Serial.println("Arduino Working" + mySerial.available());
  while(mySerial.available()){
    IncomingString = mySerial.readString();
    StringReady = true;
  }

  if(StringReady){
    Serial.println("Received String: " + IncomingString);
  }
}
