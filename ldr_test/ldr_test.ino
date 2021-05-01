#include "PubSubClient.h" 
#include "ESP8266WiFi.h"

const char* ssid = "PSK-JioFiber_4G";                
const char* wifi_password = "19752001";

const char* mqtt_server = "192.168.29.208";  // IP of the MQTT broker
const char* mqtt_topic = "Light_Sensor";
const char* mqtt_username = "shanki"; // MQTT username
const char* mqtt_password = "sscpsk5$5$5$"; // MQTT password
const char* clientID = "light_sensor_node"; // MQTT client ID

WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient);

const int ldrPin = A0;

void setup() {

Serial.begin(9600);
pinMode(ldrPin, INPUT);

Serial.print("Connecting to ");
Serial.println(ssid);

// Connect to the WiFi
WiFi.begin(ssid, wifi_password);

// Wait until the connection has been confirmed before continuing
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}

// Debugging - Output the IP Address of the ESP8266
Serial.println("WiFi connected");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());

// Connect to MQTT Broker
// client.connect returns a boolean value to let us know if the connection was successful.
if (client.connect(clientID)) {
  Serial.println("Connected to MQTT Broker!");
}
else {
  Serial.println("Connection to MQTT Broker failed...");
}


}

void loop() {
  // put your main code here, to run repeatedly:
  int ldrStatus = analogRead(ldrPin);
  char str[2];
  itoa(ldrStatus,str,10);
  client.publish(mqtt_topic, str);
  delay(2000);
}
