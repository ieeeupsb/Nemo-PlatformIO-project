#include "udp_client.h"
#include "wifi_credentials_private.h"

//https://www.alejandrowurts.com/projects/esp32-wifi-udp/

#include <WiFi.h>
#include <WiFiUdp.h>

#define N_BOXES 4
#define M_CHARS 32
#define UDP_PORT 1234

WiFiUDP udp;  // Creation of wifi Udp instance

unsigned int udpPort = 44832;
const char * udpAddress = "192.168.1.69"; // your pc ip

void udp_setup() {
  Serial.print("Conecting to WiFi");
  
  WiFi.begin(ssid, password);
  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && (retries < 15)) {
    retries++;
    delay(500);
    Serial.print(".");
  }
  if (retries > 14) {
      Serial.println(F("WiFi connection FAILED"));
  }
  else if (WiFi.status() == WL_CONNECTED) {
      Serial.println(F("WiFi connected!"));
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP()); //192.168.1.151
  }
  udp.begin(UDP_PORT);
}

void recieve_color_code(char* color_code) {  
  char* message = NULL;
  Serial.println("Looking for next UDP package"); 
  while (!message) message = receive_data();
  Serial.println("Valid package recieved from server...");

  for (int i = 0; i < N_BOXES; i++) {
    char aux = message[i];

    if((aux != 'R') & (aux != 'G') & (aux != 'B')) {
      Serial.println("Invalid message for color code");
      color_code[0] = '\0';
      return;
    }
    color_code[i] = aux;
  }
}
char* receive_data() {
  char* ret = (char*)calloc(M_CHARS, 1);
  udp.parsePacket();
  if(udp.read(ret, M_CHARS) > 0){
    Serial.print("Returning message from server: ");
    return ret;
  }
  //Serial.print(".d");
  free(ret);
  ret = NULL;
  return ret;
}
