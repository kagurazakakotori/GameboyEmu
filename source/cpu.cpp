#include "CPU.h"

void Gameboy::CPU::init()
{
    // Initialize registers
    reg.a  = 0x01;  // Gameboy CPU Manual 2.7.1
    reg.f  = 0xb0;
    reg.bc = 0x0013;
    reg.de = 0x00d8;
    reg.hl = 0x014d;
    reg.pc = 0x0100;  // Gameboy CPU Manual 3.2.3
    reg.sp = 0xfffe;  // Gameboy CPU Manual 3.2.4
}