#include <cpu.h>

int emulate_cpu(struct cpu *bacpu)
{
    if(bacpu == NULL) { FATAL("emulate_cpu: bacpu == NULL\n"); return 1; }

    if(!(bacpu->in.enable)) return 0; // CPU is not enabled
    
    if(bacpu->in.reset) // CPU reset
    {
        /*
         *      We need to reset some of the registers here so the CPU can
         *  successfully reset and reenter the BIOS. The PC needs to be reset,
         *  because the BIOS is always located at address 4096. Flags also needs
         *  to be reset in case the BIOS expects it to be cleared. The region
         *  registers are NOT cleared, because they are not required, as the
         *  flags register was cleared, thus it is in linear memory mode. The
         *  general-purpose registers are also not cleared, because they will be
         *  set when needed.
         */
        bacpu->regs.pc   = 4096;
        bacpu->regs.flgs = 0;

        return 0; // Done with reset
    }

    uint8_t opcode;

    memory_read(bacpu, MMU_SIZE_BYTE, bacpu->regs.pc, &opcode);

    // NOTE: Emulator-only instruction!
    if(opcode == 0xFF)
    {
        uint8_t subcode;
        memory_read(bacpu, MMU_SIZE_BYTE, bacpu->regs.pc+1, &subcode);
        switch(subcode)
        {
            case 0x00: // Halt forever
                INFO("Halting forever at %08X...\n", bacpu->regs.pc);
                for(;;) ndelay(1000000); // TODO: Do something better...
                break;

            case 0x01: // Quit emulator
                INFO("Quitting emulator at %08X...\n", bacpu->regs.pc);
                return 1;

            case 0x02: // Display message
            {
                uint32_t str = 0;
                memory_read(bacpu, MMU_SIZE_DWORD, bacpu->regs.pc+2, &str);
                INFO("CPU Says: (0x%X):%s\n", str, (char *)(bacpu->mm.memory + str));
                bacpu->regs.pc += 6; // 1 + 1 + 4
            }   break;

            default:
                FATAL("Unrecognized emulator opcode 0x%02X at 0x%08X. Halting.\n", subcode, bacpu->regs.pc);
                for(;;) ndelay(1000000); // TODO
                break;
        }

        return 0;
    }
    
    INFO("Executing opcode %02X at %08X\n", opcode, bacpu->regs.pc);

    if(instructions[opcode](bacpu))
    {
        // TODO: Handle this well
        INFO("Instruction failed\n");
    }

    return 0;
}
