#pragma once

#include "mcu_pinouts.h"

#ifdef PICO

#include "pico_pinout.h"

// LEFT MOTOR
#define DRIVER_ENABLE_PIN_L PORT26_GP20
#define DRIVER_IN_A_PIN_L PORT25_GP19
#define DRIVER_IN_B_PIN_L PORT24_GP18
// THERE IS A GROUND BETWEEN THIS
#define ENC_C1_PIN_L PORT22_GP17
#define ENC_C2_PIN_L PORT21_GP16

// RIGHT MOTOR
#define DRIVER_ENABLE_PIN_R PORT15_GP11
#define DRIVER_IN_A_PIN_R PORT16_GP12
#define DRIVER_IN_B_PIN_R PORT17_GP13
// THERE IS A GROUND BETWEEN THIS
#define ENC_C1_PIN_R PORT19_GP14
#define ENC_C2_PIN_R PORT20_GP15

#endif

#ifdef ESP32
#include "ESP32_pinout.h"

// LEFT MOTOR
#define DC_MOTOR_1L RDX   // in_3 -> header_1_pin1 -> rdx
#define DC_MOTOR_2L GPIO5 // in_4 -> header_1_pin2 -> gpio5
#define ENABLE_L GPIO12   // en_b -> header_1_pin3-> gpio12
#define ENC1_L GPIO16     // yellow
#define ENC2_L GPIO17     // white

// RIGHT MOTOR
#define DC_MOTOR_1R GPIO21 // in_1 -> header_1_pin5 -> gpio21
#define DC_MOTOR_2R GPIO23 // in_2 -> header_1_pin7 -> gpio23
#define ENABLE_R GPIO13    // en_a -> header_1_pin8 -> gpio13

#define ENC1_R GPIO18 // yellow
#define ENC2_R GPIO19 // white

#endif

#ifdef PORTENTA1

#define DC_MOTOR_1L RDX   // in_3 -> header_1_pin1 -> rdx
#define DC_MOTOR_2L GPIO5 // in_4 -> header_1_pin2 -> gpio5
#define ENABLE_L GPIO12   // en_b -> header_1_pin3-> gpio12
#define ENC1_L GPIO16     // yellow
#define ENC2_L GPIO17     // white

#endif