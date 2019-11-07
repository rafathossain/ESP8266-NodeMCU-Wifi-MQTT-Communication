ESP8266 WiFi and MQTT Communication
===========================================
This tutorial is mainly focused on connecting the ESP8266 with WIFI and Communicate with NodeRed through MQTT Protocol. Read more about NodeRed here: [https://nodered.org/](https://nodered.org/)

# Installing ESP8266/NodeMCU Board on Arduino IDE
Starting with 1.6.4, Arduino allows installation of third-party platform packages using Boards Manager. We have packages available for Windows, Mac OS, and Linux (32 and 64 bit).

- Install the current upstream Arduino IDE at the 1.8.7 level or later. The current version is on the [Arduino website](https://www.arduino.cc/en/main/software).
- Start Arduino and open the Preferences window.
- Enter ```https://arduino.esp8266.com/stable/package_esp8266com_index.json``` into the *Additional Board Manager URLs* field. You can add multiple URLs, separating them with commas.
- Open Boards Manager from Tools > Board menu and install *esp8266* platform (and don't forget to select your ESP8266 board from Tools > Board menu after installation).

#### Latest release [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/)
Boards manager link: `https://arduino.esp8266.com/stable/package_esp8266com_index.json`

Documentation: [https://arduino-esp8266.readthedocs.io/en/2.5.2/](https://arduino-esp8266.readthedocs.io/en/2.5.2/)

# How to connect and communicate
First download the zip from git and unzip in a folder. Copy the PubSubClient folder to your arduino library (Documents/Arduino/libraries) folder.

Now Open the code `ESP8266_Wifi_and_MQTT.ino`. 

Here you need to updated your wifi ssid and password.
```
//Wifi Connection
const char* ssid = "SSID";
const char* password = "PASSWORD";
```

This is the MQTT configuartion for connecting to NodeRed
```
//MQTT Configuration
const char* mqttServer = "SERVER_IP";
const int mqttPort = 8883;
const char* mqttUser = "MQTT_USERNAME";
const char* mqttPassword = "MQTT_PASSWORD";
```

You will find the `sendData` method which can be used to transmit data.

To receive data from nodered, you can use this piece of code:

Add this before void setup()
```
//MQTT Data Receive Configuration
//If RECEIVE_DATA flag is true then the MQTT will subscribe to the topic to receive data
const boolean RECEIVE_DATA = true;
const String RECEIVE_TOPIC = "COFFEEISLOVE_RX";
```

Then setup the `callback` method:
```
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
```

That's all! Now you can easily communicate between nodered and esp8266/nodemcu.

If you are facing any issues or unable to use nodered, just send me an email: [sayhi@rafat.me](mailto:sayhi@rafat.me)

<b>I have also servers available for nodered. You can email me to get a server with nodered.</b>

Thank you!
