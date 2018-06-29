# GameboyEmu

Yet Another Gameboy Emulator

Object Oriented Programming Course Project, SSE, Tongji University, 2018. 

## Development Progress

### What's working

* Gameboy CPU (LR35902) Emulation
* Timer (working, probably)
* Input (without customize)
* Memory Emulation (ROM only and MBC1)
* Display

### To be done

* Memory Bank Controllers support
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

## Dependencies

* [SFML](https://www.sfml-dev.org/)
* [termcolor](https://github.com/ikalnytskyi/termcolor)

## Build

### Linux

Ubuntu 18.04

```bash
# Install dependencies
sudo apt update
sudo apt install -y git build-essentials cmake
sudo apt install -y libsfml-dev libudev-dev libfreetype6-dev libxcb-image0-dev

# Download files
git clone https://github.com/kagurazakakotori/GameboyEmu.git
wget -N -P ./include/termcolor/ https://raw.githubusercontent.com/ikalnytskyi/termcolor/master/include/termcolor/termcolor.hpp

# Compile
cmake ./ -DCMAKE_PREFIX_PATH=./include/sfml/
cmake --build ./ --config Debug    # build debug
cmake --build ./ --config Release  # build release

# Run!
cd bin
./GameboyEmu

```

### Windows

You need install CMake and MSVC15 Compiler(included in Visual Studio 2017) first manually.

Script Following is for PowerShell use

```powershell
# Download files
git clone https://github.com/kagurazakakotori/GameboyEmu.git
Set-Location GameboyEmu\include
Invoke-WebRequest -Uri https://www.sfml-dev.org/files/SFML-2.5.0-windows-vc15-32-bit.zip -Outfile sfml.zip
Expand-Archive -Path sfml.zip -DestinationPath .\
Remove-Item .\sfml\
Remove-Item .\sfml.zip
Rename-Item .\SFML-2.5.0 .\sfml
Invoke-WebRequest -Uri https://raw.githubusercontent.com/ikalnytskyi/termcolor/master/include/termcolor/termcolor.hpp -Outfile .\termcolor\termcolor.hpp
Set-Location ..

# Compile
cmake ./ -DCMAKE_PREFIX_PATH=".\include\sfml"
cmake --build ./ --config Debug    # build debug
cmake --build ./ --config Release  # build release

# Run!
Set-Location bin\Release
.\GameboyEmu.exe

```

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