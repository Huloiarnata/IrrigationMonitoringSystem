#include <WiFi.h>
#include "ThingSpeak.h"

#define MOISTURE_SENSOR_PIN 33 // D33 pin on ESP32

char ssid[] = "Huloiarnata";   // your network SSID (name) 
char pass[] = "test1234";   // your network password
WiFiClient  client;

unsigned long myChannelNumber = 2462917;
const char * myWriteAPIKey = "PLDFKWER143MNEFY";

void setup() {
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    //Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  int sensorValue = analogRead(MOISTURE_SENSOR_PIN);
  float moisture = map(sensorValue, 0, 4095, 0, 100); // map to percentage
  moisture = (moisture - 100) * -1;

  Serial.print("Soil Moisture: ");
  Serial.print(moisture);
  Serial.println("%");

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  int x = ThingSpeak.writeField(myChannelNumber, 1, moisture, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  delay(2000); // Wait 20 seconds to update the channel again
}
