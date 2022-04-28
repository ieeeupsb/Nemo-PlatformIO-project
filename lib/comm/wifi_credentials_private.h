#pragma once

#include <Arduino.h>

#define N_NETWORKS 4

#define DEFAULT_NETWORK 3

#define casa_ssid "Vodafone-77312E"
#define casa_password "jkJyjeh7cp"

#define ieee_ssid "ieeehotspot"
#define ieee_password "Jk638td9og35"

#define rbpi_ssid "raspeberrypi"
#define rbpi_password "UJr2016#"

#define TP_LINK_1DC0_ssid "TP-LINK-1DC0"
#define TP_LINK_1DC0_password "08840530"

String networks[N_NETWORKS] = {TP_LINK_1DC0_ssid, casa_ssid, ieee_ssid,
                               rbpi_ssid};
String passwords[N_NETWORKS] = {TP_LINK_1DC0_password, casa_password,
                                ieee_password, rbpi_password};