#include <iostream>
#include "Gameboy.h"

int main(int argc, char* argv[])
{
    gb::Gameboy gameboy;

    // TODO: argument parser
    gameboy.loadRom("rom/helloworld.gb");
    gameboy.init();
    gameboy.run();

    return 0;
}