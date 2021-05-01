#include "DHT.h"

//#define DHTPIN D5  // for ESP8266
#define DHTPIN 15  // for ESP32

#define DHTTYPE DHT11  // DHT11 or DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  dht.begin();
}
 
void loop() {
  float humidity = dht.readHumidity();
  delay(2000);
  float temperature = dht.readTemperature();
 
  // check if returns are valid and print the sensor data
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(temperature);
    Serial.println(" *C");
  }

  delay(10000);
}
