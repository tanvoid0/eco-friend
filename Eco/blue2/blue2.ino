/*Developer: Frederik Hauke

Important Notices:

This Arduino-Code is written for Visualizating measurement data from a microcontroller via Bluetooth.

Before starting this application, the Bluetooth-Modul (HC-05) has to be coupled to the Smartphone.In the special case of the HC-05 the default PinCode for initiating the Coupling-Process is "1234".

Wiring: GND of HC-05 to GND Arduino, VCC of HC-05 to VCC Arduino, TX HC-05 to Arduino Pin 10 (RX) RX HC-05 to Arduino Pin 11 (TX) */

#include <SoftwareSerial.h>

SoftwareSerial BTserial(10, 11); // RX | TX

int sensorPin = A0;

int sensorValue = 0;

const int ledPin = 13;
const int ldrPin = A0;

void setup() {

  BTserial.begin(9600); 
  //Serial.begin(9600);

pinMode(ledPin, OUTPUT);

pinMode(ldrPin, INPUT);

}

void loop() {

  //sensorValue = analogRead(sensorPin);

  //IMPORTANT: The complete String has to be of the Form: 1234,1234,1234,1234;

  //(every Value has to be seperated through a comma (',') and the message has to

  //end with a semikolon (';'))
  ldr();
  BTserial.print("1234");

  BTserial.print(",");

  BTserial.print("1234.0");

  BTserial.print(",");

  BTserial.print("1234 hPa");

  BTserial.print(",");

  BTserial.print("500 ml/s");

  BTserial.print(",");

  BTserial.print(sensorValue);

  BTserial.print(";");

  //message to the receiving device

  delay(20);

}

void ldr(){
  int ldrStatus = analogRead(ldrPin);

  if (ldrStatus <= 200) {

    digitalWrite(ledPin, HIGH);

    //Serial.print("Its DARK, Turn on the LED : ");

    //Serial.println(ldrStatus);

  } else {

    digitalWrite(ledPin, LOW);

    //Serial.print("Its BRIGHT, Turn off the LED : ");

    Serial.println(ldrStatus);
  }
  delay(1000);

}
