#ifndef INSTRUCTION_FORMAT_H
#define INSTRUCTION_FORMAT_H

#include <cpu.h>

struct opcode
{
    uint8_t inst;
    uint8_t inst_info;
} __packed;

struct opcode_only
{
    struct opcode op;
} __packed;

struct opcode_imm
{
    struct opcode op;
    uint32_t imm;
} __packed;

struct opcode_2reg
{
    struct opcode op;
    uint8_t reg1;
    uint8_t reg2;
} __packed;

struct opcode_imm_reg
{
    struct opcode op;
    uint32_t imm;
    uint8_t reg;
    uint8_t pad;
} __packed;

struct opcode_2imm
{
    struct opcode op;
    uint32_t imm1;
    uint32_t imm2;
} __packed;

#endif // INSTRUCTION_FORMAT_H
