#include <stdio.h>

#include <arithmetic.h>
#include <cpu.h>

pthread_t alu_thread;

static void *alu_task(void *);

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

    pthread_create(&alu_thread, NULL, alu_task, &bacpu->alu); // Create ALU task

    return 0;
}

static void *alu_task(void *alu)
{
    while(1) // TODO: Allow for stopping
    {
        if(emulate_alu((struct alu *)alu))
        {
            FATAL("ALU encountered an error!\n");
            return NULL;
        }
    }
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

#define ALU_TEST(bacpu, test, a, b) \
    ({ bacpu->alu.a = a; bacpu->alu.b = b; bacpu->alu.op = test; ndelay(100); bacpu->alu.result; })

int test_alu(struct cpu *bacpu, uint32_t a, uint32_t b)
{
    INFO("Testing Aritmetic Logic Unit with (%X, %X)\n", a, b);
    
    bacpu->alu.a = a;
    bacpu->alu.b = b;

    uint32_t res = 0;

    // Test AND
    res = ALU_TEST(bacpu, ALU_AND, a, b);
    INFO("AND:  %08X\n", res);

    // Test NAND
    res = ALU_TEST(bacpu, ALU_NAND, a, b);
    INFO("NAND: %08X\n", res);

    // Test OR
    res = ALU_TEST(bacpu, ALU_OR, a, b);
    INFO("OR:   %08X\n", res);
   
    // Test NOR
    res = ALU_TEST(bacpu, ALU_NOR, a, b);
    INFO("NOR:  %08X\n", res);

    // Test XOR
    res = ALU_TEST(bacpu, ALU_XOR, a, b);
    INFO("XOR:  %08X\n", res);

    // Test XNOR
    res = ALU_TEST(bacpu, ALU_XNOR, a, b);
    INFO("XNOR: %08X\n", res);

    // Test ADD
    res = ALU_TEST(bacpu, ALU_ADD, a, b);
    INFO("ADD:  %08X\n", res);
   
    // Test SUB
    res = ALU_TEST(bacpu, ALU_SUB, a, b);
    INFO("SUB:  %08X\n", res);
   
    return 0;
}
