#include "firmware.h"
#include "kernel.h"
#include "nano_os.h"
#include <Arduino.h>

int io_pin1 = 2; //output
int io_pin2 = 3; //output
int io_pin3 = 4; //input
int io_pin4 = 5; //input

void io_driver::init_io_driver() {
    pinMode(io_pin1, OUTPUT);
    pinMode(io_pin2, OUTPUT);
    pinMode(io_pin3, INPUT);
    pinMode(io_pin4, INPUT);    
}

void io_driver::set_pin(int pin, int value) {
    if (pin == 1) {
        digitalWrite(io_pin1, value);
    } else if (pin == 2) {
        digitalWrite(io_pin2, value);
    } else {
        Serial.println("Invalid pin");
    }    
}

int io_driver::get_pin(int pin) {
    switch (pin)
    {
    case 3:
        t1.sto(0, digitalRead(io_pin3));
        return digitalRead(io_pin3);
        break;
    case 4:
        t1.sto(1, digitalRead(io_pin4));
        return digitalRead(io_pin4);
        break;
    default:
        Serial.println("Invalid pin");
        break;
    }
}

int kernel_functions::get_ram_contents(int from, int to) {
    int buff;
    for (int i = from; i <= to; i++) {
        buff = ram[i];
        Serial.print(" Addr: ");
        Serial.print(i);
        Serial.print(" data: ");
        Serial.print(buff);
    }
}

void kernel_functions::init_operating_system() {
    io_dv.init_io_driver();
    OperatingSystem.terminal();
}

int kernel_functions::direct_code_execution(int instruction) {
    return t1.diec(instruction);
}

void kernel_functions::system_info() {
    Serial.println("--System Info--");
    Serial.print("Firmware version: ");
    Serial.println(FIRMWARE_VERSION);
    Serial.print("Kernel version: ");
    Serial.println(KERNEL_VERSION);
    Serial.print("OS version: ");
    Serial.println(OS_VERSION);
    Serial.print("Core count: ");
    Serial.println(fw.get_cpu_count());
    Serial.print("Ram size: ");
    Serial.println(fw.get_ram_size());
}

void kernel_functions::set_pins(int pin, int value) {
    Serial.print("Setting pin ");
    Serial.print(pin);
    Serial.print(" to ");
    Serial.println(value);
    io_dv.set_pin(pin, value);
}

int kernel_functions::get_pins(int pin) {
    Serial.print("Pin");
    Serial.print(pin);
    Serial.print(" value: ");
    return io_dv.get_pin(pin);
}

io_driver io_dv;
kernel_functions kernel;
