# Nano-OS
Nano-OS is a simple microcontroller operating system written in C++. The OS uses Arduino as memory and [PCPU-NANO1](https://github.com/Pepe-57/pcpu-nano1) as core for calculations. Nano-os is successor of [Esp-cf](https://github.com/Pepe-57/esp-cf). More features will be added in the future.
## Requirements
- 1x Pcpu-Nano1(used for most of all calculations)
- Arduino or other microcontroller board
- Arduino IDE
## Compatibily
- Tested on Arduino Uno R4 Wifi with 1x [PCPU-NANO1](https://github.com/Pepe-57/pcpu-nano1)
## Commands
- help, displays all commands
- ram, displays RAM, usage: ram [start address] [end address]
- diec, Direct Instruction Execution on Core, usage: diec [in, data, Instruction]
- sysinfo, displays system information

## Installation steps
1. Download and install Arduino IDE
2. Download [Nano-os](https://github.com/Pepe-57/nano-os)
3. Extract the archive to /Documents/Arduino/libraries
4. Open Arduino IDE and click File -> Examples -> NanoOS -> nano_os
5. Select your microcontroller and upload the sketch
6. Open serial monitor and set baud rate to same as 'Serial.begin()'
7. Press reset on the microcontroller and clear the serial monitor
8. Now it is ready to use

## Versions
### Firmware
- Release 1.0.0
- Release 1.1.0 (Latest)
### OS
- Release 1.0.0 (Latest)
