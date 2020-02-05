#include<SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial mySerial(2,3); //RX TX

int id =0;
boolean isMobileApp = false;
int cupsOfRiceSelected = 0;
int riceTypeSelected = 0;
double scaleOfRiceWater = 0;
    
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(5000);
}

void loop() {
  //temporary must be getHttpData()
  String payloadString = "";
  payloadString = String("[{\"Id\":1,\"IsMobileApp\":true,\"CupsOfRice\":5,\"RiceType\":1,\"IsDoneCooking\":false,\"IsRiceLevelLow\":false,\"IsWaterLevelLow\":false,\"RiceDistance\":\"0\",\"WaterDistance\":\"0\",\"RiceWaterScale\":\"0\"}]");
  separateKeyValueJSONPairs(payloadString);
  delay(2000);
}

void getHttpData(){
  String payloadString = "";
  if(mySerial.available()){
    payloadString =  mySerial.readString();

    if(payloadString.length() > 1){
      separateKeyValueJSONPairs(payloadString);
      delay(2000);
    }
  }
}

void separateKeyValueJSONPairs(String payload){
    StaticJsonDocument<1000> doc;

    DeserializationError err = deserializeJson(doc, payload);

    if (err) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(err.c_str());
      return;
    }

    id = doc[0]["Id"];
    isMobileApp = doc[0]["IsMobileApp"];
    cupsOfRiceSelected = doc[0]["CupsOfRice"];
    riceTypeSelected = doc[0]["RiceType"];
    scaleOfRiceWater = doc[0]["RiceWaterScale"];

    Serial.println("Id: " + String(id));
    delay(3000);
    Serial.println("isMobileApp: " + String(isMobileApp));
    delay(3000);
    Serial.println("cupsOfRiceSelected: " + String(cupsOfRiceSelected));
    delay(3000);
    Serial.println("riceTypeSelected: " + String(riceTypeSelected));
    delay(3000);
    Serial.println("scaleOfRiceWater: " + String(scaleOfRiceWater));
}
