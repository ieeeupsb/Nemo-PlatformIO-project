#pragma once

int server_setup();
char *receive_data();
char *recieve_data_impl();
void send_data(const char *message, const char *udpAddress);
void recieve_colour_code(char *colour_code, char local);
void wifi_setup();
void debug_message(const char *message);
void receive_colour_code_imp(char colour_code[4]);