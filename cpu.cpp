#include "CPU.h"

void Gameboy::CPU::init()
{
	// Initialize registers
	reg.a = 0x01;			// Gameboy CPU Manual 2.7.1
	reg.f = 0xb0;
	reg.b = 0x00;
	reg.c = 0x13;
	reg.d = 0x00;
	reg.e = 0xd8;
	reg.h = 0x01;
	reg.l = 0x4d;
	reg.pc = 0x0100;		// Gameboy CPU Manual 3.2.3
	reg.sp = 0xfffe;		// Gameboy CPU Manual 3.2.4
}