#include <Arduino.h> //need to include Arduino.h for every code in this project that will be ran on T-SIM7000G
#include <secrets.h> //see comment at bottom of code

#define SerialMon Serial //defines serial monitoring

char hello[] = SECRET_greeting; //stored in secret.h

void setup(){
    SerialMon.begin(115200); //set the baud speed to T-SIM7000G
    delay(10000); //delay 10s
}

void loop(){
    SerialMon.println(hello); //print value of hello[] to terminal
    delay(5000);//delay 5s
}

//You can't see <secrets.h> as it is hidden in my .gitignore but for this example, it exclusively contains the following line:
//#define SECRET_greeting "Hello World";
//This has been a useful exercise in learning how to implement <secrets.h>.