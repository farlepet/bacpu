#ifndef CPU_H
#define CPU_H

#include <semaphore.h>
#include <stdbool.h>   // booleans
#include <pthread.h>   // multi-threading
#include <string.h>    // Memory operations
#include <stdint.h>    // various integer definitions
#include <stddef.h>
#include <sched.h>
#include <stdio.h>     // printf: from INFO and FATAL
#include <time.h>

struct cpu; // Required so that the files below can be included

// Macros to make messages and error reporting easier:
#define FATAL(...) ({ printf("\e[31mFATAL: \e[0m"__VA_ARGS__); fflush(stdout); })
#define INFO(...)  ({ printf("\e[32mINFO: \e[0m"__VA_ARGS__);  fflush(stdout); })

// Definitions to make data definitions easier
#define __packed __attribute__((__packed__))

#define ndelay(nsec) ({ struct timespec ts = { 0, nsec }; while(nanosleep(&ts, &ts) == -1); })

// BACPU includes
#include <instructions.h>
#include <peripherals.h>
#include <interrupts.h>
#include <registers.h>
#include <memory.h>
#include <alu.h>


// NOTE: I might move this:
struct inputs
{
    uint8_t reset;  // Reset pin (0 == normal, 1 == reset)
    uint8_t enable; // Enable pin (0 == off, 1 == on)
};

// BACPU
struct cpu
{
    struct registers regs;              // The BACPU's registers

    struct memory    mem;               // The BACPU's internal memory controller
    struct mmu       mm;                // External Memory Management Unit

    struct peripheral_con p_con;        // Peripheral Controller
    struct peripheral_dev *p_devs[256]; // Peripheral Devices

    struct alu alu;                     // Arithmetic Logic Unit

    struct inputs    in;                // Input pins on BACPU
};

int emulate_cpu(struct cpu *bacpu);

#endif // CPU_H
