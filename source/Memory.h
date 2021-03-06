#pragma once
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include "Cartridge.h"
#include "Common.h"
#include "Display.h"
#include "Gamepad.h"

namespace gb
{

class Display;
class Gamepad;

class Memory
{
public:
    Memory();

    //void dump();

    byte readByte(const word& address);
    word readWord(const word& address);

    void writeByte(const word& address, const byte value);
    void writeWord(const word& address, const word value);

    void loadRom(std::string path);
    void init(Gamepad* _gamepad, Display* _display);

    void writeDiv(const byte& value);  // Write divider/DIV at 0xff04

private:
    Cartridge cart;
    Gamepad*  gamepad;
    Display*  display;

    std::vector<byte> vram;  // Video RAM
    std::vector<byte> ram;   // Working RAM ( 8k internal RAM since it is not GameBoy Color )
    std::vector<byte> oam;   // OAM for sprites
    std::vector<byte> io;    // Memory-mapped I/O registers
    std::vector<byte> hram;  // High ram

    bool romLoaded = false;

    void transferToOAM(const byte& addrPrefix);
    void boot();
};

}  // namespace gb