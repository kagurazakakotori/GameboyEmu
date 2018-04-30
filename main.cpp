#include <iostream>
#include "CPU.h"
#include "Memory.h"

Gameboy::CPU cpu;
Gameboy::Memory memory;

int main()
{
	cpu.init();
	
	//Testing memory;
	memory.writeWord(0xc602, 0xcccc);
	memory.dump();

    return 0;
}

