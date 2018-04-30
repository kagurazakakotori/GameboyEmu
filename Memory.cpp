#include "Memory.h"
#include <iostream>
#include <fstream>

void Gameboy::Memory::dump()
{
	using namespace std;
	ofstream dumpfile("memory_dump.bin",ofstream::binary);
	dumpfile.write(reinterpret_cast<const char*>(&mem), 65536);
	dumpfile.close();
}

BYTE Gameboy::Memory::readByte(WORD address)
{
	if (address >= 0xe000 && address < 0xfe00) {
		return mem[address - 0xe000 + 0xc000];			// Echo area
	}
	else {
		return mem[address];
	}
	// TODO: I/O Memory
}

void Gameboy::Memory::writeByte(WORD address, BYTE value)
{
	// TEST ONLY
	if (address >= 0xc000 && address < 0xce00) {
		mem[address] = value;							// Echo area
		mem[address - 0xc000 + 0xe000] = value;
	}
	else {
		mem[address] = value;
	}
}