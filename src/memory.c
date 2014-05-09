#include <stdlib.h>
#include <stdio.h>

#include <cpu.h>

int init_memory(struct cpu *bacpu, size_t length)
{
    // If this is true, something bad happened
    if(bacpu == NULL) { FATAL("init_memory: bacpu == NULL\n"); return 1; }

    INFO("Initializing BACPU Memory (%dKB)\n", ((int)length / 1024));

    bacpu->mem.address = 0;
    bacpu->mem.cache   = 0;

    bacpu->mm.address = 0;
    bacpu->mm.data    = 0;
    bacpu->mm.info    = 0;
    bacpu->mm.size    = length;

    // Allocate BACPU memory and verify it
    if((bacpu->mm.memory = malloc(length)) == NULL)
    {
        FATAL("init_memory: Could not allocate memory for BACPU!\n");
        return 1;
    }

    return 0;
}

int deinit_memory(struct cpu *bacpu)
{
    if(bacpu == NULL) { FATAL("deinit_memory: bacpu == NULL\n"); return 1; }

    INFO("Uninitializing BACPU Memory\n");

    // Free allocated memory
    free(bacpu->mm.memory);

    return 0;
}
