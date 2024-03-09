#define MOISTURE_SENSOR_PIN 33 // VP pin on ESP32 corresponds to GPIO 36

void setup() {
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(MOISTURE_SENSOR_PIN);
  float moisture = map(sensorValue, 0,4095, 0, 100); // map to percentage
  moisture  = (moisture-100)*-1;

  Serial.print("Soil Moisture: ");
  Serial.print(moisture);
  Serial.println("%");

  delay(1000); // wait for a second
}
