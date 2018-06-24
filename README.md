# GameboyEmu

Yet Another Gameboy Emulator

<!-- Object Oriented Programming Course Project, SSE, Tongji University, 2018. -->

## Development Progress

### Fully working

Sadly, nothing is fully working

### Partial working

* Gameboy CPU Emulation
* Memory Emulation (No MBC support)
* Timer (working but cant pass test)
* Display (No sprites)
* Input mapping (without customize)

### To be done

* Memory Bank Controllers support
* ROM loader
* CLI commands
* and more...

## Screenshots

### Hello World!

![Hello World Screenshot](/screenshots/helloworld.png)

## CPU tests results

| Test No.              | Result                             |
| --------------------- | ---------------------------------- |
| 01-special            | Passed                             |
| 02-interrupts         | Test #4 failed, Timer doesn't work |
| 03-op sp,hl           | Failed (Stuck)                     |
| 04-op r,imm           | Passed                             |
| 05-op rp              | Passed                             |
| 06-ld r,r             | Passed                             |
| 07-jr,jp,call,ret,rst | Passed                             |
| 08-misc instrs        | Failed (Stuck)                     |
| 09-op r,r             | Passed                             |
| 10-bit ops            | Passed                             |
| 11-op a,(hl)          | Passed                             |

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