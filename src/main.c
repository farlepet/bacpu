#include <stdlib.h> // rand: for tests
#include <time.h>   // time: for random seed generation

#include <instructions.h>
#include <cpu.h>

size_t   memsize    = 1024 * 16; // 16 KB
uint32_t entrypoint = 4096;

// A test program
static uint8_t prgm[] =
{
//  Opcode  Info
    0x00,   0x00,                                   // 1000: NOP
    0x00,   0x00,                                   // 1002: NOP
    0xFF,   0x02,   0x0C,   0x10,   0x00,   0x00,   // 1004: EFN PRINT 0x100C
    0xFF,   0x01,                                   // 100A: EFN QUIT
    'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o',
    'r', 'l', 'd', '!', '\0'                        // 100C: STRING
};

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

    // Testing:
    srand(time(NULL)); // Generate a random number so tests aren't biased

    test_alu(&bacpu, rand()%256, rand()%256); // Test the ALU

    //test_mem(&bacpu); // Test the MMU
    
    INFO("----------------------------------\n");

    // Emulate the cpu TODO: Put in separate thread
    memcpy(bacpu.mm.memory + 4096, prgm, sizeof(prgm)); // Copy test program
    
    bacpu.in.enable = 1; // Enable CPU
    bacpu.in.reset  = 0; // Make sure reset line is low
    while(!emulate_cpu(&bacpu)); // TODO: Error handling
                                 // TODO: Separate thread

    INFO("----------------------------------\n");
    
    if(deinit_memory(&bacpu)) return 1;

    return 0;
}
