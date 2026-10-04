#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <secrets.h>
#include <PubSubClient.h>
#include <certs.h>

char ssid[] = SSID;
char pass[] = PASS;

char mqttIP[] = MQTTserver;
char mqttUSER[] = MQTTuser;
char mqttPASS[] = MQTTpass;

char cert[] = CERT;

#define SerialMon Serial

WiFiClientSecure MQTTconnection;
PubSubClient mqttClient(MQTTconnection);

void setup(){
    delay(10000);
    SerialMon.begin(115200);
    WiFi.begin(ssid, pass);
    SerialMon.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED){
        SerialMon.print(".");
        delay(1000);
    }
    SerialMon.println("Connected to WiFi!");

    MQTTconnection.setCACert(cert);
    mqttClient.setServer(mqttIP, 8883);
}


void loop(){
    SerialMon.println(WiFi.localIP());
    delay(1000);

    while (!mqttClient.connected()){
        SerialMon.println("Attempting MQTT connecion");
        delay(1000);

        if (mqttClient.connect("TSIM",mqttUSER, mqttPASS)) {
        SerialMon.println("MQTT connecion sucsessful");
        mqttClient.publish("watchkeeper/devices/","hello world");
        }
    }
}