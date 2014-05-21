#include <inst/int.h>

int execute_int(struct cpu *bacpu)
{
    if(bacpu == NULL) { FATAL("execute_int: bacpu == NULL\n"); return 1; }

    return 0;
}
