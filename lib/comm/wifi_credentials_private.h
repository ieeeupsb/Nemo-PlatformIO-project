#pragma once

#include <Arduino.h>

#define N_NETWORKS 2

#define DEFAULT_NETWORK 1

// #define casa_ssid "Vodafone-77312E"
// #define casa_password "jkJyjeh7cp"

// #define ieee_ssid "ieeehotspot"
// #define ieee_password "Jk638td9og35"

// #define rbpi_ssid "raspeberrypi"
// #define rbpi_password "UJr2016#"

// #define TP_LINK_1DC0_ssid "TP-LINK-1DC0"
// #define TP_LINK_1DC0_password "08840530"

#define RaF2022_ssid "RaF2022_2_4"
#define RaF2022_password "fnr2022!"

#define Robotica_SMF_ssid " Robotica_SMF"
#define Robotica_SMF_password "castelo2022"

String networks[N_NETWORKS] = {RaF2022_ssid, Robotica_SMF_ssid};
String passwords[N_NETWORKS] = {RaF2022_password, Robotica_SMF_password};

// String networks[N_NETWORKS] = {RaF2022_ssid, TP_LINK_1DC0_ssid, casa_ssid,
//                                ieee_ssid, rbpi_ssid};
// String passwords[N_NETWORKS] = {RaF2022_password, TP_LINK_1DC0_password,
//                                 casa_password, ieee_password, rbpi_password};