#pragma once
#include <array>
#include "DataType.h"

namespace Gameboy {

class Memory
{
public:
	void dump();

	byte readByte(word address);
	word readWord(word address);

	void writeByte(word address, byte value);
	void writeWord(word address, word value);

	void loadRom();
	void init();

private:
	std::array<byte, 0x8000> rom;		// (0x0000~0x7fff) 32k rom
	std::array<byte, 0x2000> vram;		// (0x8000~0x9fff) 8k video ram
	std::array<byte, 0x2000> sram;		// (0xa000~0xbfff) 8k switchable ram
	std::array<byte, 0x2000> wram;		// (0xc000~0xdfff) 8k working/internal ram
	std::array<byte, 0xa0> oam;			// (0xfe00~0xfe9f) oam for sprites
	std::array<byte, 0x80> io;			// (0xff00~0xff7f) io registers
	std::array<byte, 0x7f> hram;		// (0xff80~0xfffe) high ram
	byte interrupt = 0;
};

}