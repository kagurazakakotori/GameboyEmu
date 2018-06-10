#pragma once
#include "Common.h"
#include <string>
#include <vector>

namespace gb
{

class Cartridge
{
    friend class Memory;

public:
    Cartridge();

    std::string title() const { return _title; }

private:
    std::vector<byte> rom;  // ROM
    std::vector<byte> ram;  // External RAM in cartridge

    // Cartridge type (Default ROM only)
    bool mbc1  = false;
    bool mbc2  = false;
    bool mmm01 = false;

    bool mbc3  = false;
    bool mbc5  = false;
    bool mbc6  = false;
    bool mbc7  = false;
    bool tama5 = false;
    bool huc3  = false;
    bool huc1  = false;

    // External hardware
    bool sram    = false;
    bool battery = false;
    bool timer   = false;
    bool rumble  = false;
    bool sensor  = false;
    bool camera  = false;

    // ROM banking
    unsigned int romBank   = 1;  // Current ROM bank
    unsigned int romSize   = 2;
    unsigned int romOffset = 0x4000;

    // RAM banking
    unsigned int ramBank   = 0;  // Current RAM bank
    unsigned int ramSize   = 0;
    unsigned int ramOffset = 0x0000;
    bool         ramEnable = false;

    // ROM/RAM Banking Mode Select for MBC1
    bool mbc1_mode = false;  // false for ROM, true for RAM

    // Clock counter registers for MBC3
    struct RTC
    {
        byte second = 0;
        byte minute = 0;
        byte hour   = 0;
        byte dayL   = 0;
        byte dayH   = 0;
    } rtc;

    std::string _title;

    void getType();
    void getRomSize();
    void getRamSize();
    void getTitle();
};
}  // namespace gb