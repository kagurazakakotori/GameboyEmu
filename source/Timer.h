#include "Common.h"
#include "Display.h"
#include "Memory.h"

namespace gb
{

class Timer
{

public:
    Timer(Memory& _memory, Display& _display);

    void sync(const int& cycles);
    //void updateDisplay(const int& cycles);

private:
    static const word DIV_ADDR  = 0xff04;
    static const word TIMA_ADDR = 0xff05;
    static const word TMA_ADDR  = 0xff06;
    static const word TAC_ADDR  = 0xff07;
    static const word LCDC_ADDR = 0xff40;

    Memory&  memory;
    Display& display;

    unsigned int dividerTracker;
    unsigned int counterTracker;

    void requestInterrupt();
};

}  // namespace gb