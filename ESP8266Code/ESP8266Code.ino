#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "JCGDeGuzman";
const char* password = "JCGDeGuzman@15";

int id;
boolean isDoneCooking;
boolean isRiceLevelLow;
boolean isWaterLevelLow;
double riceDistance;
double waterDistance;
boolean isMobileDataReceived;

const char* view_host = "http://restapiarc.herokuapp.com/api/configurations.php";

const String firstUrl = "id="+String(id);
const String secondUrl = "&is_done_cooking="+String(isDoneCooking);
const String thirdUrl = "&is_rice_level_low="+String(isRiceLevelLow);
const String fourthUrl = "&is_water_level_low="+String(isWaterLevelLow);
const String fifthUrl = "&rice_distance="+String(riceDistance);
const String sixthUrl = "&water_distance="+String(waterDistance);

const String update_url = "http://restapiarc.herokuapp.com/api/update-configuration.php?"+firstUrl+secondUrl+thirdUrl+fourthUrl+fifthUrl+sixthUrl;

void setup(){
  initializedConnection();
  loadDefaultValues();
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){  
      getHttpData();
  }
  delay(50000);
}

void loadDefaultValues(){
  id = 1;
  isDoneCooking = false;
  isRiceLevelLow = false;
  isWaterLevelLow = false;
  riceDistance = 0;
  waterDistance = 0;
  isMobileDataReceived = false;
}

void initializedConnection(){
  Serial.begin(9600);
  delay(500);

  WiFi.begin(ssid, password);
    
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

String getHttpData(){
  HTTPClient http;
  int httpCode = 0;
  String payload = "";

  http.begin(view_host);
  httpCode = http.GET();

  if (httpCode > 0) {
    payload = http.getString();
    Serial.print(payload);
    delay(5000);
  }

  http.end();

  return payload;
}
