#include<SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial mySerial(2,3); //RX TX

int id =0;
boolean is_mobile_app = false;
int cups_of_rice = 0;
int rice_type = 0;
double rice_water_scale = 0;
    
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(500);
}

void loop() {
  String payloadString = "";
  payloadString = String("[{\"Id\":1,\"IsMobileApp\":true,\"CupsOfRice\":5,\"RiceType\":1,\"IsDoneCooking\":false,\"IsRiceLevelLow\":false,\"IsWaterLevelLow\":false,\"RiceDistance\":\"0\",\"WaterDistance\":\"0\",\"RiceWaterScale\":\"0\"}]");
  separateKeyValueJSONPairs(payloadString);
  delay(2000);
}

void getHttpData(){
  String IncomingString="";

  if(mySerial.available()){
    IncomingString =  mySerial.readString();
    Serial.println("Received String: " + IncomingString);
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
    is_mobile_app = doc[0]["IsMobileApp"];
    cups_of_rice = doc[0]["CupsOfRice"];
    rice_type = doc[0]["RiceType"];
    rice_water_scale = doc[0]["RiceWaterScale"];

    Serial.println("Id: " + String(id));
    delay(3000);
    Serial.println("IsMobileApp: " + String(is_mobile_app));
    delay(3000);
    Serial.println("CupsOfRice: " + String(cups_of_rice));
    delay(3000);
    Serial.println("RiceType: " + String(rice_type));
    delay(3000);
    Serial.println("RiceWaterScale: " + String(rice_water_scale));
}
