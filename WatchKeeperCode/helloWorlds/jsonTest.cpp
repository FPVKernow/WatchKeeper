//Code to get modem info and battery voltage

//Define the modem that will be used by TinyGSM
#define TINY_GSM_MODEM_SIM7000
#define TINY_GSM_BUFFER 1024

#include <Arduino.h>
#include <TinyGsmClient.h>
#include <ArduinoJson.h>

//Define serail connecitons for printing to terminal and sending to modem
#define SerialAT Serial1
#define SerialMon Serial


TinyGsm modem(SerialAT);

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
    delay(10000);
    //set baud rate
    SerialMon.begin(115200);

    JsonDocument doc;

    doc["Sensor"] = "gps";
    doc["Time"] = 123456789;

    JsonArray data = doc["data"].to<JsonArray>();
    data.add(50.0000);
    data.add(123.0000);

    serializeJson(doc, SerialMon);

    SerialMon.println();
    serializeJsonPretty(doc, SerialMon);

    delay(1000);

    //turn LED off
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
}

void loop(){

    
}