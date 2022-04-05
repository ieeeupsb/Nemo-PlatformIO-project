#pragma once

#include <Arduino.h>

#define N_NETWORKS 3

#define casa_ssid "Vodafone-E828C5"
#define casa_password "a1234567"

#define ieee_ssid "ieeehotspot"
#define ieee_password "Jk638td9og35"

#define rbpi_ssid "raspeberrypi"
#define rbpi_password "UJr2016#"

String networks[N_NETWORKS] = {casa_ssid, ieee_ssid, rbpi_ssid};
String passwords[N_NETWORKS] = {casa_password, ieee_password, rbpi_password};