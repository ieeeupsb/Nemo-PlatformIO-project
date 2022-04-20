#define DEBUG_MODE true
#define NEMO_SPEED 170 //0-255
#define UDP_ADDRESS "192.168.0.116" // Comp server ip addr
#define UDP_PORT 44832U

#define ENV ESP32DEV
#if ENV == ESP32DEV

#include <ESP32_pinout.h>

// 4 linha
// 4 para cada motor (8 total)
// 2 sonar
// 1 electroiman

// SENSORES DE LINHA
#define LINE_SENSOR_1 GPIO36 // RIGHT SIDE (VP) //
#define LINE_SENSOR_2 GPIO39 // (VN) // grey
#define LINE_SENSOR_3 GPIO34 // 
#define LINE_SENSOR_4 GPIO35 // LEFT SIDE

// ELETROINAGNET
#define ELECTROMAGNET GPIO32 //purple

// LEFT MOTOR
#define DC_MOTOR_1L GPIO3   // white
#define DC_MOTOR_2L GPIO5   // brown
#define ENABLE_L GPIO12     // WARNING: ADC2 PIN //red
#define ENC1_L GPIO16       // yellow
#define ENC2_L GPIO17       // white

// RIGHT MOTOR
#define DC_MOTOR_1R GPIO21  // white
#define DC_MOTOR_2R GPIO23  // brown
#define ENABLE_R GPIO13     // WARNING: ADC2 PIN //grey
#define ENC1_R GPIO18       // yellow
#define ENC2_R GPIO19       // white

// SONAR
#define SONAR_TRIG GPIO25   //  green
#define SONAR_ECHO GPIO33   // red
#endif