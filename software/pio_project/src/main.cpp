
#include "Arduino.h"
#include "motion_controller.h"
#include "motor_controller.h"
#include "pin_wiring.h"
#include <PID_AutoTune_v0.h>
#include <PID_v1.h>

wheels_speed_t wheels_speed;
Robot &robot = Robot::getInstance();

byte ATuneModeRemember = 2;
double input = 80, output = 50, setpoint = 0.3;
double kp = 200, ki = 0, kd = 0;

double kpmodel = 1.5, taup = 100, theta[50];
double outputStart = 5;
double aTuneStep = 50, aTuneNoise = 1, aTuneStartValue = 100;
unsigned int aTuneLookBack = 20;

boolean tuning = false;
unsigned long modelTime, serialTime;

MotorController left_motor_controller(DRIVER_ENABLE_PIN_L, DRIVER_IN_A_PIN_L, DRIVER_IN_B_PIN_L, kp, ki, kd);
MotorController right_motor_controller(DRIVER_ENABLE_PIN_R, DRIVER_IN_A_PIN_R, DRIVER_IN_B_PIN_R, kp, ki, kd);

PID *myPID = left_motor_controller.getPid();
PID_ATune aTune(&input, &output);

// set to false to connect to the real world
boolean useSimulation = false;

void updateLeftCount() {
    robot.updateLeftCount();
}

void updateRightCount() {
    robot.updateRightCount();
}

void AutoTuneHelper(boolean start) {
    if (start)
        ATuneModeRemember = myPID->GetMode();
    else
        myPID->SetMode(ATuneModeRemember);
}

void changeAutoTune() {
    if (!tuning) {
        // Set the output to the desired starting frequency.
        output = aTuneStartValue;
        aTune.SetNoiseBand(aTuneNoise);
        aTune.SetOutputStep(aTuneStep);
        aTune.SetLookbackSec((int)aTuneLookBack);
        AutoTuneHelper(true);
        tuning = true;
    } else { // cancel autotune
        aTune.Cancel();
        tuning = false;
        AutoTuneHelper(false);
    }
}

void SerialSend() {
    Serial.print("setpoint: ");
    Serial.print(setpoint);
    Serial.print(" ");
    Serial.print("input: ");
    Serial.print(input);
    Serial.print(" ");
    Serial.print("output: ");
    Serial.print(output);
    Serial.print(" ");
    if (tuning) {
        Serial.println("tuning mode");
    } else {
        Serial.print("kp: ");
        Serial.print(myPID->GetKp());
        Serial.print(" ");
        Serial.print("ki: ");
        Serial.print(myPID->GetKi());
        Serial.print(" ");
        Serial.print("kd: ");
        Serial.print(myPID->GetKd());
        Serial.println();
    }
}

void SerialReceive() {
    if (Serial.available()) {
        char b = Serial.read();
        Serial.flush();
        if ((b == '1' && !tuning) || (b != '1' && tuning))
            changeAutoTune();
    }
}

void DoModel() {
    // cycle the dead time
    for (byte i = 0; i < 49; i++) {
        theta[i] = theta[i + 1];
    }
    // compute the input
    input = (kpmodel / taup) * (theta[0] - outputStart) + input * (1 - 1 / taup) + ((float)random(-10, 10)) / 100;
}

// void setup() {
//     attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_L), updateLeftCount, CHANGE);
//     attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_R), updateRightCount, CHANGE);

//     if (useSimulation) {
//         for (byte i = 0; i < 50; i++) {
//             theta[i] = outputStart;
//         }
//         modelTime = 0;
//     }
//     // Setup the pid
//     myPID->SetMode(AUTOMATIC);

//     if (tuning) {
//         tuning = false;
//         changeAutoTune();
//         tuning = true;
//     }

//     serialTime = 0;
//     Serial.begin(9600);
// }

// void loop() {

//     unsigned long now = millis();

//     if (!useSimulation) { // pull the input in from the real world
//         input = robot.wheel_speed_calculator().left_wheel_speed;
//     }

//     if (tuning) {
//         byte val = (aTune.Runtime());
//         if (val != 0) {
//             tuning = false;
//         }
//         if (!tuning) { // we're done, set the tuning parameters
//             kp = aTune.GetKp();
//             ki = aTune.GetKi();
//             kd = aTune.GetKd();
//             myPID->SetTunings(kp, ki, kd);
//             AutoTuneHelper(false);
//         }
//     } else
//         myPID->Compute();

//     if (useSimulation) {
//         theta[30] = output;
//         if (now >= modelTime) {
//             modelTime += 100;
//             DoModel();
//         }
//     } else {
//         left_motor_controller.getDriverController()->setPwm(output);
//         right_motor_controller.getDriverController()->setPwm(output);
//     }

//     // send-receive with processing if it's time
//     if (millis() > serialTime) {
//         SerialReceive();
//         SerialSend();
//         serialTime += 500;
//     }
// }
void setup() {
    left_motor_controller.test_motor();

    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_L), updateLeftCount, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_R), updateRightCount, CHANGE);

    left_motor_controller.enablePidControl();
    left_motor_controller.SetPIDConstants(500, 500, 500);

    serialTime = 0;
    Serial.begin(9600);
    left_motor_controller.setTargetSpeed(0.3);
}

void loop() {
    left_motor_controller.updateSpeedRead(0.1);
    left_motor_controller.Compute();
    left_motor_controller.setPidPwm();
}
