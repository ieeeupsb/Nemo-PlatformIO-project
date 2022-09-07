#pragma once
#include "Arduino.h"

#define pin_mode pinMode
#define digital_write digitalWrite

#if ESP32

#define analog_attach_pin ledcAttachPin
#define analog_channel_write ledcWrite
#define analog_channel_setup ledcSetup

#else

#define analog_write analogWrite

#endif