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

/**
 * Emulate a call of an interrupt or exception
 *
 * @param bacpu pointer to CPU structure
 * @param n     interrupt or exception number to call
 *
 * @returns 0 if successful, else 1
 */
int call_interrupt(struct cpu *bacpu, uint16_t n);
#endif // INTERRUPTS
