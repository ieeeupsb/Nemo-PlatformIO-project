#pragma once

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

#ifdef PICO

#include "pico_pinout.h"

// LEFT MOTOR
#define ENABLE_L PORT14_GP10
#define ENC1_L PORT15_GP11
#define ENC2_L PORT16_GP12

// RIGHT MOTOR
#define ENABLE_R PORT25_GP19
#define ENC1_R PORT26_GP20
#define ENC2_R PORT27_GP21

#endif

#ifdef PORTENTA1

#define DC_MOTOR_1L RDX   // in_3 -> header_1_pin1 -> rdx
#define DC_MOTOR_2L GPIO5 // in_4 -> header_1_pin2 -> gpio5
#define ENABLE_L GPIO12   // en_b -> header_1_pin3-> gpio12
#define ENC1_L GPIO16     // yellow
#define ENC2_L GPIO17     // white

#endif