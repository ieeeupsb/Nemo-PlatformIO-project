# Nemo PIO Project
TODO: explain how to use the todo extension
TODO: create another README for the physical configurations and connections of the robot

## How to contribute to the PIO project with VS Code:
* First check the main project README.md file.
* Open nemo/nemo_pio folder in VS Code.
* Do not modify `main.cpp`, use `main_test.cpp` instead for testing.
* Use `platformio.ini` for mode configuration ([more about .ini file](###-.ini-file))
* Use proper documentation ([more about documentation](###-.documentation))
* Use code auto-format (enabled in this VS Code project workspace)
* Use TODO Tree extension properly ([more about TODO Tree](###-.todo-tree))

## Software structure:
* Nemo's software is designed is a three layer pyramid structure, so that it maintains consistency over different microcontrollers and functioning modes.
* First layer (bottom): l1_io_libs -> Controls communication between the microcontroller and the hardware. This layer may change with different microcontrollers. 
* Second layer: l2_function_libs -> Parses and formats IO information. Basic robot actions are defined in this layer, such as walking forward.
* Third layer: l3_modes_libs -> Different modes use the Nemo Libs differently do to different things. One mode might be an RC car, another mode might be an autonomous mode that doesn't use Bluetooth. Here is the main function.

Futhemore, the software pinout is in the `circuit` folder in the root directory of the project.

FIXME update this
### .ini file
If you want to build or upload a specific mode use
release in build type, for testing use test in build type
Changing here the configuration implies rebuilding the
project, for small changes, like activating
or deactivating the debug, go to 
nemo_libs/nemo_global_macros.h

```ini
;##########################################################
[nemo_configuration]
current_mode = rc_nemo
; Available modes: rc_nemo, raf4_0
baud_rate = 115200
build_type = test
; test/release
;##########################################################
```
### Documentation
* Install https://github.com/cschlosser/doxdocgen#templates extension
* Before function declaration or after creating a new file for auto-complete doxygen commands type `/**`, and press `Enter`

### TODO Tree

Setting up wifi (deprecated):

Put your wifi credentials here:
src/udp_client/wifi_credentials_private.h

in terminal:    linux: ipconfig -> ipv4     add to setup.h
                windows: ifconfig -> inet