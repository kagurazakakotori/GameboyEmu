# GameboyEmu

Yet Another Gameboy Emulator

<!-- Object Oriented Programming Course Project, SSE, Tongji University, 2018. -->

## Development Progress

### What's working

* Gameboy CPU (LR35902) Emulation
* Timer (working, probably)
* Input (without customize)
* Memory Emulation (ROM only and MBC1)
* Display (No sprites)

### To be done

* Memory Bank Controllers support
* Sprite
* and more...

## Screenshots

### Hello World!

![Hello World screenshot](/screenshots/helloworld.png)

### CPU instruction test

![CPU instruction test screenshot](/screenshots/cpu_instr.png)

## Blargg's CPU tests results

| Test No.              | Result | Remark           |
| --------------------- | ------ | ---------------- |
| 01-special            | ✅      | Passed           |
| 02-interrupts         | ✅      | Passed           |
| 03-op sp,hl           | ✅      | Passed           |
| 04-op r,imm           | ✅      | Passed           |
| 05-op rp              | ✅      | Passed           |
| 06-ld r,r             | ✅      | Passed           |
| 07-jr,jp,call,ret,rst | ✅      | Passed           |
| 08-misc instrs        | ✅      | Passed           |
| 09-op r,r             | ✅      | Passed           |
| 10-bit ops            | ✅      | Passed           |
| 11-op a,(hl)          | ✅      | Passed           |
| all-cpu_instrs        | ✅      | Passed all tests |

## References

### Hardware

* [GameBoy CPU Manual (Many mistakes found, but still useful)](http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf)
* [Game Boy Programming Manual](https://archive.org/download/GameBoyProgManVer1.1/GameBoyProgManVer1.1.pdf)
* [Gameboy Development Wiki](http://gbdev.gg8.se/wiki/articles/Main_Page)
* [Awesome Game Boy Development](https://github.com/avivace/awesome-gbdev)

#### CPU

* [Gameboy CPU (LR35902) instruction set](http://pastraiser.com/cpu/gameboy/gameboy_opcodes.html)
* [GameBoy Opcode Summary](http://www.devrs.com/gb/files/opcodes.html)

#### Memory

* [GameBoy Memory Map](http://gameboy.mongenel.com/dmg/asmmemmap.html)

### Tutorials

* [How to make a (GameBoy) emulator?](https://www.cl.cam.ac.uk/~pv273/slides/emulation.pdf)
* [GameBoy Emulation in JavaScript](http://imrannazar.com/GameBoy-Emulation-in-JavaScript%3a-The-CPU)

### Other implementations

* [Two9A/jsGB on GitHub](https://github.com/Two9A/jsGB)
* [eidos06/Gameboy-Simulator on GitHub](https://github.com/eidos06/Gameboy-Simulator)

### Test roms

* [Blargg's Gameboy hardware test ROMs](https://github.com/retrio/gb-test-roms)