#ifndef ALU_H
#define ALU_H

#include <stdint.h>

#include <cpu.h>

// ALU output flags
#define ALU_FLAG_ZERO    1
#define ALU_FLAG_CARRY   2

// ALU modifiers
#define ALU_OP_INVA      1
#define ALU_OP_INVB      2
#define ALU_OP_INVOUT    4
#define ALU_OP_OPERATION (8 | 16)

// ALU functions
#define ALU_OPER_AND     (0 << 3)
#define ALU_OPER_OR      (1 << 3)
#define ALU_OPER_XOR     (2 << 3)
#define ALU_OPER_ADD     (3 << 3)

// ALU operations
#define ALU_AND          ALU_OPER_AND
#define ALU_NAND         ALU_OPER_AND | ALU_OP_INVOUT
#define ALU_OR           ALU_OPER_OR
#define ALU_NOR          ALU_OPER_OR  | ALU_OP_INVOUT
#define ALU_XOR          ALU_OPER_XOR
#define ALU_XNOR         ALU_OPER_XOR | ALU_OP_INVOUT
#define ALU_ADD          ALU_OPER_ADD
#define ALU_SUB          ALU_OPER_ADD | ALU_OP_INVB

struct alu
{
    uint32_t a;      // Input A
    uint32_t b;      // Input B
    uint8_t  op;     // Operation
    uint32_t result; // Result or operation
    uint8_t  flags;  // Output flags
};

// Initialize the ALU
int init_alu(struct cpu *bacpu);

// Emulate the ALU
int emulate_alu(struct alu *alu);

// Test the emulated ALU
int test_alu(uint32_t a, uint32_t b);

#endif // ALU_H
