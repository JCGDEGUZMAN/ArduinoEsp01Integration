#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include<SoftwareSerial.h>
#include <ArduinoJson.h>
//SoftwareSerial Serial2(7,2);

const char* ssid     = "JCGDeGuzman";
const char* password = "JCGDeGuzman@15";

int id = 0;
int isDoneCooking = 0;
boolean isRiceLevelLow = 0;
boolean isWaterLevelLow = 0;
double riceDistance = 0.00;
double waterDistance = 0.00;
  
const char* view_host = "http://restapiarc.herokuapp.com/api/configurations.php";

String firstUrl = "id="+String(id);
String secondUrl = "&is_done_cooking="+String(isDoneCooking);
String thirdUrl = "&is_rice_level_low="+String(isRiceLevelLow);
String fourthUrl = "&is_water_level_low="+String(isWaterLevelLow);
String fifthUrl = "&rice_distance="+String(riceDistance);
String sixthUrl = "&water_distance="+String(waterDistance);

String update_url = "http://restapiarc.herokuapp.com/api/update-configuration.php?"+firstUrl+secondUrl+thirdUrl+fourthUrl+fifthUrl+sixthUrl;

void setup(){
  Serial.begin(9600);

  delay(500);

  WiFi.begin(ssid, password);
    
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){  
      getHttpData();
      getArduinoData();
  }
  delay(30000);
}

void getHttpData(){ 
  HTTPClient http;
  int httpCode = 0;
  String payload = "";

  http.begin(view_host);
  httpCode = http.GET();

  if (httpCode > 0){
    payload = http.getString();
    Serial.print(payload);
  }

  http.end();
}

void postHttpData(){
  HTTPClient http;
  int httpCode = 0;
  String payload = "";

  http.begin(update_url);
  httpCode = http.GET();

  if (httpCode > 0) {
    payload = http.getString();
  }

  http.end();
}

void getArduinoData(){
  String payloadString = "";

  if(Serial.available()){
    payloadString =  Serial.readString();

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
    Serial.print(F("deserializeJson() failed with esp code "));
    Serial.println(err.c_str());
    return;
  }
  
  id = doc[0]["Id"];
  isDoneCooking = doc[0]["IsDoneCooking"];
  isRiceLevelLow = doc[0]["IsRiceLevelLow"];
  isWaterLevelLow = doc[0]["IsWaterLevelLow"];
  riceDistance = doc[0]["RiceDistance"];
  waterDistance = doc[0]["WaterDistance"];

  if(id > 0){
    postHttpData();
  }
}