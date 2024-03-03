#ifndef NANO_OS_H
#define NANO_OS_H

#include <kernel.h>
class operating_system {
public:
    int shell();
};

extern operating_system OperatingSystem;
#endif