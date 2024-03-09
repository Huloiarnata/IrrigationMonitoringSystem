#include <ThingSpeak.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define MOISTURE_SENSOR_PIN 33 // D33 pin on ESP32

const char* ssid = "Huloiarnata";
const char* password = "test1234";

unsigned long myChannelNumber = 2462917;
String apiKey = "PLDFKWER143MNEFY"; // replace with your ThingSpeak channel's Write API Key

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int wifiAttempt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    wifiAttempt++;
    if(wifiAttempt > 20){ // After 10 seconds timeout, stop execution
      Serial.println("Failed to connect to WiFi. Please check your credentials and signal strength.");
      while(true); // Stop execution
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  int sensorValue = analogRead(MOISTURE_SENSOR_PIN);
  float moisture = map(sensorValue, 0, 4095, 0, 100); // map to percentage
  moisture = (moisture - 100) * -1;

  Serial.print("Soil Moisture: ");
  Serial.print(moisture);
  Serial.println("%");

  if(WiFi.status() == WL_CONNECTED){ // Check for WiFi connection before sending data
    int status = ThingSpeak.writeField(myChannelNumber, 1, moisture, apiKey);
    if(status == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(status));
    }
  }
  else{
    Serial.println("Lost WiFi connection. Attempting to reconnect...");
    WiFi.begin(ssid, password); // Attempt to reconnect to WiFi
  }

  delay(1000); // wait for a second
}
