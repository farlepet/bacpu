#include <stdio.h>

#include <cpu.h>

size_t memsize      = 1024 * 16; // 16 KB
uint32_t entrypoint = 4096;

int main(int argc, char **argv)
{
	(void)argc;
    (void)argv;

    INFO("BACPU emulator -- (c) 2014 Peter Farley\n");

    struct cpu bacpu;

    if(init_memory(&bacpu, memsize)) return 1;
    if(init_registers(&bacpu, entrypoint)) return 1;
    if(init_peripherals(&bacpu)) return 1;
    if(init_alu(&bacpu)) return 1;
    if(init_interrupts(&bacpu)) return 1;

    INFO("----------------------------------\n");

    // Emulate CPU here...
    test_alu(0xFE, 0x01);
    
    INFO("----------------------------------\n");

    if(deinit_memory(&bacpu)) return 1;

    return 0;
}
