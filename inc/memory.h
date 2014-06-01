#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MMU_INFO_ENABLE   1        //!< MMU enable
#define MMU_INFO_WRITE    2        //!< MMU read(0)/write(1)
#define MMU_INFO_SIZE     (4 | 8)  //!< MMU memory access size
#define MMU_INFO_EXIST    16       //!< MMU memory exists
#define MMU_INFO_COMPLETE 32       //!< MMU operation complete

#define MMU_SIZE_BYTE     (0 << 2) //!< MMU memory size == byte
#define MMU_SIZE_WORD     (1 << 2) //!< MMU memory size == word
#define MMU_SIZE_DWORD    (2 << 2) //!< MMU memory size == dword

//! Struct defining the CPU's internal memory controller state
struct memory
{
    uint32_t address; //!< Address of memory
    uint32_t cache;   //!< CPU internal cache for dealing with memory access
};

//! Struct defining the MMU's state
struct mmu
{
    uint32_t address; //!< Address lines
    uint32_t data;    //!< Data lines
    uint8_t  info;    //!< Info lines

    // Only used internally by emulator:
    uint32_t size;    //!< Size of memory
    uint32_t *memory; //!< Pointer to memory
};

/**
 * Initialize CPU memory controllers and allocate memory for the CPU.
 * 
 * @param bacpu  pointer to CPU structure
 * @param length amount of memory to allocate
 * 
 * @return 0 if successful,  else 1
 */
int init_memory(struct cpu *bacpu, size_t length);

int emulate_mem(struct mmu *mm);

/**
 * De-initialize memory controller and free allocated memory.
 *
 * @param bacpu pointer to CPU structure
 *
 * @return 0 if successful, else 1
 */
int deinit_memory(struct cpu *bacpu);

/**
 * Simulate a memory read.
 *
 * @param      bacpu     pointer to CPU structure
 * @param      data_size size of data read
 * @param      addr      address of data to be read
 * @param[out] data      pointer where the read data is to be stored
 *
 * @return 0 if successful, else 1
 */
int memory_read(struct cpu *bacpu, uint8_t data_size, uint32_t addr, void *data);

/**
 * Simulate a memory write.
 *
 * @param bacpu     pointer to CPU structure
 * @param data_size size of data to be written
 * @param addr      address of data to be written to
 * @param data      data to be written
 *
 * @return 0 if successful, else 1
 */
int memory_write(struct cpu *bacpu, uint8_t data_size, uint32_t addr, uint32_t data);

/**
 * Push an item onto the stack
 *
 * @param bacpu pointer to CPU structure
 * @param data  value to be pushed
 *
 * @return 0 if successful, else 1
 */
int stack_push(struct cpu *bacpu, uint32_t data);

/**
 * Pop an item from the stack
 *
 * @param      bacpu pointer to CPU structure
 * @param[out] data  pointer to where to store popped value.
 *
 * @return 0 if successful, else 1
 */
int stack_pop(struct cpu *bacpu, uint32_t *data);

#endif
