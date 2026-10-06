//Code to get modem info and battery voltage

//Define the modem that will be used by TinyGSM
#define TINY_GSM_MODEM_SIM7000
#define TINY_GSM_BUFFER 1024

//Inlcude Arduino framework
//Include TinyGsm
#include <Arduino.h>
#include <TinyGsmClient.h>

//Define serail connecitons for printing to terminal and sending to modem
#define SerialAT Serial1
#define SerialMon Serial


TinyGsm modem(SerialAT);

//Generic details used for testing with basic sim from giffgaff.
#define GSM_PIN ""
const char apn[] = "giffgaff.com";
const char gprsUser[] = "gg";
const char gprsPass[] = "p";

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

    Serial.println("Initializing modem...");
    if (!modem.restart()) {
        Serial.println("Failed to restart modem, attempting to continue without restarting");
    }

    delay(5000);
}

void loop(){
    Serial.println("Initializing modem...");
    if (!modem.init()) {
        Serial.println("Failed to restart modem, attempting to continue without restarting");
    }

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

    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    delay(10000);
    return;
    }
    if (modem.isGprsConnected()) {
    Serial.println("connected");
    String res;
    String imei = modem.getIMEI();
    res = modem.sendSMS("Your number here", String("Hello World "));
    
    } else {
    Serial.println("not connected");
    modem.poweroff();
    }
    
    delay(60000);
    modem.poweroff();
    delay(60000);

}