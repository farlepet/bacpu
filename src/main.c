#include <stdio.h>

#include <cpu.h>

int main(int argc, char **argv)
{
	(void)argc;
    (void)argv;

    INFO("BACPU emulator -- (c) 2014 Peter Farley\n");

    size_t memsz = 4096*4; // Temporary
    uint32_t entryp = 4096;

    struct cpu bacpu;

    if(init_memory(&bacpu, memsz)) return 1;

    if(init_registers(&bacpu, entryp)) return 1;

    if(init_peripherals(&bacpu)) return 1;

    INFO("----------------------------------\n");

    // Emulate CPU here...
    
    INFO("----------------------------------\n");

    if(deinit_memory(&bacpu)) return 1;

    return 0;
}
