#ifndef KERNEL_H
#define KERNEL_H

class kernel {
public:
    int get_ram_contents(int from, int to);
    int init_operating_system();
    int direct_code_execution(int instruction);
    int system_info();
};


extern kernel kern;
#endif