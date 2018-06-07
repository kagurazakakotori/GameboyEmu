#include "Common.h"

bool getBit(const byte& source, int bit)
{
    return (source >> bit) & 1u;
}

void setBit(byte& target, int bit, bool value)
{
    target ^= (-value ^ target) & (1u << bit);
}