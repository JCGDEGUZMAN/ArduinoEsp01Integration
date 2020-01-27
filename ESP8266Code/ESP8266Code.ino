void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.write("Hello from ESP");
  delay(2000);
}
