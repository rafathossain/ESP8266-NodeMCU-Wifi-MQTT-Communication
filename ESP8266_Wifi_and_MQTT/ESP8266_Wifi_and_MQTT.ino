/*=====================================================================
   Author:    Md. Rafat Hossain
   Created:   11 November 2019

   (c) Copyright by Md. Rafat Hossain
  =====================================================================*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

//Wifi Connection
const char* ssid = "SSID";
const char* password = "PASSWORD";

//MQTT Configuration
const char* mqttServer = "SERVER_IP";
const int mqttPort = 8883;
const char* mqttUser = "MQTT_USERNAME";
const char* mqttPassword = "MQTT_PASSWORD";

//Auto generated device id
const String deviceID = String(random(0xffff), HEX);

//MQTT Data Send Configuration
String SEND_TOPIC = "COFFEEISLOVE";

void setup() {
  Serial.begin(9600);
  connectWifi();
  connectMQTT();
}

void loop() {
  client.loop();  //This is used to make the connection alive

  //Sending data (Topic Name, Data))
  SendData("HELLO COFFEE");
  delay(1000);
}

void SendData(String msg){
  client.publish(SEND_TOPIC.c_str(), msg.c_str());
}

//This method will be called once data is received
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

//This method will connect to the given ssid
void connectWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

//This method will connect to the defined mqtt configuration
void connectMQTT() {
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect(deviceID.c_str(), mqttUser, mqttPassword)) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed with state");
      Serial.print(client.state());
      delay(2000);
    }
  }
}
