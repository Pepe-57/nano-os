#ifndef KERNEL_H
#define KERNEL_H

#define KERNEL_VERSION "1.1.0"

class kernel_functions {
public:
    int get_ram_contents(int from, int to);
    void init_operating_system();
    int direct_code_execution(int instruction);
    void system_info();
    void set_pins(int pin, int value);
    int get_pins(int pin);
};

class io_driver {
public:
    void init_io_driver();
    void set_pin(int pin, int value);
    int get_pin(int pin);
};

extern int io_pin1;
extern int io_pin2;
extern int io_pin3;
extern int io_pin4;
extern io_driver io_dv;
extern kernel_functions kernel;
#endif
