#include<SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial mySerial(2,3); //RX TX

int id = 0;
boolean isMobileApp = false;
int cupsOfRiceSelected = 0;
int riceTypeSelected = 0;
double scaleOfRiceWater = 0.00;
  
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(1500);
}

void loop() {
  if(id == 0)
  {
       getHttpData();
  }
  if(id > 0)
  {
      postHttpData();
  }
}

void getHttpData(){
    String payloadString = "";
    if(mySerial.available()){
      payloadString =  mySerial.readString();

      if(payloadString.length() > 1){
        separateKeyValueJSONPairs(payloadString);
      }
    }
  }
  
void postHttpData(){
  delay(5000);
  String payloadString = "";

  String firstParam = "\"Id\":" + String(id);
  String secondParam = ",\"IsDoneCooking\":" + String(4);
  String thirdParam = ",\"IsRiceLevelLow\":" + String(false);
  String fourthParam = ",\"IsWaterLevelLow\":" + String(false);
  String fifthParam = ",\"RiceDistance\":" + String(5.00);
  String sixthParam = ",\"WaterDistance\":" + String(5.00);

  payloadString = String("[{"+ firstParam +  secondParam + thirdParam + fourthParam + fifthParam + sixthParam + "}]");

  mySerial.print(payloadString);
}

void separateKeyValueJSONPairs(String payload){
  StaticJsonDocument<256> doc;

  DeserializationError err = deserializeJson(doc, payload);

  if (err) {
    Serial.print(F("ARDUINO deserializeJson() failed with code "));
    Serial.println(err.c_str());
    return;
  }

  id = doc[0]["Id"];
  isMobileApp = doc[0]["IsMobileApp"];
  cupsOfRiceSelected = doc[0]["CupsOfRice"];
  riceTypeSelected = doc[0]["RiceType"];
  scaleOfRiceWater = doc[0]["RiceWaterScale"];

  delay(5000);
}
