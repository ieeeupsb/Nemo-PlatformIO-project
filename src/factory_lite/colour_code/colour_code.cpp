    #include "colour_code.h"
#include "setup.h"

void recieve_colour_code(char *colour_code, char local,
                         const char *udpAddress) {
    char *message = NULL;

    switch (local) {
    case 'I':
        send_data("IWP", udpAddress, UDP_PORT);
        break;
    case 'O':
        send_data("OWP", udpAddress, UDP_PORT);
        break;
    case 'A':
        send_data("MAP", udpAddress, UDP_PORT);
        break;
    case 'B':
        send_data("MBP", udpAddress, UDP_PORT);
        break;
    }

    Serial.println("Looking for next UDP package");
    do {
        message = receive_data();

    } while (!message);

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