#define DEBUG_MODE true
#define UDP_ADDRESS                                                            \
    "192.168.1.43" // "192.168.120.187" //"192.168.0.116" // Comp server ip
                   // addr
#define UDP_PORT 44832U

#define ENV ESP32DEV
#define MODE FACTORY_LITE

#define BAUD_RATE 115200

#if ENV == ESP32DEV

#define NEMO_SPEED 125 // 140
#define MAX_SPEED 0.12 // 0.5
#define MIN_SPEED 0.1  // 0.25
#define USE_WIFI 0

#include <ESP32_pinout.h>

// 4 linha
// 4 para cada motor (8 total)
// 2 sonar
// 1 electroiman

// SENSORES DE LINHA
#define LINE_SENSOR_4 GPIO35 // LEFT SIDE //green
#define LINE_SENSOR_2 GPIO39 // (VN) // grey
#define LINE_SENSOR_3 GPIO34 // orange
#define LINE_SENSOR_1 VP     // RIGHT SIDE (VP) // purple

// ELETROINAGNET
#define ELECTROMAGNET GPIO32 // purple

// LEFT MOTOR
#define DC_MOTOR_1L RDX   // in_3 -> header_1_pin1 -> rdx
#define DC_MOTOR_2L GPIO5 // in_4 -> header_1_pin2 -> gpio5
#define ENABLE_L GPIO12   // en_b -> header_1_pin3-> gpio12
#define ENC1_L GPIO16     //
#define ENC2_L GPIO17     // white

// RIGHT MOTOR
#define DC_MOTOR_1R GPIO21 // in_1 -> header_1_pin5 -> gpio21
#define DC_MOTOR_2R GPIO23 // in_2 -> header_1_pin7 -> gpio23
#define ENABLE_R GPIO13    // en_a -> header_1_pin8 -> gpio13
#define ENC1_R GPIO18      // yellow
#define ENC2_R GPIO19      // white

// SONAR
#define SONAR_TRIG GPIO25 //  green
#define SONAR_ECHO GPIO33 // red
#endif