#include "Cartridge.h"

namespace gb
{

Cartridge::Cartridge()
{
    ram.assign(0x20000, 0x00);  // Maxmium 128K External RAM (MBC5)
}

void Cartridge::getType()
{
    switch (rom[0x0147]) {
        case 0x00:  // ROM ONLY
            return;
        case 0x01:  // MBC1
            mbc1 = true;
            return;
        case 0x02:  // MBC1+RAM
            mbc1 = true;
            sram = true;
            return;
        case 0x03:  // MBC1+RAM+BATTERY
            mbc1    = true;
            sram    = true;
            battery = true;
            return;
        case 0x05:  // MBC2
            mbc2 = true;
            return;
        case 0x06:  // MBC2+BATTERY
            mbc2    = true;
            battery = true;
            return;
        case 0x08:  // ROM+RAM
            sram = true;
            return;
        case 0x09:  // ROM+RAM+BATTERY
            sram    = true;
            battery = true;
            return;
        case 0x0b:  // MMM01
            mmm01 = true;
            return;
        case 0x0c:  // MMM01+RAM
            mmm01 = true;
            sram  = true;
            return;
        case 0x0d:  // MMM01+RAM+BATTERY
            mmm01   = true;
            sram    = true;
            battery = true;
            return;
        case 0x0f:  // MBC3+TIMER+BATTERY
            mbc3    = true;
            timer   = true;
            battery = true;
            return;
        case 0x10:  // MBC3+TIMER+RAM+BATTERY
            mbc3    = true;
            timer   = true;
            sram    = true;
            battery = true;
            return;
        case 0x11:  // MBC3
            mbc3 = true;
            return;
        case 0x12:  // MBC3+RAM
            mbc3 = true;
            sram = true;
            return;
        case 0x13:  // MBC3+RAM+BATTERY
            mbc3    = true;
            sram    = true;
            battery = true;
            return;
        case 0x19:  // MBC5
            mbc5 = true;
            return;
        case 0x1a:  // MBC5+RAM
            mbc5 = true;
            sram = true;
            return;
        case 0x1b:  // MBC5+RAM+BATTERY
            mbc5    = true;
            sram    = true;
            battery = true;
            return;
        case 0x1c:  // MBC5+RUMBLE
            mbc5   = true;
            rumble = true;
            return;
        case 0x1d:  // MBC5+RUMBLE+RAM
            mbc5   = true;
            rumble = true;
            sram   = true;
            return;
        case 0x1e:  // MBC5+RUMBLE+RAM+BATTERY
            mbc5    = true;
            rumble  = true;
            sram    = true;
            battery = true;
            return;
        case 0x20:  // MBC6
            mbc6 = true;
            return;
        case 0x22:  // MBC7+SENSOR+RUMBLE+RAM+BATTERY
            mbc7    = true;
            sensor  = true;
            rumble  = true;
            sram    = true;
            battery = true;
            return;
        case 0xfc:  // POCKET CAMERA
            camera = true;
            return;
        case 0xfd:  // BANDAI TAMA5
            tama5 = true;
            return;
        case 0xfe:  // HuC3
            huc3 = true;
            return;
        case 0xff:  //HuC1+RAM+BATTERY
            huc1    = true;
            sram    = true;
            battery = true;
            return;
    }
}

void Cartridge::getRomSize()
{
    switch (rom[0x0148]) {
        case 0x00:
            return;
        case 0x01:
            romSize = 4;
            return;
        case 0x02:
            romSize = 8;
            return;
        case 0x03:
            romSize = 16;
            return;
        case 0x04:
            romSize = 32;
            return;
        case 0x05:
            romSize = 64;
            return;
        case 0x06:
            romSize = 128;
            return;
        case 0x07:
            romSize = 256;
            return;
        case 0x08:
            romSize = 512;
            return;
        case 0x52:
            romSize = 72;
            return;
        case 0x53:
            romSize = 80;
            return;
        case 0x54:
            romSize = 96;
            return;
    }
}

void Cartridge::getRamSize()
{
    switch (rom[0x0149]) {
        case 0x00:       // None
            if (mbc2) {  // MBC2 has a built-in 512*4bit RAM
                ramSize = 1;
            }
            return;
        case 0x01:  // 2KB
        case 0x02:  // 8KB
            ramSize = 1;
            return;
        case 0x03:  // 32KB
            ramSize = 4;
            return;
        case 0x04:  // 128KB
            ramSize = 16;
            return;
        case 0x05:  // 64KB
            ramSize = 8;
            return;
    }
}

void Cartridge::getTitle()
{
    for(int i = 0x0134 ; i < 0x0143; i++)
    {
       if(rom[i] != 0x00){
           _title += rom[i];
       }
    }

	std::cout << "[INFO] Cartridge title: " << _title << std::endl;
}

}  // namespace gb