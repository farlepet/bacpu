#include <stdlib.h> // rand: for tests
#include <time.h>   // time: for random seed generation

#include <instructions.h>
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
    
    // Testing:
    srand(time(NULL)); // Generate a random number so tests aren't biased
    test_alu(rand()%256, rand()%256); // Test the ALU
    
    INFO("----------------------------------\n");

    if(deinit_memory(&bacpu)) return 1;

    return 0;
}
