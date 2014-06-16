#include <cpu.h>

pthread_t irq_thread;

static void *irq_task(void *);

int init_interrupts(struct cpu *bacpu)
{
    // This should never be true
    if(bacpu == NULL) { FATAL("init_interrupts: bacpu == NULL\n"); return 1; }

    INFO("Initializing interrupt controllers\n");

    pthread_create(&irq_thread, NULL, irq_task, bacpu);

    return 0;
}

static inline bool get_irq_line(struct cpu *bacpu, uint8_t n)
{
    if(bacpu == NULL) { FATAL("get_irq_line: bacpu == NULL\n"); return false; }

    if(bacpu->p_devs[n])
        if(bacpu->p_devs[n]->irq)
            return true;

    return false;
}

int call_interrupt(struct cpu *bacpu, uint16_t n)
{
    if(bacpu == NULL) { FATAL("call_interrupt: bacpu == NULL\n"); return 1; }

    if(n > 512) return 1; // TODO

    uint32_t addr = n << 2;
    uint32_t ptr;

    // Get value of the interrupt vector
    if(memory_read(bacpu, MMU_SIZE_DWORD, addr, &ptr)) return 1; // TODO: more reliable error reporting

    // Push the current value of PC so we can return there after the interrupt
    if(stack_push(bacpu, bacpu->regs.pc)) return 1; // TODO: more reliable error reporting

    // TODO: Check memory mode
    bacpu->regs.pc = ptr;


    return 0;
}

static void *irq_task(void *bacpu)
{
    while(1) // TODO: Add more conditions for stopping
    {
        if(emulate_irq((struct cpu *)bacpu))
        {
            FATAL("irq_task: emulate_irq failed\n");
            return NULL; // TODO: Exit entire program
        }
        sched_yield();
    }
}

int emulate_irq(struct cpu *bacpu)
{
    if(bacpu == NULL) { FATAL("emulate_irq: bacpu == NULL\n"); return 1; }

    for(int i = 0; i < 256; i++)
    {
        // Check each MUX input:
        if(get_irq_line(bacpu, (uint8_t)i))
        {
            INFO("IRQ from peripheral %d\n", i);
            call_interrupt(bacpu, i);
        }
    }

    return 0;
}
