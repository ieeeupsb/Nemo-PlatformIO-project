#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <stdlib.h>

extern WiFiUDP udp; // Creation of wifi Udp instance
extern bool wifi_is_setup;

int server_setup();
char *receive_data();
char *recieve_data_impl();
void recieve_colour_code(char *colour_code, char local);
void wifi_setup(const char *ip_address, int udp_port);
void send_data(const char *message, const char *udpAddress, uint16_t udp_port);