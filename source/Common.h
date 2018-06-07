#pragma once
#include <cstdint>

using byte = uint8_t;
using word = uint16_t;

bool getBit(const byte& source, int bit);
void setBit(byte& target, int bit, bool value);