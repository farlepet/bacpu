#include <inst/int.h>

int execute_int(struct cpu *bacpu)
{
    if(bacpu == NULL) { FATAL("execute_int: bacpu == NULL\n"); return 1; }

    uint8_t inst_fmt;
    if(memory_read(bacpu, MMU_SIZE_BYTE, bacpu->regs.pc + 1, &inst_fmt)) return 1; // TODO

    if(inst_fmt & 0x01) // SRC bit
    { // Immediate
        uint32_t idx;
        if(memory_read(bacpu, MMU_SIZE_DWORD, bacpu->regs.pc + 2, &idx)) return 1; // TODO
        bacpu->regs.pc += 6;
        if(idx >= 512)
        {
            INFO("Interrupt out of range\n");
            return 1; // TODO: Call exception
        }
        call_interrupt(bacpu, idx);
    }
    else
    { // Register
        // TODO
        bacpu->regs.pc += 4;
    }

    return 0;
}
