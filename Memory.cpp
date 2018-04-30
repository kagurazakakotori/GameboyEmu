#include "Memory.h"
#include <iostream>
#include <fstream>

void Gameboy::Memory::dump()
{
	using namespace std;
	std::array<byte, 0x60> tempArr = { '\0' };
	ofstream dumpfile("memory_dump.bin",ofstream::binary);
	dumpfile.write(reinterpret_cast<const char*>(&rom), 0x8000);
	dumpfile.write(reinterpret_cast<const char*>(&vram), 0x2000);
	dumpfile.write(reinterpret_cast<const char*>(&sram), 0x2000);
	dumpfile.write(reinterpret_cast<const char*>(&wram), 0x2000);
	dumpfile.write(reinterpret_cast<const char*>(&wram), 0x1e00);
	dumpfile.write(reinterpret_cast<const char*>(&oam), 0xa0);
	dumpfile.write(reinterpret_cast<const char*>(&tempArr), 0x60);
	dumpfile.write(reinterpret_cast<const char*>(&io), 0x80);
	dumpfile.write(reinterpret_cast<const char*>(&hram), 0x7f);
	dumpfile.write(reinterpret_cast<const char*>(&interrupt), 1);
	dumpfile.close();
}

byte Gameboy::Memory::readByte(word address)
{
	if (address < 0x8000) {
		return rom[address];
	}
	else if (address >= 0x8000 && address < 0xa000) {
		return vram[address - 0x8000];
	}
	else if (address >= 0xa000 && address < 0xc000) {
		return sram[address - 0xa000];
	}
	else if (address >= 0xc000 && address < 0xe000) {
		return wram[address - 0xc000];
	}
	else if (address >= 0xe000 && address < 0xfe00) {
		return wram[address - 0xe000];
	}
	else if (address >= 0xfe00 && address < 0xfea0) {
		return oam[address - 0xfe00];
	}
	else if (address >= 0xff00 && address < 0xff80) {
		return io[address - 0xff00];
	}
	else if (address >= 0xff80 && address < 0xffff) {
		return hram[address - 0xff80];
	}
	else if (address = 0xffff) {
		return interrupt;
	}
}

word Gameboy::Memory::readWord(word address)
{
	return readByte(address + 1) << 8 | readByte(address);
}

void Gameboy::Memory::writeByte(word address, byte value)
{
	if (address >= 0x8000 && address < 0xa000) {
		vram[address - 0x8000] = value;
	}
	else if (address >= 0xa000 && address < 0xc000) {
		sram[address - 0xa000] = value;
	}
	else if (address >= 0xc000 && address < 0xe000) {
		wram[address - 0xc000] = value;
	}
	else if (address >= 0xe000 && address < 0xfe00) {
		wram[address - 0xe000] = value;
	}
	else if (address >= 0xfe00 && address < 0xfea0) {
		oam[address - 0xfe00] = value;
	}
	else if (address >= 0xff00 && address < 0xff80) {
		io[address - 0xff00] = value;
	}
	else if (address >= 0xff80 && address < 0xffff) {
		hram[address - 0xff80] = value;
	}
	else if (address = 0xffff) {
		interrupt = value;
	}
}

void Gameboy::Memory::writeWord(word address, word value)
{
	writeByte(address, value & 0x00FF);
	writeByte(address + 1, (value & 0xFF00) >> 8);
}