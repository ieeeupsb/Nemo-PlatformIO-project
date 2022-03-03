#include <Arduino.h>
#include "sonar/sonar.h"
#include "udp_client/udp_client.h"
#include "music/music.h"
#include "setup.h"

char color_code[4] = {};

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  delay(1000);
  Serial.print("Hello Esp32! \n");
  udp_setup();
  sonar_setup();

  Serial.println("Waiting for color code...");
  do {
    recieve_color_code(color_code);
  } while(color_code[0] == '\0');
  digitalWrite(13, HIGH);
  zelda_link_to_the_past_secret(BUZZER_PIN);

  Serial.println(color_code[0]);
  Serial.println(color_code[1]);
  Serial.println(color_code[2]);
  Serial.println(color_code[3]);
} 
#define BUZZER_CHANNEL 0
void loop() { 
ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
  ledcWriteNote(BUZZER_CHANNEL, NOTE_C, 4);
  delay(500);
  ledcWriteNote(BUZZER_CHANNEL, NOTE_D, 4);
  delay(500);
  ledcWriteNote(BUZZER_CHANNEL, NOTE_E, 4);
  delay(500);
  ledcWriteNote(BUZZER_CHANNEL, NOTE_F, 4);
  delay(500);
  ledcWriteNote(BUZZER_CHANNEL, NOTE_G, 4);
  delay(500);
  ledcWriteNote(BUZZER_CHANNEL, NOTE_A, 4);
  delay(500);
  ledcWriteNote(BUZZER_CHANNEL, NOTE_B, 4);
  delay(500);
  ledcDetachPin(BUZZER_PIN);
}