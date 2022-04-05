#include <Arduino.h>
#include "sonar/sonar.h"
#include "communication/comm.h"
#include "setup.h"
#include "motor/motor.h"

char color_code[4] = {};

void setup() {
  Serial.begin(9600);
  
  delay(1000);
  Serial.print("Hello Esp32! \n");
  wifi_setup();
  // sonar_setup();
  //motors_setup();
  pinMode(DC_MOTOR_1A, OUTPUT);
  digitalWrite(DC_MOTOR_1A, HIGH);

  Serial.println("Waiting for color code...");
  do {
    recieve_color_code(color_code, 'I');
  } while(color_code[0] == '\0');

  Serial.println(color_code[0]);
  Serial.println(color_code[1]);
  Serial.println(color_code[2]);
  Serial.println(color_code[3]);
} 
void loop() { 
  //move_forward();
  delay(1000);
}