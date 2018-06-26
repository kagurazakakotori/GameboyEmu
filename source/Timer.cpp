#include "Timer.h"

namespace gb
{

void Timer::init()
{
    dividerTracker = 0;
    counterTracker = 0;
}

void Timer::sync(const int& cycles)
{
    updateDivider(cycles);
    updateTimer(cycles);
}

void Timer::updateDivider(const int& cycles)
{
    byte divider = memory.readByte(DIV_ADDR);  // 16384Hz, every 256 cycle

    dividerTracker += cycles;
    if (dividerTracker >= 256) {
        divider++;
        dividerTracker -= 256;
        //dividerTracker = 0;
    }
    memory.writeDiv(divider);
}

void Timer::updateTimer(const int& cycles)
{
    byte counter = memory.readByte(TIMA_ADDR);
    byte tac     = memory.readByte(TAC_ADDR);

    if (tac & 0x04) {  // Timer Enable
        unsigned int inputClock;
        switch (tac & 0x03) {
            case 0x0:
                inputClock = 1024;
            case 0x1:
                inputClock = 16;
            case 0x2:
                inputClock = 64;
            case 0x3:
                inputClock = 256;
        }

        counterTracker += cycles;
        if (counterTracker > inputClock) {
            if (0xff == counter) {
                requestInterrupt();
                counter = memory.readByte(TMA_ADDR);
            }
            else {
                counter++;
                counterTracker -= inputClock;
                //counterTracker = 0;
            }
        }
    }

    // Write back
    memory.writeByte(TIMA_ADDR, counter);
}

void Timer::requestInterrupt()
{
    byte interruptFlag = memory.readByte(IF_ADDR);
    setBit(interruptFlag, 2, 1);
    memory.writeByte(IF_ADDR, interruptFlag);
}

}  // namespace gb