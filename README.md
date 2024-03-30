# Nano-OS
Nano-OS is a simple microcontroller operating system written in C++. The OS uses Arduino as memory and [PCPU-NANO1](https://github.com/Pepe-57/pcpu-nano1) as the core for calculations. More features will be added in the future. It's recommended to download from [releases](https://github.com/Pepe-57/nano-os/releases).
## Requirements
- 1x Pcpu-Nano1(used for most of all calculations)
- Arduino or other microcontroller board
- Arduino IDE
## Compatibility
- Tested on Arduino Uno R4 Wifi with 1x [PCPU-NANO1](https://github.com/Pepe-57/pcpu-nano1)
## Terminal commands:
- help, displays all commands
- ram, displays RAM, usage: ram [start address] [end address]
- diec, Direct Instruction Execution on Core, usage: diec [in, data, Instruction]
- sysinfo, displays system information
- setpin, sets pin value, usage: setpin <pin(1 or 2), value, 0 LOW or 1 HIGH>
- getpin, gets pin value, usage: getpin <pin(3 or 4)>
- calculator, simple calculator

## Installation steps(new)
1. Download Nano-OS from [releases](https://github.com/Pepe-57/nano-os/releases/)
2. Extract the archive to your desired location
3. Open `NanoOS.ino`
4. Select your microcontroller and upload the sketch
5. Open the serial monitor and set the baud rate to 115200
6. Press reset on the microcontroller
7. Now it is ready to use

## Installation steps(old)
1. Download and install Arduino IDE
2. Download [Nano-os]([https://github.com/Pepe-57/nano-os](https://github.com/Pepe-57/nano-os/releases/tag/1.1.0))
3. Extract the archive to /Documents/Arduino/libraries
4. Open Arduino IDE and click File -> Examples -> NanoOS -> nano_os
5. Select your microcontroller and upload the sketch
6. Open the serial monitor and set the baud rate to the same as 'Serial.begin()'
7. Press reset on the microcontroller and clear the serial monitor
8. Now it is ready to use

## Versions
### Firmware
- Release 1.0.0
- Release 1.1.0 
- Release 1.2.0 (Latest, Recommended)
### OS
- Release 1.0.0
- Release 1.1.0 (Latest, Recommended)
