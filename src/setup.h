#include "ESP32_pinout.h"

#define COMP_UPD_ADDRESS "192.168.1.69" // Comp server ip addr
#define MONITOR_UPD_ADDRESS "192.168.1.69" // Monitor server ip addr

// 4 linha
// 2 para os motores
// 8 sonares
// 1 electroinam

#define LINE_SENSOR_1 GPIO36
#define LINE_SENSOR_2 GPIO39
#define LINE_SENSOR_3 GPIO34
#define LINE_SENSOR_4 GPIO35

// #define ELECTRO_IMAN 22

#define DC_MOTOR_1A GPIO22
#define ENC1_A GPIO1
#define ENC1_B GPIO3
#define DC_MOTOR_2A GPIO21

//  #define SONAR_TRIG_1 999
// #define SONAR_ECHO_1 GPIO38
// #define SONAR_TRIG_2 GPIO37
// #define SONAR_ECHO_2 GPIO38