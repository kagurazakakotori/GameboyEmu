#pragma once
#include <cstdint>

namespace gb
{

using byte = uint8_t;
using word = uint16_t;

static const word IF_ADDR = 0xff0f;

bool getBit(const byte& source, int bit);
void setBit(byte& target, int bit, bool value);

}  // namespace gb