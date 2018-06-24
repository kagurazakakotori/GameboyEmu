#include "Timer.h"

namespace gb
{

Timer::Timer(Memory& _memory, Display& _display) : memory(_memory), display(_display)
{
    dividerTracker  = 0;
    counterTracker  = 0;
    //scanlineTracker = 0;
    //vblank          = false;
}

void Timer::sync(const int& cycles)
{
    byte divider = memory.readByte(DIV_ADDR);  // 16384Hz, every 256 cycle

    dividerTracker += cycles;
    if (dividerTracker >= 256) {
        divider++;
        dividerTracker -= 256;
        //dividerTracker = 0;
    }

    byte counter = memory.readByte(TIMA_ADDR);
    byte tac     = memory.readByte(TAC_ADDR);

    if (tac & 0x04) {  // Timer Enable
        unsigned int inputClock;
        switch (tac & 0x03) {
            case 0b00:
                inputClock = 1024;
            case 0b01:
                inputClock = 16;
            case 0b10:
                inputClock = 64;
            case 0b11:
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
    memory.writeDiv(divider);
    memory.writeByte(TIMA_ADDR, counter);
}

void Timer::requestInterrupt()
{
    byte interruptFlag = memory.readByte(IF_ADDR);
    setBit(interruptFlag, 2, 1);
    memory.writeByte(IF_ADDR, interruptFlag);
}

}  // namespace gb