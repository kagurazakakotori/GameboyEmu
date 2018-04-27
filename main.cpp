#include <iostream>
#include "CPU.h"
#include "Memory.h"

HW_CPU cpu;
HW_Memory memory;

int main()
{
	cpu.init();
	
	//Testing memory;
	memory.writeByte(0xc602, 0xFF);
	memory.dump();

    return 0;
}

