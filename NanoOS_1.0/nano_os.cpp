#include <kernel.h>
#include <nano_os.h>
#include <Arduino.h>

#define helpMessage "Commands: help, ram [start address] [end address], diec [in, data, instruction], sysinfo"
int operating_system::shell() {
    while (true) {
        while (!Serial.available());
        String command = Serial.readStringUntil('\n');
        Serial.print("Command typed: ");
        Serial.println(command);

        String argument1, argument2;
        int spaceIndex = command.indexOf(' ');
        if (spaceIndex != -1) {
            argument1 = command.substring(spaceIndex + 1);
            spaceIndex = argument1.indexOf(' ');
            if (spaceIndex != -1) {
                argument2 = argument1.substring(spaceIndex + 1);
                argument1 = argument1.substring(0, spaceIndex);
            }
        }

        if (command == "help" || command == "Help") {
            Serial.println(helpMessage);
        } else if (command.startsWith("ram") || command.startsWith("RAM")) {
            int sAddr = argument1.toInt();
            int eAddr = argument2.toInt();
            kern.get_ram_contents(sAddr, eAddr);
        } else if (command.startsWith("diec") || command.startsWith("DIEC")) {
            int instruction = argument1.toInt();
            Serial.println(kern.direct_code_execution(instruction));
        } else if (command == "sysinfo" || command == "Sysinfo") {
            kern.system_info();
        }
        else {
            Serial.println("Command not found");
        }
    }
}


operating_system OperatingSystem;
