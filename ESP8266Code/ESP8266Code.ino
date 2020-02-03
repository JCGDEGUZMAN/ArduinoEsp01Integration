#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid     = "JCGDeGuzman";
const char* password = "JCGDeGuzman@15";

const char* view_host = "http://restapiarc.herokuapp.com/api/configurations.php";
const char* update_host = "http://restapiarc.herokuapp.com/api/update-configuration.php?id=1&is_mobile_app=true";

void setup(){
  Serial.begin(9600);
  delay(500);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to " + String(ssid));
    
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected!");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){
      HTTPClient http;
      int httpCode = 0;
      String payload = "";
      
      http.begin(view_host);
      httpCode = http.GET();
  
      if (httpCode > 0) {
   
      payload = http.getString();
      Serial.println("\n");

      separateKeyValueJSONPairs(payload);
      }
      http.end();
  }
  delay(50000);
}

void separateKeyValueJSONPairs(String payload){
    StaticJsonDocument<1000> doc;

    DeserializationError err = deserializeJson(doc, payload);

    if (err) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(err.c_str());
    }

    int id = doc[0]["id"];
    boolean is_mobile_app = doc[0]["is_mobile_app"];
    int cups_of_rice = doc[0]["cups_of_rice"];
    int rice_type = doc[0]["rice_type"];
    boolean is_done_cooking = doc[0]["is_done_cooking"];
    boolean is_rice_level_low = doc[0]["is_rice_level_low"];
    boolean is_water_level_low = doc[0]["is_water_level_low"];
    double rice_distance = doc[0]["rice_distance"];
    double water_distance = doc[0]["water_distance"];
    double rice_water_scale = doc[0]["rice_water_scale"];

    Serial.println("id: " + String(id));
    delay(3000);
    Serial.println("is_mobile_app: " + String(is_mobile_app));
    delay(3000);
    Serial.println("cups_of_rice: " + String(cups_of_rice));
    delay(3000);
    Serial.println("rice_type: " + String(rice_type));
    delay(3000);
    Serial.println("is_done_cooking: " + String(is_done_cooking));
    delay(3000);
    Serial.println("is_rice_level_low: " + String(is_rice_level_low));
    delay(3000);
    Serial.println("is_water_level_low: " + String(is_water_level_low));
    delay(3000);
    Serial.println("rice_distance: " + String(rice_distance));
    delay(3000);
    Serial.println("water_distance: " + String(water_distance));
    delay(3000);
    Serial.println("rice_water_scale: " + String(rice_water_scale));
}
