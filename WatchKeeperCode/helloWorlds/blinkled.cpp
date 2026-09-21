//basic blink LED on T-SIM7000G

#include <Arduino.h>

#define LED_PIN 12
#define SerialMon Serial

void setup() {
  SerialMon.begin(115200);//Baud rate for T-SIM7000G

  pinMode(LED_PIN, OUTPUT); //define pin output
  digitalWrite(LED_PIN, HIGH); //set initial state
}

void loop() { //loops blink LED
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED ON");
  delay(5000);
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED OFF");
  delay(5000);
}