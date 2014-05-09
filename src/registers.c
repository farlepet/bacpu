#include <stdio.h>

#include <cpu.h>

int init_registers(struct cpu *bacpu, uint32_t entrypoint)
{
    // If either of these are true, something terrible happened
    if(bacpu == NULL) { FATAL("init_registers: bacpu == NULL\n"); return 1; }
    if(entrypoint < 4096) { FATAL("init_registers: invalid entrypoint!\n"); return 1; }

    INFO("Initializing BACPU Registers\n");

    // General-Purpose registers start uninitialized

    bacpu->regs.pc   = entrypoint;
    bacpu->regs.flgs = 0;
    bacpu->regs.dr   = bacpu->regs.cr = bacpu->regs.sr = 0;
    bacpu->regs.sp   = 0;

    return 0;
}
