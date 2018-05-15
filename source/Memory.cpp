#include "Memory.h"
#include <iostream>

Gameboy::Memory::Memory()
{
    vram.assign(0x2000, 0x00);  // 8K VRAM
    ram.assign(0x2000, 0x00);   // 8K Internal RAM
    oam.assign(0x100, 0x00);    // 256B OAM
    io.assign(0x80, 0x00);      // MMIO
    hram.assign(0x7f, 0x00);    // 127B HRAM
    interruptEnable = 0x00;
}

void Gameboy::Memory::init()
{
    // Emulate BIOS operations on boot
    boot();

    // Read cartridge type from ROM header
    cart.getType();

    // Get ROM bank numbers (16KB per bank)
    cart.getRomSize();

    // Get RAM bank numbers (8KB per bank)
    cart.getRamSize();

    // Get game title
    cart.getTitle();
}

void Gameboy::Memory::boot()
{
    io[0xff00 & 0xff] = 0x00;  // Leaving all keys unpressed
    io[0xff05 & 0xff] = 0x00;  // TIMA
    io[0xff06 & 0xff] = 0x00;  // TMA
    io[0xff07 & 0xff] = 0x00;  // TAC
    io[0xff10 & 0xff] = 0x80;  // NR10
    io[0xff11 & 0xff] = 0xbf;  // NR11
    io[0xff12 & 0xff] = 0xf3;  // NR12
    io[0xff14 & 0xff] = 0xbf;  // NR14
    io[0xff16 & 0xff] = 0x3f;  // NR21
    io[0xff17 & 0xff] = 0x00;  // NR22
    io[0xff19 & 0xff] = 0xbf;  // NR24
    io[0xff1a & 0xff] = 0x7f;  // NR30
    io[0xff1b & 0xff] = 0xff;  // NR31
    io[0xff1c & 0xff] = 0x9f;  // NR32
    io[0xff1e & 0xff] = 0xbf;  // NR33
    io[0xff20 & 0xff] = 0xff;  // NR41
    io[0xff21 & 0xff] = 0x00;  // NR42
    io[0xff22 & 0xff] = 0x00;  // NR43
    io[0xff23 & 0xff] = 0xbf;  // NR30
    io[0xff24 & 0xff] = 0x77;  // NR50
    io[0xff25 & 0xff] = 0xf3;  // NR51
    io[0xff26 & 0xff] = 0xf1;  // NR52
    io[0xff40 & 0xff] = 0x91;  // LCDC
    io[0xff42 & 0xff] = 0x00;  // SCY
    io[0xff43 & 0xff] = 0x00;  // SCX
    io[0xff45 & 0xff] = 0x00;  // LYC
    io[0xff47 & 0xff] = 0xfc;  // BGP
    io[0xff48 & 0xff] = 0xff;  // OBP0
    io[0xff49 & 0xff] = 0xff;  // OBP1
    io[0xff4a & 0xff] = 0x00;  // WY
    io[0xff4b & 0xff] = 0x00;  // WX
    interruptEnable   = 0x00;  // IE
}