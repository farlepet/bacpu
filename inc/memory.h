#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MMU_INFO_ENABLE   1
#define MMU_INFO_WRITE    2
#define MMU_INFO_SIZE     (4 | 8)
#define MMU_INFO_EXIST    16
#define MMU_INFO_COMPLETE 32

// Memory Unit within CPU
struct memory
{
    uint32_t address; // Address of memory
    uint32_t cache;   // CPU internal cache for dealing with memory access
};

// Memory Management Unit (MMU)
struct mmu
{
    uint32_t address; // Address lines
    uint32_t data;    // Data lines
    uint8_t  info;    // Info lines

    // Only used internally by emulator:
    uint32_t size;    // Size of memory
    uint32_t *memory; // Pointer to memory
};

// Initialize CPU memory controllers and allocate memory
int init_memory(struct cpu *bacpu, size_t length);

// Deallocate allocated memory
int deinit_memory(struct cpu *bacpu);

#endif
