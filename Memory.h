#pragma once
#include <vector>
#include "Cartridge.h"
#include "DataType.h"

namespace Gameboy
{

class Memory
{
public:
    Memory();

    void dump();

    byte readByte(word address);
    word readWord(word address);

    void writeByte(word address, byte value);
    void writeWord(word address, word value);

    void loadRom();
    void init();

private:
    Cartridge cart;

    std::vector<byte> rom;   // ROM
    std::vector<byte> vram;  // Video RAM
    std::vector<byte> sram;  // Switchable RAM
    std::vector<byte> wram;  // Working RAM ( 8k internal RAM since it is not GameBoy Color )
    std::vector<byte> oam;   // OAM for sprites
    std::vector<byte> io;    // Memory-mapped I/O registers
    std::vector<byte> hram;  // High ram
    byte interruptEnable;    // Interrupts Enable Register at 0xffff

    bool romLoaded = false;

    void boot();
};
}