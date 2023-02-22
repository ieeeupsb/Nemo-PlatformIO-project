

Wheel left_wheel(M1_L, M2_L, ENABLE_L, ENC1_L, ENC2_L);
Wheel right_wheel = Wheel(M1_R, M2_R, ENABLE_R, ENC1_R, ENC2_R);

// Interrupt service routine

void setup() {
    motor_rotation_dir_t motor_direction_dir = motor_rotation_dir_t::CLOCKWISE;
    Serial.begin(BAUD_RATE);
    left_wheel.SetDirection(motor_direction_dir);
    left_wheel.SetPwm(100);
    delay(500);
    // left_wheel.SetPwm(30);

    attach_all_interrupts();
}

#define WAIT_TIME_MS 1000

// int aux_print_motor_rpm() {
//     Serial.println(motor_controller.GetRpm());
// }

void loop() {

    // int rpm = left_wheel.GetRpm();
    int enc1 = digitalRead(ENC1_L);
    int enc2 = digitalRead(ENC2_L);
    NON_BLOCKING_DELAY_MS(Serial.println(left_wheel.GetRpm());, WAIT_TIME_MS);
}

void ace_main() {

    // nemo();
    // Nemo.AttachWheels();
}

// alias smonitor="platformio device monitor --port /dev/ttyACM0 --baud 115200"

// char buffer[BUFFER_SIZE];
// void loop() {
//     SerialParser serial_parser;

//     if (millis() - lastReadTime > 1000) { // Only read from serial port every 1 second
//         // strcpy(buffer, serial_parser.ReadInput());
//         // Serial.print("BEGIN OF READ----");
//         // Serial.print(buffer);
//         // Serial.println("----END OF READ");<DIR:LEFT;DIST:0.5;SPEED:0.5>
//         serial_parser.GetCommand();

//         lastReadTime = millis();
//     }
// }
