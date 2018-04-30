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
	std::array<byte, 65536> mem;		// 65536 addresses from 0x0000 to 0xFFFF
};

}