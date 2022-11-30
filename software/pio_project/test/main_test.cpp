#include "Arduino.h"

// the setup function runs once when you press reset or power the board
void setup() {
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH); // turn the LED off after being turned on by pinMode()
}

// the loop function runs over and over again forever
void loop() {
    digitalWrite(13, LOW);  // turn the LED on (LOW is the voltage level)
    delay(1000);            // wait for a second
    digitalWrite(13, HIGH); // turn the LED off by making the voltage HIGH
    delay(1000);            // wait for a second
}