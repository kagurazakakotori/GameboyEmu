#pragma once
#include "DataType.h"

namespace Gameboy
{

struct Cartridge
{
	// Cartridge type (Default ROM only)
	bool mbc1 = false;
	bool mbc2 = false;
	bool mmc01 = false;
	bool mbc3 = false;
	bool mbc5 = false;
	bool mbc6 = false;
	bool mbc7 = false;
	bool tama5 = false;
	bool huc3 = false;
	bool huc1 = false;

	// External hardware
	bool ram = false;
	bool battery = false;
	bool timer = false;
	bool rumble = false;
	bool sensor = false;
	bool camera = false;

	// Clock counter registers
	struct RTC
	{
		byte second = 0;
		byte minute = 0;
		byte hour = 0;
		byte dayL = 0;
		byte dayH = 0;
	} rtc;
};

}