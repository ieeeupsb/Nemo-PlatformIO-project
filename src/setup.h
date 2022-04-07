#include "ESP32_pinout.h"

#define COMP_UPD_ADDRESS "192.168.1.177" // Comp server ip addr
#define MONITOR_UPD_ADDRESS "192.168.1.177" // Monitor server ip addr

// 4 linha
// 4 para cada motor (8 total)
// 2 sonar
// 1 electroiman

// SENSORES DE LINHA
#define LINE_SENSOR_1 GPIO36
#define LINE_SENSOR_2 GPIO39
#define LINE_SENSOR_3 GPIO34
#define LINE_SENSOR_4 GPIO35

#define ELECTRO_IMAN GPIO32

// MOTOR A
#define DC_MOTOR_1A GPIO23
#define ENC1_A GPIO22
#define ENC2_A GPIO1
#define DC_MOTOR_2A GPIO3

// MOTOR B
#define DC_MOTOR_1B GPIO21
#define ENC1_B GPIO19
#define ENC2_B GPIO18
#define DC_MOTOR_2B GPIO5

// SONAR
#define SONAR_TRIG GPIO25
#define SONAR_ECHO GPIO33
