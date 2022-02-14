#include <Arduino.h>
#include "sonar/sonar.h"

void setup() {
  Serial.begin(9600);
  sonar_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
}


void loop() {
  // put your main code here, to run repeatedly:
  
  float d = distance();

  Serial.print("Distancia = ");
  if (d >= 400 || d <= 2.5) {
    Serial.println("Fora de alcance");
    delay(500);
    }
  else {
    Serial.print(d);
    Serial.println(" cm");
    delay(25);
    }
   Serial.println(MAXTIME);
}