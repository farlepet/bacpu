#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

#define FLAG_CARRY 1 // Carry Flag
#define FLAG_MMODE 2 // Memory Mode
#define FLAG_TRUE  4 // True Flag (Used by CMP and JOC)

// BACPU registers
struct registers
{
    uint32_t r0, r1, r2,  r3,  r4,  r5,  r6,  r7;  // General-Purpose
    uint32_t r8, r9, r10, r11, r12, r13, r14, r15; //   Registers
    uint32_t pc;                                   // Program Counter
    uint32_t flgs;                                 // Flags
    uint32_t dr, cr, sr;                           // Region Registers
    uint32_t sp;                                   // Stack Pointer
};

// Set all registers to their defaults and sets PC to entrypoint
int init_registers(struct cpu *bacpu, uint32_t entrypoint);

#endif // REGISTERS_H
