
#ifndef NEMO_COMMUNICATIONS_H
#define NEMO_COMMUNICATIONS_H

#if DEBUG_MODE

#include <Arduino.h>
#include <comm.h>
#include <line.h>
#include <motor.h>
#include <nemo_setup.h>

// #define printf(format)                                                         \
//     {                                                                          \
//         char aux_s[32];                                                        \
//         sprintf(aux_s, message);
// }

// #define printf(format)                                                         \
//     {                                                                          \
//                                                                \
//         if (millis() - last_time_printf > DEBUG_REFRESH_RATE) {                \
//             last_time_printf = millis();                                       \
//         } else                                                                 \
//             return;                                                            \
//         sprintf(aux_s, message);
// if (USE_SERIAL)
//     Serial.println(message);
// if (USE_WIFI)
//     udp.beginPacket(UDP_ADDRESS, UDP_PORT); // Initiate transmission of data
// udp.printf(aux_s);
// udp.endPacket(); // Close communication
// }

#define DEBUG_SPEED                                                            \
    {                                                                          \
        debug_message(aux, "Left speed %f: Right speed %f \n",                 \
                      left_motor.get_speed(), right_motor.get_speed());        \
    }

void debug_encoder(Motor m);
int line_case_debug();
void debug_motor(Motor m, int time);

#endif

#endif