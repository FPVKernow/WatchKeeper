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
  modem.sendAT("+SGPIO=0,4,1,1");
  if (modem.waitResponse(10000L) != 1){
    SerialMon.println("SGPIO=0,4,1,1 is false");
  }

  modem.enableGPS();

  delay(15000);
  uint8_t status;
  float lat;
  float lon;
  float speed     = 0;
  float alt       = 0;
  int vsat        = 0;
  int usat        = 0;
  float accuracy  = 0;
  int year        = 0;
  int month       = 0;
  int day         = 0;
  int hour        = 0;
  int min         = 0;
  int sec         = 0;

  for (int8_t i = 2; i; i--){
    SerialMon.println("Getting GPS position");
    if (modem.getGPS(&status, &lat, &lon)){
      SerialMon.print("Latitude: " + String(lat, 8));
      SerialMon.println();
      SerialMon.print("Latitude: " + String(lon, 8));
      SerialMon.println();
      break;
    }
  }
}

//&speed, &alt, &vsat, &usat, &accuracy, &year, &month, &day, &hour, &min, &sec