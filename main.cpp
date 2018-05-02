#include <iostream>
#include "CPU.h"
#include "Memory.h"

Gameboy::CPU cpu;
Gameboy::Memory memory;

int main()
{
	cpu.init();

    return 0;
}

