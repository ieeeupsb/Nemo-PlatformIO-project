#include "nemo_communications.h"

unsigned long last_time_printf = 0;

#if DEBUG_MODE

// void printf_implemeted(const char *message) {
//     char aux_s[32];
//     if (millis() - last_time_printf > DEBUG_REFRESH_RATE) {
//         last_time_printf = millis();
//     } else
//         return;
//     sprintf(aux_s, message);
//     // printf_implemented(aux_s);
// #if USE_SERIAL
//     Serial.println(message);
// #endif

// #if USE_WIFI
//     udp.beginPacket(UDP_ADDRESS, UDP_PORT); // Initiate transmission of data

//     udp.printf(aux_s);
//     udp.endPacket(); // Close communication
// #endif
// }

int line_case_debug() {

    switch (LINE_CASE_FAST) {
    case CORRECT_TO_RIGHT:
        printf("CORRECT_TO_RIGHT");
        break;
    case CORRECT_TO_LEFT:
        printf("CORRECT_TO_LEFT");
        break;
    case RIGHT_CURVE:
        printf("RIGHT_CURVE");
        break;
    case LEFT_CURVE:
        printf("LEFT CURVE");
        break;
    case INTERCEPTION:
        printf("INTERCEPTION");
        break;
    case LINE:
        printf("LINE");
        break;
    case FREE:
        printf("FREE");
        break;
    default:
        printf("ERROR");
        return -1;
    }

    return LINE_CASE_FAST;
}
void debug_encoder(Motor m) {
    // printf("Left encoder: %d \n", (int32_t)m.encoder.getCount());
    // char auxs[32];
    // sprintf(auxs, "Left encoder: %d \n", (int32_t)m.encoder.getCount());
    // printf(auxs);
}

#endif