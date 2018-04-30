#include <iostream>
#include "CPU.h"
#include "Memory.h"

Gameboy::CPU cpu;
Gameboy::Memory memory;

int main()
{
	cpu.init();
	
	//Testing memory;
	memory.writeByte(0xc602, 0xFF);
	memory.dump();

    return 0;
}

