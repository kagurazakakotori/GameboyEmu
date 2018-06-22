#pragma once
#include <cstdint>
#include <termcolor.hpp>
#undef max
#undef min

namespace gb
{

using byte = uint8_t;
using word = uint16_t;

static const word IF_ADDR = 0xff0f;
static const word IE_ADDR = 0xffff;

enum interruptType { INTERRUPT_VBLANK, INTERRUPT_STAT, INTERRUPT_TIMER, INTERRUPT_SERIAL, INTERRUPT_JOYPAD };

bool getBit(const byte& source, int bit);
void setBit(byte& target, int bit, bool value);

}  // namespace gb