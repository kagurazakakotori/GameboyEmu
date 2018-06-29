#pragma once
#include <cstdint>
#include <termcolor.hpp>
#undef max
#undef min

namespace gb
{

using byte = uint8_t;
using word = uint16_t;

static const word IF_ADDR = 0xff0f;
static const word IE_ADDR = 0xffff;

// Display registers
static const word LCDC_ADDR = 0xff40;
static const word STAT_ADDR = 0xff41;
static const word SCX_ADDR  = 0xff43;
static const word SCY_ADDR  = 0xff42;
static const word BGP_ADDR  = 0xff47;
static const word WX_ADDR   = 0xff4b;
static const word WY_ADDR   = 0xff4a;
static const word LY_ADDR   = 0xff44;
static const word LYC_ADDR  = 0xff45;
static const word OBP0_ADDR = 0xff48;
static const word OBP1_ADDR = 0xff49;

// Timer registers
static const word DIV_ADDR  = 0xff04;
static const word TIMA_ADDR = 0xff05;
static const word TMA_ADDR  = 0xff06;
static const word TAC_ADDR  = 0xff07;

enum interruptType { INTERRUPT_VBLANK,
                     INTERRUPT_STAT,
                     INTERRUPT_TIMER,
                     INTERRUPT_SERIAL,
                     INTERRUPT_JOYPAD };

bool getBit(const byte& source, int bit);
void setBit(byte& target, int bit, bool value);

}  // namespace gb