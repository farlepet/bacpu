#include <stdlib.h>
#include <stdio.h>

#include <cpu.h>

pthread_t mem_thread;

static void *mem_task(void *);

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

    pthread_create(&mem_thread, NULL, mem_task, &bacpu->mm);

    return 0;
}

static void *mem_task(void *bacpu)
{
    while(1)
    {
        if(emulate_mem(&((struct cpu *)bacpu)->mm))
        {
            FATAL("mem_task: emulate_mem: An error occured\n");
            return NULL; // TODO
        }
    }
}

int emulate_mem(struct mmu *mm)
{
    if(mm == NULL) { FATAL("emulate_mem: mm == NULL\n"); return 1; }
    
    if(!(mm->info & MMU_INFO_ENABLE)) return 0; // Don't do anything yet

    if((mm->address + ((1 << (((mm->info & MMU_INFO_SIZE) >> 2) - 1)) - 1)) > mm->size)
    { // Not actually an error
        INFO("emulate_mem: memory access to non-existent area\n");
        mm->info |= MMU_INFO_COMPLETE;
        mm->info &= ~MMU_INFO_EXIST;
    }
    else mm->info |= MMU_INFO_EXIST;

    if(mm->info & MMU_INFO_WRITE)
    { // Memory write
        switch(mm->info & MMU_INFO_SIZE)
        {
            case MMU_SIZE_BYTE:
                ((uint8_t *)mm->memory)[mm->address] = (uint8_t)mm->data;
                break;

            case MMU_SIZE_WORD:
                ((uint16_t *)mm->memory)[mm->address] = (uint16_t)mm->data;
                break;

            case MMU_SIZE_DWORD:
                ((uint32_t *)mm->memory)[mm->address] = (uint32_t)mm->data;
                break;

            default:
                FATAL("emulate_mem: Unhandled MMU_SIZE\n");
                return 1;
        }
        mm->info |= MMU_INFO_COMPLETE;
    }
    else
    { // Memory read
        switch(mm->info & MMU_INFO_SIZE)
        {
            case MMU_SIZE_BYTE:
                mm->data = ((uint8_t *)mm->memory)[mm->address];
                break;

            case MMU_SIZE_WORD:
                mm->data = ((uint16_t *)mm->memory)[mm->address];
                break;

            case MMU_SIZE_DWORD:
                mm->data = ((uint32_t *)mm->memory)[mm->address];
                break;

            default:
                FATAL("emulate_mem: Unhandled MMU_SIZE\n");
                return 1;
        }
        mm->info |= MMU_INFO_COMPLETE;
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



int memory_read(struct cpu *bacpu, uint8_t data_size, uint32_t addr, void *data)
{
    if(bacpu == NULL) { FATAL("memory_write: bacpu == NULL\n"); return 1; }

    bacpu->mem.address = addr;
    bacpu->mm.address  = addr;
    bacpu->mm.info     = data_size | MMU_INFO_ENABLE;

    while(!(bacpu->mm.info & MMU_INFO_COMPLETE)); // NOTE: Make sure to make MMU a seperate thread

    if(!(bacpu->mm.info & MMU_INFO_EXIST))
    {
        return 1;
    }

    switch(data_size)
    {
        case MMU_SIZE_BYTE:     *(uint8_t *)data = (uint8_t)bacpu->mm.data;
                                break;
        case MMU_SIZE_WORD:     *(uint16_t *)data = (uint16_t)bacpu->mm.data;
                                break;
        case MMU_SIZE_DWORD:    *(uint32_t *)data = (uint32_t)bacpu->mm.data;
                                break;
        default:                return 1; // TODO
    }
    bacpu->mm.info = 0;

    return 0;
}

int memory_write(struct cpu *bacpu, uint8_t data_size, uint32_t addr, uint32_t data)
{
   if(bacpu == NULL) { FATAL("memory_write: bacpu == NULL\n"); return 1; }

    bacpu->mem.address = addr;
    bacpu->mm.address  = addr;
    bacpu->mm.info     = data_size | MMU_INFO_ENABLE | MMU_INFO_WRITE;
    bacpu->mm.data     = data;

    while(!(bacpu->mm.info & MMU_INFO_COMPLETE)); // NOTE: Make sure to make MMU a seperate thread

    if(!(bacpu->mm.info & MMU_INFO_EXIST))
    {
        return 1;
    }

    bacpu->mm.info = 0;

    return 0;
}

int memory_exists(struct cpu *bacpu, uint32_t addr)
{
    if(bacpu == NULL) { FATAL("memory_exists: bacpu == NULL\n"); exit(1); }

    bacpu->mem.address = addr;
    bacpu->mm.address  = addr;
    bacpu->mm.info     = MMU_SIZE_BYTE | MMU_INFO_ENABLE;

    while(!(bacpu->mm.info & MMU_INFO_COMPLETE));

    return ((bacpu->mm.info & MMU_INFO_EXIST) == MMU_INFO_EXIST);
}

int stack_push(struct cpu *bacpu, uint32_t data)
{
    if(bacpu == NULL) { FATAL("stack_push: bacpu == NULL\n"); return 1; }

    if(memory_write(bacpu, MMU_SIZE_DWORD, bacpu->regs.sp & (~0x03), data)) return 1; // TODO: Call exception (Stack Overflow???)

    bacpu->regs.sp += 4; // NOTE: Should I emulate the ALU here? Or just keep with using a single C statement?

    return 0;
}

int stack_pop(struct cpu *bacpu, uint32_t *data)
{
    if(bacpu == NULL) { FATAL("stack_pop: bacpu == NULL\n"); return 1; }

    if(bacpu->regs.sp == 0) return 0; // TODO: Cause exception (Stack underflow???)

    if(memory_read(bacpu, MMU_SIZE_DWORD, bacpu->regs.sp & (~0x03), data)) return 1;

    bacpu->regs.sp -= 4;

    return 0;
}
