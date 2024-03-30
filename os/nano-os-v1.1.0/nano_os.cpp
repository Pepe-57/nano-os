#include "firmware.h"
#include "kernel.h"
#include "nano_os.h"
#include <Arduino.h>

#define helpMessage "Commands: help, ram <start address> <end address>, diec <in, data, instruction>, sysinfo, setpin <pin(1 or 2), value, 0 LOW or 1 HIGH>, getpin <pin(3 or 4)>, calculator"
#define CALC_OPS "Available operations: add, sub, help, quit"

void operating_system::calculator() {
    Serial.println("--Calculator--");
    Serial.println("Operations: help, quit, add, sub");
    while (true) {
        Serial.println("--------");
        while (!Serial.available());
        String op = Serial.readStringUntil('\n');
        Serial.println(op);
        String operand1, operand2;
        int spaceIndex = op.indexOf(' ');
        if (spaceIndex != -1) {
            operand1 = op.substring(spaceIndex + 1);
            spaceIndex = operand1.indexOf(' ');
            if (spaceIndex != -1) {
                operand2 = operand1.substring(spaceIndex + 1);
                operand1 = operand1.substring(0, spaceIndex);
            }
        }

        if (op.startsWith("help") || op.startsWith("Help")) {
            Serial.println(CALC_OPS);
            Serial.println("Operation format: <operation> <operand1> <operand2>, example: add 2 3");
        } else if (op.startsWith("quit") || op.startsWith("Quit")) {
            Serial.println("--Terminal--");
            break;
        } else if (op.startsWith("add") || op.startsWith("Add")) {
            Serial.println(nm.add16(operand1.toInt(), operand2.toInt()));  
        } else if (op.startsWith("sub") || op.startsWith("Sub")) {
            Serial.println(nm.sub16(operand1.toInt(), operand2.toInt()));
        }
        else {Serial.println("Invalid operation");} 
    }
}
void operating_system::terminal() {
    Serial.println("--Terminal--");
    while (true) {
        Serial.print("> ");
        while (!Serial.available());
        String command = Serial.readStringUntil('\n');
        Serial.println(command);

        String parameter1, parameter2;
        int spaceIndex = command.indexOf(' ');
        if (spaceIndex != -1) {
            parameter1 = command.substring(spaceIndex + 1);
            spaceIndex = parameter1.indexOf(' ');
            if (spaceIndex != -1) {
                parameter2 = parameter1.substring(spaceIndex + 1);
                parameter1 = parameter1.substring(0, spaceIndex);
            }
        }

        if (command.startsWith("help") || command.startsWith("Help")) {
            Serial.println(helpMessage);
        } else if (command.startsWith("ram") || command.startsWith("RAM")) {
            kernel.get_ram_contents(parameter1.toInt(), parameter2.toInt());
        } else if (command.startsWith("diec") || command.startsWith("DIEC")) {
            Serial.println(kernel.direct_code_execution(parameter1.toInt()));
        } else if (command.startsWith("sysinfo") || command.startsWith("Sysinfo")) {
            kernel.system_info();
        } else if (command.startsWith("setpin") || command.startsWith("Setpin")) {
            kernel.set_pins(parameter1.toInt(), parameter2.toInt());
        } else if (command.startsWith("getpin") || command.startsWith("Getpin")) {
            Serial.println(kernel.get_pins(parameter1.toInt()));
        } else if (command.startsWith("calculator") || command.startsWith("Calculator") || command.startsWith("calc")) {
            calculator();
        } else if (command.startsWith("\n") || command.startsWith(" ") || command.length() == 0) {
            continue;
        } else {
            Serial.println("Unknown command, type 'help' for available commands");
        }
    }
}


operating_system OperatingSystem;
