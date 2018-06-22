#include "Common.h"
#include "Memory.h"
#include "Display.h"

namespace gb
{

class Timer
{

public:
    Timer(Memory& _memory, Display& _display);

    void updateTimer(const int& cycles);
    void updateDisplay(const int& cycles);

private:
    static const word DIV_ADDR  = 0xff04;
    static const word TIMA_ADDR = 0xff05;
    static const word TMA_ADDR  = 0xff06;
    static const word TAC_ADDR  = 0xff07;

    static const word LCDC_ADDR = 0xff40;
    static const word STAT_ADDR = 0xff41;
    static const word LY_ADDR   = 0xff44;
    static const word LYC_ADDR  = 0xff45;

    Memory& memory;
    Display& display;

    unsigned int dividerTracker;
    unsigned int counterTracker;

    unsigned int scanlineTracker;
    bool         vblank;

    void requestInterrupt(const int& interruptType);
};

}  // namespace gb