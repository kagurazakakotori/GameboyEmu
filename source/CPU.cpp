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
    word pc    = reg.pc;
    byte value = memory.readByte(reg.pc++);
    cycle += opcode[value]();

    /*  For debugging use
    instrCnt++;
    std::cout << "[INFO] " << std::dec << "[" << instrCnt << "] [Cycle:" << cycle << "] Executing " << std::showbase << std::hex << (int) value << " at " << pc << std::endl;
    std::cout << "[INFO] " << std::showbase << std::hex << "AF: " << reg.af << "   BC: " << reg.bc << "   DE: " << reg.de << "   HL: " << reg.hl << "   SP: " << reg.sp << "   PC: " << reg.pc << std::endl;
    std::cout << "[INFO] Stack pointer value: " << std::showbase << std::hex << memory.readWord(reg.sp) << std::endl;
    */
}

void CPU::handleInterrupt()
{
    byte interruptFlag   = memory.readByte(IF_ADDR);
    byte interruptEnable = memory.readByte(IE_ADDR);
    byte interruptFired  = interruptFlag & interruptEnable;

    if (interruptFlag && interruptEnable) {
        // Handle the HALT bug
        if (halt) {
            halt = false;
            reg.pc++;
        }

        // Service interrupt
        for (int i = 0; i < 5; i++) {
            if (getBit(interruptFired, i) && interruptMasterEnable) {
                serviceInterrupt(i);
            }
        }
    }
}

void CPU::serviceInterrupt(const int& interruptType)
{
    byte interruptFlag = memory.readByte(IF_ADDR);
    setBit(interruptFlag, interruptType, 0);
    memory.writeByte(IF_ADDR, interruptFlag);

    interruptMasterEnable = false;

    // Push current PC onto stack
    memory.writeByte(--reg.sp, ((reg.pc & 0xff00) >> 8));
    memory.writeByte(--reg.sp, (reg.pc & 0x00ff));

    // Set PC
    switch (interruptType) {
        case INTERRUPT_VBLANK:
            reg.pc = 0x40;
            return;
        case INTERRUPT_STAT:
            reg.pc = 0x48;
            return;
        case INTERRUPT_TIMER:
            reg.pc = 0x50;
            return;
        case INTERRUPT_SERIAL:
            reg.pc = 0x58;
            return;
        case INTERRUPT_JOYPAD:
            reg.pc = 0x60;
            return;
    }
}

}  // namespace gb
