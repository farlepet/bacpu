#include <cpu.h>

int init_interrupts(struct cpu *bacpu)
{
    // This should never be true
    if(bacpu == NULL) { FATAL("init_interrupts: bacpu == NULL\n"); return 1; }

    INFO("Initializing interrupt controllers\n");

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

int emulate_irq(struct cpu *bacpu)
{
    if(bacpu == NULL) { FATAL("emulate_irq: bacpu == NULL\n"); return 1; }

    for(int i = 0; i < 256; i++)
    {
        if(get_irq_line(bacpu, (uint8_t)i))
        {
            INFO("IRQ from peripheral %d\n", i);
            // Do Something
        }
    }

    return 0;
}
