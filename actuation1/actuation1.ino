#include "PubSubClient.h" 
#include "ESP8266WiFi.h"

#define relay_count 4

// WiFi
const char* ssid = "PSK-JioFiber_4G";                
const char* wifi_password = "19752001";

const char* mqtt_server = "192.168.29.208";  // IP of the MQTT broker
const char* mqtt_username = "shanki"; // MQTT username
const char* mqtt_password = "sscpsk5$5$5$"; // MQTT password
const char* clientID = "client_livingroom"; // MQTT client ID

WiFiClient wifiClient;


int previous_state[relay_count] = {0,0,0,0};
int cloud_state[relay_count] = {0,0,0,0};

int masterButtonPins[relay_count] = {16,5,4,0};
int relayPins[relay_count] = {14,12,13,15};

void cpy_prev_state()
{
  for(int i = 0;i < relay_count; i++)
  {
    previous_state[i] = cloud_state[i];
  }
}


bool cmp_state()
{
  bool flag = 1;
  for(int i = 0;i < relay_count; i++)
  {
    if(previous_state[i] != cloud_state[i])
      flag = 0;
  }
  return flag;
}

void log_state()
{
  for(int i = 0; i < relay_count; i++)
    Serial.print(cloud_state[i]);
  Serial.println();
}
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<relay_count;i++) {
    int receivedBit = payload[i];
//    Serial.print(receivedBit);
    if(receivedBit == '1')
      cloud_state[i] = 1;
    else
      cloud_state[i] = 0;
    Serial.print(cloud_state[i]);
  }
  Serial.println();

}

PubSubClient client(wifiClient); 

void actuate(){
  for(int i=0; i<relay_count;i++){
    digitalWrite(relayPins[i],cloud_state[i]);
  }
}

void readbutton(){

  for (int i=0;i<relay_count;i++){
    if(digitalRead(masterButtonPins[i]))
    {
      cloud_state[i] = !cloud_state[i];

    }
//    Serial.println(); 
  }
}
 
// void calculate(unsigned int length, int *physical, int *logical){
//   int finalvals[length];
//   for(int k=0;k<length;k++){
//     finalvals[k] = physical[k]&logical[k];
//   }
// }
// 
void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) {
 Serial.print("Attempting MQTT connection...");
 // Attempt to connect
 if (client.connect("Client")) {
  Serial.println("connected");
  // ... and subscribe to topic
  client.subscribe("test");             // led is the topic which we are going to add in rapberry pi
 } else {
  Serial.print("failed, rc=");
  Serial.print(client.state());
  Serial.println(" try again in 5 seconds");
  // Wait 5 seconds before retrying
  delay(5000);
  }
 }
}
 
void setup()
{
 Serial.begin(9600);
 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);

  for(int i=0; i<relay_count;i++){
  pinMode(masterButtonPins[i],INPUT);
  
  }

 for(int i=0; i<relay_count;i++){
  pinMode(relayPins[i],OUTPUT);
  
  }
  cpy_prev_state();

//digitalWrite(14,LOW);
//delay(5000);
//digitalWrite(14,HIGH);

}

 
void loop()
{
// Serial.println(cloud_state[0]);
 if (!client.connected()) {
  reconnect();
 }
 client.loop();
 readbutton();

  if(!cmp_state())
    actuate();
//    client.publish("real_state",);
  cpy_prev_state();

}
