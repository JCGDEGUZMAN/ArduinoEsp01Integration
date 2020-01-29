#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "JCGDeGuzman";
const char* password = "JCGDeGuzman@15";

const char* host = "http://jsonplaceholder.typicode.com/users/1";

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
    
    http.begin(host);
    httpCode = http.GET();

    if (httpCode > 0) {
 
    payload = http.getString();
    Serial.println(payload);
     
    }
    http.end();
  }
  delay(30000);
}
