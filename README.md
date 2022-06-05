Useful links:
    https://github.com/P33a/RobotAtFactoryLite

How to contribute:
Create new branches for new features
Do not modify "main.cpp", use main_test.cpp instead
Use "platformio.ini" for mode configuration:
; If you want to build or upload a specific mode use
; release in build type, for testing use test in build type
; Changing here the configuration implies rebuilding the
; project, for small changes, like activating
; or deactivating the debug, go to 
; nemo_libs/nemo_global_macros.h

Setting up wifi(old):

Put your wifi credentials here:
src/udp_client/wifi_credentials_private.h

in terminal:    linux: ipconfig -> ipv4     add to setup.h
                windows: ifconfig -> inet