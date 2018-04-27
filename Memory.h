#pragma once
#include <array>
#include "DataType.h"

class HW_Memory
{
public:
	void dump();

	BYTE readByte(WORD address);
	WORD readWord(WORD address);

	void writeByte(WORD address, BYTE value);
	void writeWord(WORD address, WORD value);
	
	void loadRom();
	void init();

private:
	std::array<BYTE, 65536> mem;		// 65536 addresses from 0x0000 to 0xFFFF
};