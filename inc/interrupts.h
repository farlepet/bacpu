#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

#include <cpu.h>

//! Struct defining IRQ controller state
struct irq_con
{
    uint8_t irq;      //! Whether an IRQ is being fired
    uint8_t in;       //! Input of the current IRQ line
    uint8_t selector; //! Select which IRQ line to check
};

//! Format of an interrupt vector
struct int_vec
{
    uint32_t l_ptr;    //! Linear pointer
    uint32_t p_region; //! Planar region
    uint16_t p_offset; //! Planar offset
};

/**
 * Initialize interrupt controller
 *
 * @param bacpu pointer to CPU structure
 *
 * @return 0 if successful, else 1
 */
int init_interrupts(struct cpu *bacpu);

/**
 * Emulate one cycle of the IRQ controller.
 *
 * @param bacpu pointer to CPU structure
 *
 * @return 0 if successful, else 1
 */
int emulate_irq(struct cpu *bacpu);

#endif // INTERRUPTS
