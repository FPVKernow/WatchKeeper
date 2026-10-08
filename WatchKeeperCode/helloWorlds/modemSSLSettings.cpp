//Code to get modem info and battery voltage

//Define the modem that will be used by TinyGSM
#define TINY_GSM_MODEM_SIM7000SSL
#define TINY_GSM_BUFFER 1024

//Inlcude Arduino framework
//Include TinyGsm
#include <Arduino.h>
#include <TinyGsmClient.h>
#include <PubSubClient.h>
#include <certs.h>
#include <secrets.h>

//Define serail connecitons for printing to terminal and sending to modem
#define SerialAT Serial1
#define SerialMon Serial

TinyGsm modem(SerialAT);
TinyGsmClientSecure secureClient(modem, 0);
PubSubClient mqttClient(secureClient);

//Generic details used for testing with basic sim from giffgaff.
#define GSM_PIN ""
const char apn[] = "giffgaff.com";
const char gprsUser[] = "gg";
const char gprsPass[] = "p";

char mqttIP[] = MQTTserver;
char mqttUSER[] = MQTTuser;
char mqttPASS[] = MQTTpass;

char cert[] = CERT;

//board pins
#define UART_BAUD           115200
#define PIN_DTR             25
#define PIN_TX              27
#define PIN_RX              26
#define PWR_PIN             4
#define SD_MISO             2
#define SD_MOSI             15
#define SD_SCLK             14
#define SD_CS               13
#define LED_PIN             12

//power on modem
void modemPowerOn(){
    pinMode(PWR_PIN, OUTPUT);
    digitalWrite(PWR_PIN, LOW);
    delay(1000);
    digitalWrite(PWR_PIN, HIGH);
}

//power cycle modem
void modemPowerOff(){
    pinMode(PWR_PIN, OUTPUT);
    digitalWrite(PWR_PIN, LOW);
    delay(1500);
    digitalWrite(PWR_PIN, HIGH);
}

//reboot modem
void modemRestart(){
    modemPowerOff();
    delay(1000);
    modemPowerOn();
}

void setup(){
    //set baud rate
    SerialMon.begin(115200);

    delay(10);

    //turn LED off
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    modemPowerOn();

    //set SerialAt to modem
    SerialAT.begin(UART_BAUD, SERIAL_8N1, PIN_RX, PIN_TX);

    delay(2000);

    //initalise modem
    Serial.println("Initializing modem...");
    if (!modem.restart()) {
        Serial.println("Failed to restart modem, attempting to continue without restarting");
        modem.init();
    }

    //connect to GPRS
    modem.waitForNetwork();
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    delay(10000);
    SerialMon.println("Connecting to GPRS");
    return;
    }

    SerialMon.println("Setting MQTT connection");
    secureClient.connect(mqttIP, 8883);

    SerialMon.println("Setting connection");
    mqttClient.setServer(mqttIP, 8883);


    delay(5000);
}

void loop(){
    for (int i = 0; i < 1; i++){
    //get modem name
    String modemName = modem.getModemName();
    delay(500);
    SerialMon.println("Modem Name: "+modemName);

    //get modem info
    String modemInfo = modem.getModemInfo();
    delay(500);
    SerialMon.println("Modem Info: "+ modemInfo);
    }

    String settingsSSL;
    modem.sendAT("+CSSLCFG?");
    modem.waitResponse(1000L, settingsSSL);
    SerialMon.println(settingsSSL);

    String SSL;
    modem.sendAT("+CASSLCFG?");
    modem.waitResponse(1000L, SSL);
    SerialMon.println(SSL);
}