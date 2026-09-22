//Following randomNerd tutorial

#define TINY_GSM_MODEM_SIM7000
#define TINY_GSM_RX_BUFFER 1024

#include <TinyGsmClient.h>
#include <Arduino.h> //Need to include Arduino as other libraries are only supported by Arduino framework

#define UART_BAUD 115200
#define PIN_DTR   25
#define PIN_TX    27
#define PIN_RX    26
#define PWR_PIN   4

#define LED_PIN   12

#define SerialMon Serial
#define SerialAT Serial1

TinyGsm modem(SerialAT);

void setup(){
  SerialMon.begin(115200);
  SerialMon.println("Place in view of GNSS satelites");

  //Set LED off
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  //Turn on modem
  pinMode(PWR_PIN, OUTPUT);
  digitalWrite(PWR_PIN, HIGH);
  delay(300);
  digitalWrite(PWR_PIN, LOW);

  delay(1000);

  //set modeule baud rate and UART pins
  SerialAT.begin(UART_BAUD,SERIAL_8N1,PIN_RX,PIN_TX);

  SerialMon.println("Initialising Modem");
  if (!modem.restart()){
    SerialMon.println("Failed to restart. Continuing without restarting");
  }

  //Modem info:
  String modemName = modem.getModemName();
  delay(500);
  SerialMon.println("Modem Name: "+modemName);

  String modemInfo = modem.getModemInfo();
  delay(500);
  SerialMon.println("Modem Info: "+ modemInfo);
}

void loop(){
}