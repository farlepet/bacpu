#include <stdio.h>
#include <string.h>

#include <cpu.h>

int init_peripherals(struct cpu *bacpu)
{
    // If this is true, something bad has happened
    if(bacpu == NULL) { FATAL("init_peripherals: bacpu == NULL\n"); return 1; }

    INFO("Initializing BACPU peripheral controller\n");

    memset(bacpu->p_devs, 0, sizeof(bacpu->p_devs));

    bacpu->p_con.selector = 0;
    bacpu->p_con.request  = 0;
    bacpu->p_con.data     = 0;

    return 0;
}
