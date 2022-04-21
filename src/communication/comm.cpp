#include "comm.h"
#include "setup.h"
#include "wifi_credentials_private.h"

// https://www.alejandrowurts.com/projects/esp32-wifi-udp/
//  https://www.youtube.com/watch?v=U3vOyzJzGRU

#include <WiFi.h>
#include <WiFiUdp.h>

#define N_BOXES 4
#define M_CHARS 32

WiFiUDP udp;         // Creation of wifi Udp instance
WiFiUDP udp_monitor; // Creation of wifi Udp instance

char ip_address[] = UDP_ADDRESS;

void wifi_setup() {
    Serial.print("Trying to conecting to ");

    int n_networks = WiFi.scanNetworks();

    String ssid;
    String password;

    if (n_networks) {
        bool aux_break = 0;

        for (int i = 0; i < n_networks; i++) {

            if (aux_break)
                break;

            Serial.println(WiFi.SSID(i));
            for (int j = 0; j < N_NETWORKS; j++)
                if (WiFi.SSID(i).compareTo(networks[j]) == 0) {
                    ssid = networks[j];
                    password = passwords[j];
                    aux_break = 1;
                    break;
                }
        }
    } else {
        Serial.println("Não encontrrou nenhuma rede Wifi conhecida");
        return;
    }

    WiFi.begin(ssid.c_str(), password.c_str());
    int retries = 0;
    while ((WiFi.status() != WL_CONNECTED) && (retries < 15)) {
        retries++;
        delay(500);
        Serial.print(".");
    }
    if (retries > 14) {
        Serial.println(F("WiFi connection FAILED"));
    } else if (WiFi.status() == WL_CONNECTED) {
        Serial.println(F("WiFi connected!"));
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP()); // 192.168.1.151
    }
    udp.begin(UDP_PORT);
    Serial.println("Is this your local ip: " + (String)ip_address + "?");
}

void recieve_colour_code(char *colour_code, char local) {
    char *message = NULL;

    switch (local) {
    case 'I':
        send_data("IWP", UDP_ADDRESS);
        break;
    case 'O':
        send_data("OWP", UDP_ADDRESS);
        break;
    case 'A':
        send_data("MAP", UDP_ADDRESS);
        break;
    case 'B':
        send_data("MBP", UDP_ADDRESS);
        break;
    }

    Serial.println("Looking for next UDP package");
    while (!message)
        message = receive_data();
    Serial.println("Valid package recieved from server...");

    for (int i = 0; i < N_BOXES; i++) {
        char aux = message[i];

        if ((aux != 'R') & (aux != 'G') & (aux != 'B')) {
            Serial.println("Invalid message for colour code");
            colour_code[0] = '\0';
            return;
        }
        colour_code[i] = aux;
    }
}
char *receive_data() {
    char *ret = (char *)calloc(M_CHARS, 1);
    udp.parsePacket();
    if (udp.read(ret, M_CHARS) > 0) {
        Serial.print("Returning message from server: ");
        return ret;
    }
    free(ret);
    ret = NULL;
    return ret;
}

char *recieve_data_impl() {
    char *message = NULL;
    Serial.println("Looking for next UDP package");
    while (!message)
        message = receive_data();
    Serial.println("Valid package recieved from server...");

    Serial.print("Recieving: ");
    Serial.println(message);

    return message;
}

void send_data(const char *message, const char *udpAddress) {

    udp.beginPacket(udpAddress, UDP_PORT); // Initiate transmission of data

    udp.printf(message);
    udp.endPacket(); // Close communication
}

void debug_message(const char *message) {

    if (!DEBUG_MODE)
        return;
    udp.beginPacket(UDP_ADDRESS, UDP_PORT); // Initiate transmission of data

    udp.printf(message);
    udp.endPacket(); // Close communication

    Serial.println(message);
}

void receive_colour_code_imp(char colour_code[4]) {

    debug_message("Waiting for colour code...");
    do {
        recieve_colour_code(colour_code, 'I');
    } while (colour_code[0] == '\0');
}
