#ifndef CPU_H
#define CPU_H

#include <stdint.h>

struct cpu; // Required so that the files below can be included

// BACPU includes
#include <peripherals.h>
#include <registers.h>
#include <memory.h>
#include <alu.h>

// Macros to make messages and error reporting easier:
#define FATAL(...) printf("\e31FATAL: \e0"__VA_ARGS__)
#define INFO(...) printf("INFO: "__VA_ARGS__)

// BACPU
struct cpu
{
    struct registers regs;              // The BACPU's registers

    struct memory    mem;               // The BACPU's internal memory controller
    struct mmu       mm;                // External Memory Management Unit

    struct peripheral_con p_con;        // Peripheral Controller
    struct peripheral_dev *p_devs[256]; // Peripheral Devices

    struct alu alu;                     // Arithmetic Logic Unit
};

#endif // CPU_H
