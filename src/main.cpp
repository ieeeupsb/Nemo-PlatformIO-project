#include <Arduino.h>
#include "sonar/sonar.h"
#include "udp_client/udp_client.h"
#include "music/music.h"
#include "setup.h"

char color_code[4] = {};

void setup() {
  Serial.begin(9600);
  
  delay(1000);
  Serial.print("Hello Esp32! \n");
  udp_setup();
  sonar_setup();

  Serial.println("Waiting for color code...");
  do {
    recieve_color_code(color_code);
  } while(color_code[0] == '\0');

  Serial.println(color_code[0]);
  Serial.println(color_code[1]);
  Serial.println(color_code[2]);
  Serial.println(color_code[3]);
} 
#define BUZZER_CHANNEL 0
void loop() { 

}