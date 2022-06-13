#include "comm.h"

#include "wifi_credentials_private.h"

#define M_CHARS 32

WiFiUDP udp; // Creation of wifi Udp instance
bool wifi_is_setup = false;

void wifi_setup(const char *ip_address, int udp_port) {
    String ssid;
    String password;

    int n_networks = WiFi.scanNetworks();

    if (n_networks) {
        bool aux_break = 0;

        for (int i = 0; i < n_networks; i++) {

            if (aux_break)
                break;

            for (int j = 0; j < N_NETWORKS; j++)
                if (WiFi.SSID(i).compareTo(networks[j]) == 0) {
                    Serial.print("Connecting to: ");
                    Serial.println(WiFi.SSID(i));
                    ssid = networks[j];
                    password = passwords[j];
                    aux_break = 1;
                    break;
                }
        }
    } else {
        Serial.println("Não encontrou nenhuma rede Wifi conhecida");
        ssid = networks[DEFAULT_NETWORK];
        password = password[DEFAULT_NETWORK];
    }

    WiFi.begin(ssid.c_str(), password.c_str());
    int retries = 0;
    while ((WiFi.status() != WL_CONNECTED) && (retries < 15)) {
        retries++;
        delay(500);
        Serial.print(".");
    }
    if (retries > 30) {
        Serial.println(F("WiFi connection FAILED"));
        wifi_is_setup = false;
        return;
    } else if (WiFi.status() == WL_CONNECTED) {
        Serial.println(F("WiFi connected!"));
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP()); // 192.168.1.151
    }
    udp.begin(udp_port);
    Serial.println("Is this your local ip: " + (String)ip_address + "?");
    wifi_is_setup = true;
}
// void wifi_simple() {
//     WiFi.begin("RaF2022_2_4", "");
//     int retries = 0;
//     while ((WiFi.status() != WL_CONNECTED) && (retries < 15)) {
//         retries++;
//         delay(500);
//         Serial.print(".");
//     }
//     if (retries > 14) {
//         Serial.println(F("WiFi connection FAILED"));
//         wifi_is_setup = false;
//         return;
//     } else if (WiFi.status() == WL_CONNECTED) {
//         Serial.println(F("WiFi connected!"));
//         Serial.println("IP address: ");
//         Serial.println(WiFi.localIP()); // 192.168.1.151
//     }
//     udp.begin(udp_port);
//     Serial.println("Is this your local ip: " + (String)ip_address + "?");
//     wifi_is_setup = true;
// }

char *receive_data() {
    if (!wifi_is_setup)
        return NULL;
    char *ret = (char *)calloc(32, 1);
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
    if (!wifi_is_setup)
        return NULL;
    char *message = NULL;
    Serial.println("Looking for next UDP package");
    while (!message)
        message = receive_data();
    Serial.println("Valid package recieved from server...");

    Serial.print("Recieving: ");
    Serial.println(message);

    return message;
}

void send_data(const char *message, const char *udpAddress, uint16_t udp_port) {

    if (!wifi_is_setup)
        return;
    udp.beginPacket(udpAddress, udp_port); // Initiate transmission of data

    udp.printf(message);
    udp.endPacket(); // Close communication
}
