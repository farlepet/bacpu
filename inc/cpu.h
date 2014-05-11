#ifndef CPU_H
#define CPU_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

struct cpu; // Required so that the files below can be included

// Macros to make messages and error reporting easier:
#define FATAL(...) printf("\e31FATAL: \e0"__VA_ARGS__)
#define INFO(...) printf("INFO: "__VA_ARGS__)

// Definitions to make data definitions easier
#define __packed __attribute__((__packed__))

// BACPU includes
#include <instruction_format.h>
#include <peripherals.h>
#include <interrupts.h>
#include <registers.h>
#include <memory.h>
#include <alu.h>



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
