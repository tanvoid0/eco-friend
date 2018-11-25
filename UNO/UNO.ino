#include <Wire.h>
int pin = A0;
int lux = 0;
void setup() {
 Wire.begin(8);                /* join i2c bus with address 8 */
// Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent); /* register request event */
 Serial.begin(9600);           /* start serial for debug */
}

void loop() {
 delay(500);
 lux = analogRead(pin);
 Serial.println(lux);
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    Serial.print(c);           /* print the character */
  }
 Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
 Wire.write("Light:sssssssssssssssssss ");  /*send string on request */
}
