#include <instructions.h>

int (*instructions[N_INSTRUCTIONS])(struct cpu *) =
{
    execute_nop,
    execute_int,
};
