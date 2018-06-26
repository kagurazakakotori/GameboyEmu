#include "Common.h"
#include "Display.h"
#include "Memory.h"

namespace gb
{

class Timer
{

public:
    Timer(Memory& _memory) : memory(_memory) {}

    void init();

    void sync(const int& cycles);

private:
    static const word DIV_ADDR  = 0xff04;
    static const word TIMA_ADDR = 0xff05;
    static const word TMA_ADDR  = 0xff06;
    static const word TAC_ADDR  = 0xff07;

    Memory& memory;

    unsigned int dividerTracker;
    unsigned int counterTracker;

    void updateDivider(const int& cycles);
    void updateTimer(const int& cycles);
    void requestInterrupt();
};

}  // namespace gb