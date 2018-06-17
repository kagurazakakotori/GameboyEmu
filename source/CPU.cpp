#include "CPU.h"

namespace gb
{

CPU::CPU(Memory& _memory) : memory(_memory)
{
    // Load instruction codes
    loadOpcode();
    loadCbcode();

    std::cout << "[INFO] CPU initialized" << std::endl;
}

void CPU::init()
{
    // Initialize registers
    reg.a  = 0x01;
    reg.f  = 0xb0;
    reg.bc = 0x0013;
    reg.de = 0x00d8;
    reg.hl = 0x014d;
    reg.pc = 0x0100;
    reg.sp = 0xfffe;
    cycle  = 0;
}

void CPU::exec()
{
    byte value = memory.readByte(reg.pc++);
    cycle += opcode[value]();

#ifdef DEBUG_MODE
    std::cout << "[INFO] Executing " << std::hex << value << std::endl;
    std::cout << "[INFO] Registers " << std::hex
              << "AF: " << reg.af << "BC: " << reg.bc << "DE: " << reg.de
              << "HL: " << reg.hl << "SP: " << reg.sp << "PC: " << reg.pc << std::endl;
#endif
}

}  // namespace gb
