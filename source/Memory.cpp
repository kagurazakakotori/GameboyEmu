#include "Memory.h"

namespace gb
{

Memory::Memory()
{
    vram.assign(0x2000, 0x00);  // 8K VRAM
    ram.assign(0x2000, 0x00);   // 8K Internal RAM
    oam.assign(0x100, 0x00);    // 256B OAM
    io.assign(0x80, 0x00);      // MMIO
    hram.assign(0x80, 0x00);    // 127B HRAM + IE at 0xffff

    std::cout << "[INFO] MMU initialized" << std::endl;
}

void Memory::loadRom(std::string romPath)
{
    std::ifstream file(romPath, std::ios::in | std::ios::binary);

    char b;
    int  i = 0;
    while (file.get(b)) {
        cart.rom.push_back(static_cast<byte>(b));
    }

    std::cout << "[INFO] ROM loaded successfully" << std::endl;
}

void Memory::init(Gamepad* _gamepad)
{
    gamepad = _gamepad;
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

byte Memory::readByte(const word& address)
{
    // WARNING: This implementation do NOT support I/O and MBC !
    // TODO: Add I/O support
    // TODO: Add MBC support
    switch (address & 0xf000) {
        case 0x0000:
        case 0x1000:
        case 0x2000:
        case 0x3000:
            return cart.rom[address];
        case 0x4000:
        case 0x5000:
        case 0x6000:
        case 0x7000:
            return cart.rom[(address & 0x3fff) + cart.romOffset];
        case 0x8000:
        case 0x9000:
            return vram[address & 0x1fff];
        case 0xa000:
        case 0xb000:
            return cart.ram[address & 0x1fff];
        case 0xc000:
        case 0xd000:
        case 0xe000:
            return ram[address & 0x1fff];
        case 0xf000:
            switch (address & 0x0f00) {
                case 0x000:
                case 0x100:
                case 0x200:
                case 0x300:
                case 0x400:
                case 0x500:
                case 0x600:
                case 0x700:
                case 0x800:
                case 0x900:
                case 0xa00:
                case 0xb00:
                case 0xc00:
                case 0xd00:
                    return ram[address & 0x1fff];
                case 0xe00:
                    return oam[address & 0x00ff];
                case 0xf00:
                    if (address >= 0xff80) {
                        return hram[address & 0x007f];
                    }
                    else if (address == 0xff00) {  // Joypad
                        return gamepad->readByte();
                    }
                    else {
                        return io[address & 0x00ff];
                        // TODO: I/O handling
                    }
            }
    }
}

word Memory::readWord(const word& address)
{
    return readByte(address) + (readByte(address + 1) << 8);
}

void Memory::writeByte(const word& address, const byte value)
{
    // WARNING: This implementation do NOT support I/O and MBC !
    // TODO: Add I/O support
    // TODO: Add MBC support
    switch (address & 0xf000) {
        case 0x0000:
        case 0x1000:
        case 0x2000:
        case 0x3000:
        case 0x4000:
        case 0x5000:
        case 0x6000:
        case 0x7000:
            return;
        case 0x8000:
        case 0x9000:
            vram[address & 0x1fff] = value;
            return;
        case 0xa000:
        case 0xb000:
            cart.ram[address & 0x1fff] = value;
            return;
        case 0xc000:
        case 0xd000:
        case 0xe000:
            ram[address & 0x1fff] = value;
            return;
        case 0xf000:
            switch (address & 0x0f00) {
                case 0x000:
                case 0x100:
                case 0x200:
                case 0x300:
                case 0x400:
                case 0x500:
                case 0x600:
                case 0x700:
                case 0x800:
                case 0x900:
                case 0xa00:
                case 0xb00:
                case 0xc00:
                case 0xd00:
                    ram[address & 0x1fff] = value;
                    return;
                case 0xe00:
                    oam[address & 0x00ff] = value;
                    return;
                case 0xf00:
                    if (address >= 0xff80) {
                        hram[address & 0x007f] = value;
                        return;
                    }
                    else if (address == 0xff00) {  // Joypad
                        gamepad->writeByte(value);
                        return;
                    }
                    else if (address == 0xff04) {  // DIV
                        io[address & 0x00ff] = 0;
                        return;
                    }
                    else {
                        io[address & 0x00ff] = value;
                        return;
                        // TODO: I/O handling
                    }
            }
    }
}

void Memory::writeWord(const word& address, const word value)
{
    writeByte(address, value & 0x00ff);
    writeByte(address + 1, (value & 0xff00) >> 8);
}

void Memory::writeDiv(const byte& value){
    io[0xff04 & 0x00ff] = value;
}

void Memory::boot()
{
    io[0xff05 & 0xff]   = 0x00;  // TIMA
    io[0xff06 & 0xff]   = 0x00;  // TMA
    io[0xff07 & 0xff]   = 0x00;  // TAC
    io[0xff10 & 0xff]   = 0x80;  // NR10
    io[0xff11 & 0xff]   = 0xbf;  // NR11
    io[0xff12 & 0xff]   = 0xf3;  // NR12
    io[0xff14 & 0xff]   = 0xbf;  // NR14
    io[0xff16 & 0xff]   = 0x3f;  // NR21
    io[0xff17 & 0xff]   = 0x00;  // NR22
    io[0xff19 & 0xff]   = 0xbf;  // NR24
    io[0xff1a & 0xff]   = 0x7f;  // NR30
    io[0xff1b & 0xff]   = 0xff;  // NR31
    io[0xff1c & 0xff]   = 0x9f;  // NR32
    io[0xff1e & 0xff]   = 0xbf;  // NR33
    io[0xff20 & 0xff]   = 0xff;  // NR41
    io[0xff21 & 0xff]   = 0x00;  // NR42
    io[0xff22 & 0xff]   = 0x00;  // NR43
    io[0xff23 & 0xff]   = 0xbf;  // NR30
    io[0xff24 & 0xff]   = 0x77;  // NR50
    io[0xff25 & 0xff]   = 0xf3;  // NR51
    io[0xff26 & 0xff]   = 0xf1;  // NR52
    io[0xff40 & 0xff]   = 0x91;  // LCDC
    io[0xff42 & 0xff]   = 0x00;  // SCY
    io[0xff43 & 0xff]   = 0x00;  // SCX
    io[0xff45 & 0xff]   = 0x00;  // LYC
    io[0xff47 & 0xff]   = 0xfc;  // BGP
    io[0xff48 & 0xff]   = 0xff;  // OBP0
    io[0xff49 & 0xff]   = 0xff;  // OBP1
    io[0xff4a & 0xff]   = 0x00;  // WY
    io[0xff4b & 0xff]   = 0x00;  // WX
    hram[0xffff & 0x7f] = 0x00;  // IE
}

}  // namespace gb