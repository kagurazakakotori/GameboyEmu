#include "Timer.h"

namespace gb
{

Timer::Timer(Memory& _memory, Display& _display) : memory(_memory), display(_display)
{
    dividerTracker  = 0;
    counterTracker  = 0;
    scanlineTracker = 0;
    vblank          = false;
}

void Timer::updateTimer(const int& cycles)
{
    byte divider = memory.readByte(DIV_ADDR);  // 16384Hz, every 256 cycle

    dividerTracker += cycles;
    if (dividerTracker >= 256) {
        divider++;
        dividerTracker -= 256;
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
                requestInterrupt(INTERRUPT_TIMER);
                counter = memory.readByte(TMA_ADDR);
            }
            else {
                counter++;
                counterTracker -= inputClock;
            }
        }
    }

    // Write back
    memory.writeDiv(divider);
    memory.writeByte(TIMA_ADDR, counter);
}

void Timer::updateDisplay(const int& cycles)
{
    byte scanline = memory.readByte(LY_ADDR);
    byte lcdc     = memory.readByte(LCDC_ADDR);

    if (lcdc & 0x80) {  // LCDC Enable
        scanlineTracker += cycles;
        if (scanlineTracker >= 456) {
            scanline++;
            scanlineTracker -= 456;

            if (scanline < 144) {
                display.renderScanline(scanline);
            }
        }
        if (scanline > 153) {
            scanline = 0;
            vblank   = false;
        }
    }
    else {  // Reset if disables
        scanline        = 0;
        scanlineTracker = 0;
    }

    // Update STAT
    byte stat = memory.readByte(STAT_ADDR);
    if (scanline >= 144) {  // 01: V-Blank
        setBit(stat, 1, 0);
        setBit(stat, 0, 1);
        if (!vblank) {
            requestInterrupt(INTERRUPT_VBLANK);
            vblank = true;
        }
    }
    else if (scanlineTracker > (80 + 172)) {  // 00: H-Blank
        setBit(stat, 1, 0);
        setBit(stat, 0, 0);
    }
    else if (scanlineTracker > 80) {  // 11: VRAM
        setBit(stat, 1, 1);
        setBit(stat, 0, 1);
    }
    else {  // 10: OAM
        setBit(stat, 1, 1);
        setBit(stat, 0, 0);
    }

    // Check LYC
    byte lyc = memory.readByte(LYC_ADDR);
    if (lyc == scanline) {
        setBit(lcdc, 2, 1);
        requestInterrupt(INTERRUPT_STAT);
    }
    else {
        setBit(lcdc, 2, 0);
    }

    // Finally write back;
    memory.writeByte(LCDC_ADDR, lcdc);
    memory.writeByte(LY_ADDR, scanline);
}

void Timer::requestInterrupt(const int& interruptType)
{
    byte interruptFlag = memory.readByte(IF_ADDR);
    setBit(interruptFlag, interruptType, 1);
    memory.writeByte(IF_ADDR, interruptFlag);
}

}  // namespace gb