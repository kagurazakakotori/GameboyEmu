#pragma once
#include "DataType.h"

struct HW_Reg
{
	BYTE a = 0;
	BYTE f = 0;
	BYTE b = 0;
	BYTE c = 0;
	BYTE d = 0;
	BYTE e = 0;
	BYTE h = 0;
	BYTE l = 0;
	WORD sp = 0;
	WORD pc = 0;
};

class HW_CPU
{
public:
	void init();
private:
	HW_Reg reg;
};