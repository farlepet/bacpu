#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <instruction_format.h>

#include <inst/nop.h>
#include <inst/int.h>

#define N_INSTRUCTIONS 15

#define INSTRUCTION_NOP 0
#define INSTRUCTION_INT 1

int (*instructions[N_INSTRUCTIONS])(struct cpu *); //!< List of pointers to 
                                                   //!< instruction functions

#endif // INSTRUCTIONS_H
