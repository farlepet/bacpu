#ifndef CPU_H
#define CPU_H

#include <stdint.h>


struct cpu;
// BACPU includes
#include <registers.h>
#include <memory.h>


#define FATAL(str) printf("\e31FATAL: \e0"str)


struct cpu
{
    struct registers regs; // The BACPU's registers

    struct memory    mem;  // The BACPU's internal memory controller
    struct mmu       mm;   // External Memory Management Unit
};

#endif // CPU_H
