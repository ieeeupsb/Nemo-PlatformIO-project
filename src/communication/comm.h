#pragma once

int server_setup();
char* receive_data();
char* recieve_data_impl();
void send_data(const char* message, const char* udpAddress);
void recieve_color_code(char* color_code, char local);
void wifi_setup();