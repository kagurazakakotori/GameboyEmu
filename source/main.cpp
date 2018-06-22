#include <iostream>
#include "Gameboy.h"

int main(int argc, char* argv[])
{
    std::cout << "[INFO] GameboyEmu ver 0.0.1 created on 2018-06-23" << std::endl;
    std::cout << termcolor::yellow << "[WARN] This is a unstable version. Use at your own risk" << termcolor::reset<< std::endl;

    gb::Gameboy gameboy;

    // TODO: argument parser
    gameboy.loadRom("rom/helloworld.gb");
    gameboy.init();
    gameboy.run();

    return 0;
}