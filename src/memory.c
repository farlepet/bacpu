#include <stdlib.h>
#include <stdio.h>

#include <cpu.h>

int init_memory(struct cpu *bacpu, size_t length)
{
    if(bacpu == NULL) { FATAL("init_memory: bacpu == NULL\n"); return 1; }

    bacpu->mem.address = 0;
    bacpu->mem.cache   = 0;

    bacpu->mm.address = 0;
    bacpu->mm.data    = 0;
    bacpu->mm.info    = 0;
    bacpu->mm.size    = length;

    if((bacpu->mm.memory = malloc(length)) == NULL)
    {
        FATAL("init_memory: Could not allocate memory for BACPU!\n");
        return 1;
    }

    return 0;
}
