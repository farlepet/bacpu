#include <inst/nop.h>

int execute_nop(struct cpu *bacpu)
{
    if(bacpu == NULL) { FATAL("execute_nop: bacpu == NULL\n"); return 1; }

    bacpu->regs.pc += 2;

    return 0;
}
