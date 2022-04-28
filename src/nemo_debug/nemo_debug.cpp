#include "nemo_debug.h"

void debug_message(const char *message) {

    if (!DEBUG_MODE)
        return;
    udp.beginPacket(UDP_ADDRESS, UDP_PORT); // Initiate transmission of data

    udp.printf(message);
    udp.endPacket(); // Close communication

    Serial.println(message);
}

int line_case_debug() {
    Serial.println(LINE_CASE_FAST);

    switch (LINE_CASE_FAST) {
    case CORRECT_TO_RIGHT:
        debug_message("CORRECT_TO_RIGHT");
        break;
    case CORRECT_TO_LEFT:
        debug_message("CORRECT_TO_RIGHT");
        break;
    case RIGHT_CURVE:
        debug_message("RIGHT_CURVE");
        break;
    case LEFT_CURVE:
        debug_message("LEFT CURVE");
        break;
    case INTERCEPTION:
        debug_message("INTERCEPTION");
        break;
    case LINE:
        debug_message("LINE");
        break;
    case FREE:
        debug_message("FREE");
        break;
    default:
        debug_message("ERROR");
        return -1;
    }

    return LINE_CASE_FAST;
}
void debug_encoder(Motor m) {
    char auxs[32];
    sprintf(auxs, "Left encoder: %d \n", (int32_t)m.encoder.getCount());
    debug_message(auxs);
}

void debug_motor(Motor m, int time) {
    m.set_speed(FORWARD, NEMO_SPEED);
    debug_encoder(m);
    // millis(time);
}