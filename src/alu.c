#include <stdio.h>

#include <arithmetic.h>
#include <cpu.h>

int init_alu(struct cpu *bacpu)
{
    // If this is true, somehting went wrong internally
    if(bacpu == NULL) { FATAL("init_alu: bacpu == NULL\n"); return 1; }
    
    INFO("Initializing ALU\n");

    bacpu->alu.a      = 0;
    bacpu->alu.b      = 0;
    bacpu->alu.op     = 0;
    bacpu->alu.result = 0;
    bacpu->alu.flags  = 0;

    return 0;
}

int emulate_alu(struct alu *alu)
{
    if(alu == NULL) { FATAL("emulate_alu: alu == NULL\n"); return 1; }

    // Results of the 4 operations
    static uint32_t results[4];

    // Invert inputs if necessary
    uint32_t A = ((alu->op & ALU_OP_INVA) ? ~alu->a : alu->a);
    uint32_t B = ((alu->op & ALU_OP_INVB) ? ~alu->b : alu->b);

    // Generate results for all operations
    results[0] = A & B;
    results[1] = A | B;
    results[2] = A ^ B;
    results[3] = add32(A, B, (alu->op & ALU_OP_INVB) == ALU_OP_INVB);


    // Run result through multiplexer
    alu->result = results[(alu->op & ALU_OP_OPERATION) >> 3];
    
    // Invert output if necessary
    if(alu->op & ALU_OP_INVOUT) alu->result = ~alu->result;

    // Find flag values
    if(A > ((uint32_t)(~0) - B)) alu->flags |= ALU_FLAG_CARRY;
    else alu->flags &= ~ALU_FLAG_CARRY;
    if(alu->result == 0) alu->flags |= ALU_FLAG_ZERO;
    else alu->flags &= ~ALU_FLAG_ZERO;

    return 0;
}

int test_alu(uint32_t a, uint32_t b)
{
    INFO("Testing Aritmetic Logic Unit with (%X, %X)\n", a, b);
    
    struct alu alu;

    alu.a = a;
    alu.b = b;

    // Test AND
    alu.op = ALU_AND;
    emulate_alu(&alu);
    INFO("AND(%X, %X):  %08X:%X\n", alu.a, alu.b, alu.result, alu.flags);

    // Test NAND
    alu.op = ALU_NAND;
    emulate_alu(&alu);
    INFO("NAND(%X, %X): %08X:%X\n", alu.a, alu.b, alu.result, alu.flags);

    // Test OR
    alu.op = ALU_OR;
    emulate_alu(&alu);
    INFO("OR(%X, %X):   %08X:%X\n", alu.a, alu.b, alu.result, alu.flags);
    
    // Test OR
    alu.op = ALU_NOR;
    emulate_alu(&alu);
    INFO("NOR(%X, %X):  %08X:%X\n", alu.a, alu.b, alu.result, alu.flags);

    // Test XOR
    alu.op = ALU_XOR;
    emulate_alu(&alu);
    INFO("XOR(%X, %X):  %08X:%X\n", alu.a, alu.b, alu.result, alu.flags);

    // Test XNOR
    alu.op = ALU_XNOR;
    emulate_alu(&alu);
    INFO("XNOR(%X, %X): %08X:%X\n", alu.a, alu.b, alu.result, alu.flags);

    // Test ADD
    alu.op = ALU_ADD;
    emulate_alu(&alu);
    INFO("ADD(%X, %X):  %08X:%X\n", alu.a, alu.b, alu.result, alu.flags);
    
    // Test SUB
    alu.op = ALU_SUB;
    emulate_alu(&alu);
    INFO("SUB(%X, %X):  %08X:%X\n", alu.a, alu.b, alu.result, alu.flags);
    
    return 0;
}
