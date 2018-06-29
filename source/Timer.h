#pragma once
#include "Common.h"
#include "Display.h"
#include "Memory.h"

namespace gb
{
class Memory;

class Timer
{

public:
    Timer(Memory& _memory) : memory(_memory) {}

    void init();

    void sync(const int& cycles);

private:
    Memory& memory;

    int dividerTracker;
    int counterTracker;
    int counterFrequency;

    void updateDivider(const int& cycles);
    void updateTimer(const int& cycles);
    void requestInterrupt();
};

}  // namespace gb