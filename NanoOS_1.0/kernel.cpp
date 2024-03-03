#include <firmware.h>
#include <kernel.h>
#include <nano_os.h>
#include <Arduino.h>

int kernel::get_ram_contents(int from, int to) {
    int buff;
    for (int i = from; i <= to; i++) {
        buff = ram[i];
        Serial.print(" addr: ");
        Serial.print(i);
        Serial.print(" data: ");
        Serial.print(buff);
    }
}

int kernel::init_operating_system() {
    OperatingSystem.shell();
}

int kernel::direct_code_execution(int instruction) {
    return t1.diec(instruction);
}

int kernel::system_info() {
    Serial.println("--System Info--");
    Serial.print("Core count: ");
    Serial.println(fw.get_cpu_count());
    Serial.print("Ram size: ");
    Serial.println(fw.get_ram_size());
    Serial.println("Register values:");
    fw.get_registers();
}

kernel kern;